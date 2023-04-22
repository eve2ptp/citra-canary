// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <atomic>
#include <list>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "common/thread_worker.h"
#include "video_core/rasterizer_cache/pixel_format.h"

namespace Core {
class System;
}

namespace Frontend {
class ImageInterface;
}

namespace VideoCore {

struct StagingData;
class SurfaceParams;
enum class PixelFormat : u32;

enum class CustomFileFormat : u32 {
    PNG = 0,
    DDS = 1,
    KTX = 2,
};

enum class DecodeState : u32 {
    None = 0,
    Pending = 1,
    Decoded = 2,
};

struct CustomTexture {
    u32 width;
    u32 height;
    unsigned long long hash{};
    CustomPixelFormat format;
    CustomFileFormat file_format;
    std::string path;
    std::vector<u8> data;
    std::atomic<DecodeState> state{};

    bool IsPending() const noexcept {
        return state.load(std::memory_order_relaxed) == DecodeState::Pending;
    }

    bool IsDecoded() const noexcept {
        return state.load(std::memory_order_relaxed) == DecodeState::Decoded;
    }

    bool IsNone() const noexcept {
        return state.load(std::memory_order_relaxed) == DecodeState::None;
    }

    explicit operator bool() const noexcept {
        return hash != 0;
    }
};

struct AsyncUpload {
    CustomTexture* texture;
    std::function<bool()> func;
};

class CustomTexManager {
public:
    CustomTexManager(Core::System& system);
    ~CustomTexManager();

    /// Processes queued texture uploads
    void TickFrame();

    /// Searches the load directory assigned to program_id for any custom textures and loads them
    void FindCustomTextures();

    /// Saves the pack configuration file template to the dump directory if it doesn't exist.
    void WriteConfig();

    /// Preloads all registered custom textures
    void PreloadTextures();

    /// Saves the provided pixel data described by params to disk as png
    void DumpTexture(const SurfaceParams& params, u32 level, std::span<u8> data, u64 data_hash);

    /// Returns the custom texture handle assigned to the provided data hash
    CustomTexture* GetTexture(u64 data_hash);

    /// Decodes the data in texture to a consumable format
    bool Decode(CustomTexture* texture, std::function<bool()>&& upload);

    /// True when mipmap uploads should be skipped (legacy packs only)
    bool SkipMipmaps() const noexcept {
        return skip_mipmap;
    }

    /// Returns true if the pack uses the new hashing method.
    bool UseNewHash() const noexcept {
        return use_new_hash;
    }

private:
    /// Loads the texture from file decoding the data if needed
    void LoadTexture(CustomTexture* texture);

    /// Reads the pack configuration file
    void ReadConfig(const std::string& load_path);

    /// Creates the thread workers.
    void CreateWorkers();

private:
    Core::System& system;
    Frontend::ImageInterface& image_interface;
    std::unordered_set<u64> dumped_textures;
    std::unordered_map<u64, CustomTexture*> custom_texture_map;
    std::unordered_map<std::string, u64> path_to_hash_map;
    std::vector<std::unique_ptr<CustomTexture>> custom_textures;
    std::list<AsyncUpload> async_uploads;
    std::unique_ptr<Common::ThreadWorker> workers;
    bool textures_loaded{false};
    bool skip_mipmap{true};
    bool flip_png_files{true};
    bool use_new_hash{false};
    bool refuse_dds{false};
};

} // namespace VideoCore
