// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/file_util.h"
#include "common/ini.h"
#include "common/microprofile.h"
#include "common/settings.h"
#include "common/texture.h"
#include "core/core.h"
#include "video_core/rasterizer_cache/custom_tex_manager.h"
#include "video_core/rasterizer_cache/default_pack_ini.h"
#include "video_core/rasterizer_cache/surface_params.h"

namespace VideoCore {

namespace {

MICROPROFILE_DEFINE(CustomTexManager_TickFrame, "CustomTexManager", "TickFrame",
                    MP_RGB(54, 16, 32));
MICROPROFILE_DEFINE(CustomTexManager_ComputeHash, "CustomTexManager", "LoadTexture",
                    MP_RGB(64, 32, 128));

constexpr std::size_t MAX_UPLOADS_PER_TICK = 16;

bool IsPow2(u32 value) {
    return value != 0 && (value & (value - 1)) == 0;
}

CustomFileFormat MakeFileFormat(std::string_view ext) {
    if (ext == "png") {
        return CustomFileFormat::PNG;
    } else if (ext == "dds") {
        return CustomFileFormat::DDS;
    } else if (ext == "ktx") {
        return CustomFileFormat::KTX;
    }
    LOG_ERROR(Render, "Unknown file extension {}", ext);
    return CustomFileFormat::PNG;
}

CustomPixelFormat ToCustomPixelFormat(ddsktx_format format) {
    switch (format) {
    case DDSKTX_FORMAT_RGBA8:
        return CustomPixelFormat::RGBA8;
    case DDSKTX_FORMAT_BC1:
        return CustomPixelFormat::BC1;
    case DDSKTX_FORMAT_BC3:
        return CustomPixelFormat::BC3;
    case DDSKTX_FORMAT_BC5:
        return CustomPixelFormat::BC5;
    case DDSKTX_FORMAT_BC7:
        return CustomPixelFormat::BC7;
    case DDSKTX_FORMAT_ASTC4x4:
        return CustomPixelFormat::ASTC4;
    case DDSKTX_FORMAT_ASTC6x6:
        return CustomPixelFormat::ASTC6;
    case DDSKTX_FORMAT_ASTC8x6:
        return CustomPixelFormat::ASTC8;
    default:
        LOG_ERROR(Common, "Unknown dds/ktx pixel format {}", format);
        return CustomPixelFormat::RGBA8;
    }
}

} // Anonymous namespace

CustomTexManager::CustomTexManager(Core::System& system_)
    : system{system_}, image_interface{*system.GetImageInterface()} {}

CustomTexManager::~CustomTexManager() = default;

void CustomTexManager::TickFrame() {
    if (!textures_loaded) {
        return;
    }

    MICROPROFILE_SCOPE(CustomTexManager_TickFrame);

    std::size_t num_uploads = 0;
    for (auto it = async_uploads.begin(); it != async_uploads.end();) {
        if (num_uploads >= MAX_UPLOADS_PER_TICK) {
            return;
        }
        if (it->texture->IsDecoded()) {
            it->func();
            num_uploads++;
            it = async_uploads.erase(it);
        } else {
            it++;
        }
    }
}

void CustomTexManager::FindCustomTextures() {
    if (textures_loaded) {
        return;
    }

    if (!workers) {
        CreateWorkers();
    }

    // Custom textures are currently stored as
    // [TitleID]/tex1_[width]x[height]_[64-bit hash]_[format].png
    const u64 program_id = system.Kernel().GetCurrentProcess()->codeset->program_id;
    const std::string load_path =
        fmt::format("{}textures/{:016X}/", GetUserPath(FileUtil::UserPath::LoadDir), program_id);

    // Create the directory if it did not exist
    if (!FileUtil::Exists(load_path)) {
        FileUtil::CreateFullPath(load_path);
    }

    FileUtil::FSTEntry texture_dir;
    std::vector<FileUtil::FSTEntry> textures;
    // 64 nested folders should be plenty for most cases
    FileUtil::ScanDirectoryTree(load_path, texture_dir, 64);
    FileUtil::GetAllFilesFromNestedEntries(texture_dir, textures);

    // Read configuration file if it exists
    ReadConfig(load_path);

    // Reserve space for all the textures in the folder
    const std::size_t num_textures = textures.size();
    custom_textures.resize(num_textures);

    u32 width{};
    u32 height{};
    u32 format{};
    unsigned long long hash{};
    std::string ext(3, '\0');
    for (std::size_t i = 0; i < textures.size(); i++) {
        const auto& file = textures[i];
        const std::string& path = file.physicalName;
        if (file.isDirectory) {
            continue;
        }

        // Check if the path is mapped directly to a hash before trying to parse the texture
        // filename. In the latter case we only really care about the hash, the rest will be queried
        // from the file itself.
        const auto it = path_to_hash_map.find(file.virtualName);
        if (it != path_to_hash_map.end()) {
            hash = it->second;
        } else if (std::sscanf(file.virtualName.c_str(), "tex1_%ux%u_%llX_%u", &width, &height,
                               &hash, &format) != 4) {
            continue;
        }

        const auto format{MakeFileFormat(FileUtil::GetExtensionFromFilename(file.virtualName))};
        if (format == CustomFileFormat::DDS && refuse_dds) {
            LOG_ERROR(Render, "Legacy pack is attempting to use DDS textures, skipping!");
            return;
        }

        custom_textures[i] = std::make_unique<CustomTexture>();
        CustomTexture& texture = *custom_textures[i];

        // Fill in relevant information
        texture.file_format = format;
        texture.hash = hash;
        texture.path = path;
    }

    // Assign each texture to the hash map
    for (const auto& texture : custom_textures) {
        if (!texture) {
            continue;
        }
        const u64 hash = texture->hash;
        auto [it, new_texture] = custom_texture_map.try_emplace(hash);
        if (!new_texture) {
            LOG_ERROR(Render, "Textures {} and {} conflict, ignoring!",
                      custom_texture_map[hash]->path, texture->path);
            continue;
        }
        it->second = texture.get();
    }

    textures_loaded = true;
}

void CustomTexManager::WriteConfig() {
    const u64 program_id = system.Kernel().GetCurrentProcess()->codeset->program_id;
    const std::string dump_path =
        fmt::format("{}textures/{:016X}/", GetUserPath(FileUtil::UserPath::DumpDir), program_id);
    const std::string pack_config = dump_path + "pack.ini";
    if (!FileUtil::Exists(pack_config)) {
        FileUtil::IOFile config{pack_config, "w"};
        config.WriteString(DefaultINI::pack_config_file);
        config.Flush();
    }
}

void CustomTexManager::PreloadTextures() {
    const std::size_t num_textures = custom_textures.size();
    const std::size_t num_workers{workers->NumWorkers()};
    const std::size_t bucket_size{num_textures / num_workers};

    for (std::size_t i = 0; i < num_workers; ++i) {
        const bool is_last_worker = i + 1 == num_workers;
        const std::size_t start{bucket_size * i};
        const std::size_t end{is_last_worker ? num_textures : start + bucket_size};
        workers->QueueWork([this, start, end]() {
            for (std::size_t i = start; i < end; i++) {
                if (!custom_textures[i]) {
                    continue;
                }
                LoadTexture(custom_textures[i].get());
            }
        });
    }
    workers->WaitForRequests();
}

void CustomTexManager::DumpTexture(const SurfaceParams& params, u32 level, std::span<u8> data,
                                   u64 data_hash) {
    const u32 data_size = static_cast<u32>(data.size());
    const u32 width = params.width;
    const u32 height = params.height;
    const PixelFormat format = params.pixel_format;

    // Check if it's been dumped already
    if (dumped_textures.contains(data_hash)) {
        return;
    }

    // Make sure the texture size is a power of 2.
    // If not, the surface is probably a framebuffer
    if (!IsPow2(width) || !IsPow2(height)) {
        LOG_WARNING(Render, "Not dumping {:016X} because size isn't a power of 2 ({}x{})",
                    data_hash, width, height);
        return;
    }

    // Allocate a temporary buffer for the thread to use
    const u32 decoded_size = width * height * 4;
    std::vector<u8> pixels(data_size + decoded_size);
    std::memcpy(pixels.data(), data.data(), data_size);

    // Proceed with the dump.
    const u64 program_id = system.Kernel().GetCurrentProcess()->codeset->program_id;
    auto dump = [this, width, height, params, data_hash, level, format, data_size, decoded_size,
                 program_id, pixels = std::move(pixels)]() mutable {
        // Decode and convert to RGBA8.
        const std::span encoded = std::span{pixels}.first(data_size);
        const std::span decoded = std::span{pixels}.last(decoded_size);
        DecodeTexture(params, params.addr, params.end, encoded, decoded,
                      params.type == SurfaceType::Color);
        Common::FlipRGBA8Texture(decoded, width, height);

        std::string dump_path = fmt::format(
            "{}textures/{:016X}/", FileUtil::GetUserPath(FileUtil::UserPath::DumpDir), program_id);
        if (!FileUtil::CreateFullPath(dump_path)) {
            LOG_ERROR(Render, "Unable to create {}", dump_path);
            return;
        }

        dump_path +=
            fmt::format("tex1_{}x{}_{:016X}_{}_mip{}.png", width, height, data_hash, format, level);
        image_interface.EncodePNG(dump_path, decoded, width, height);
    };

    if (!workers) {
        CreateWorkers();
    }

    workers->QueueWork(std::move(dump));
    dumped_textures.insert(data_hash);
}

CustomTexture* CustomTexManager::GetTexture(u64 data_hash) {
    const auto it = custom_texture_map.find(data_hash);
    if (it == custom_texture_map.end()) {
        LOG_WARNING(Render, "Unable to find replacement for surface with hash {:016X}", data_hash);
        return nullptr;
    }

    CustomTexture* texture = it->second;
    LOG_DEBUG(Render, "Assigning {} to surface with hash {:016X}", texture->path, data_hash);

    return texture;
}

bool CustomTexManager::Decode(CustomTexture* texture, std::function<bool()>&& upload) {
    if (!Settings::values.async_custom_loading.GetValue()) {
        LoadTexture(texture);
        return upload();
    }

    // Don't submit a decode multiple times.
    if (texture->IsNone()) {
        texture->state = DecodeState::Pending;
        workers->QueueWork([this, texture] { LoadTexture(texture); });
    }

    // Queue the upload for later processing.
    async_uploads.push_back({
        .texture = texture,
        .func = std::move(upload),
    });

    return false;
}

void CustomTexManager::LoadTexture(CustomTexture* texture) {
    if (texture->IsDecoded()) {
        return;
    }

    MICROPROFILE_SCOPE(CustomTexManager_ComputeHash);

    FileUtil::IOFile file{texture->path, "rb"};
    const size_t read_size = file.GetSize();
    std::vector<u8> in(read_size);
    if (file.ReadBytes(in.data(), read_size) != read_size) {
        LOG_CRITICAL(Render, "Failed to open {}", texture->path);
    }

    switch (texture->file_format) {
    case CustomFileFormat::PNG: {
        if (!image_interface.DecodePNG(in, texture->data, texture->width, texture->height)) {
            LOG_ERROR(Render, "Failed to decode png {}", texture->path);
        }
        if (flip_png_files) {
            Common::FlipRGBA8Texture(texture->data, texture->width, texture->height);
        }
        texture->format = CustomPixelFormat::RGBA8;
        break;
    }
    case CustomFileFormat::DDS:
    case CustomFileFormat::KTX: {
        // Compressed formats don't need CPU decoding and must be pre-flipped.
        ddsktx_format format{};
        image_interface.DecodeDDS(in, texture->data, texture->width, texture->height, format);
        texture->format = ToCustomPixelFormat(format);
        break;
    }
    default:
        LOG_ERROR(Render, "Unknown file format {}", texture->file_format);
        return;
    }
    texture->state = DecodeState::Decoded;
}

void CustomTexManager::ReadConfig(const std::string& load_path) {
    const std::string config_path = load_path + "pack.ini";
    Common::INIReader reader{config_path};
    if (!reader.IsOpen()) {
        LOG_INFO(Render, "Unable to find pack config file, using legacy defaults");
        refuse_dds = true;
        return;
    }

    // Read config options
    skip_mipmap = reader.GetBoolean("Options", "skip_mipmap", false);
    if (skip_mipmap) {
        LOG_WARNING(Render, "Skip mipmap option is enabled, pack is considered legacy!");
        refuse_dds = true;
    }
    flip_png_files = reader.GetBoolean("Options", "flip_png_files", false);
    use_new_hash = reader.GetBoolean("Options", "use_new_hash", true);
    if (!use_new_hash) {
        LOG_WARNING(Render, "Legacy hash is used, pack is considered legacy!");
        refuse_dds = true;
    }

    // Read any hash mappings
    auto& hashes = reader.Get("Hashes");
    for (const auto& [key, file] : hashes) {
        size_t idx{};
        const u64 hash = std::stoull(key, &idx, 16);
        if (!idx) {
            LOG_ERROR(Render, "Key {} mapping to file {} is invalid, skipping", key, file);
            continue;
        }
        const std::string filename{FileUtil::GetFilename(file)};
        auto [it, new_hash] = path_to_hash_map.try_emplace(filename);
        if (!new_hash) {
            LOG_ERROR(Render,
                      "File {} with key {} already exists and is mapped to {:#016X}, skipping",
                      file, key, path_to_hash_map[filename]);
            continue;
        }
        it->second = hash;
    }
}

void CustomTexManager::CreateWorkers() {
    const std::size_t num_workers = std::max(std::thread::hardware_concurrency(), 2U) - 1;
    workers = std::make_unique<Common::ThreadWorker>(num_workers, "Custom textures");
}

} // namespace VideoCore
