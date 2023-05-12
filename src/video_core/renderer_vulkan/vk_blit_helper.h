// Copyright 2022 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "video_core/rasterizer_cache/pixel_format.h"
#include "video_core/renderer_vulkan/vk_common.h"

namespace VideoCore {
struct TextureBlit;
}

namespace Vulkan {

class Instance;
class DescriptorManager;
class RenderpassCache;
class Scheduler;
class Surface;

class BlitHelper {
public:
    BlitHelper(const Instance& instance, Scheduler& scheduler, DescriptorManager& desc_manager,
               RenderpassCache& renderpass_cache);
    ~BlitHelper();

    bool BlitDepthStencil(Surface& source, Surface& dest, const VideoCore::TextureBlit& blit);

    bool ConvertDS24S8ToRGBA8(Surface& source, Surface& dest, const VideoCore::TextureBlit& blit);

private:
    /// Creates compute pipelines used for blit
    vk::Pipeline MakeComputePipeline(vk::ShaderModule shader);

    /// Creates graphics pipelines used for blit
    vk::Pipeline MakeDepthStencilBlitPipeline();

private:
    const Instance& instance;
    Scheduler& scheduler;
    DescriptorManager& desc_manager;
    RenderpassCache& renderpass_cache;

    vk::Device device;
    vk::RenderPass r32_renderpass;

    vk::DescriptorSetLayout compute_descriptor_layout;
    vk::DescriptorSetLayout two_textures_descriptor_layout;
    vk::DescriptorUpdateTemplate compute_update_template;
    vk::DescriptorUpdateTemplate two_textures_update_template;
    vk::PipelineLayout compute_pipeline_layout;
    vk::PipelineLayout two_textures_pipeline_layout;

    vk::ShaderModule full_screen_vert;
    vk::ShaderModule copy_d24s8_to_r32_comp;
    vk::ShaderModule d24s8_to_rgba8_comp;
    vk::ShaderModule blit_depth_stencil_frag;

    vk::Pipeline copy_d24s8_to_r32_pipeline;
    vk::Pipeline d24s8_to_rgba8_pipeline;
    vk::Pipeline depth_blit_pipeline;
    vk::Sampler linear_sampler;
    vk::Sampler nearest_sampler;
};

} // namespace Vulkan
