// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

//? #version 430 core

layout(location = 0) in vec2 tex_coord;
layout(location = 0) out vec4 frag_color;

layout(binding = 0) uniform sampler2D depth;
layout(binding = 1) uniform usampler2D stencil;

void main() {
    vec2 coord = tex_coord * vec2(textureSize(depth, 0));
    ivec2 tex_icoord = ivec2(coord);
    uint depth_val =
        uint(texelFetch(depth, tex_icoord, 0).x * (exp2(32.0) - 1.0));
    uint stencil_val = texelFetch(stencil, tex_icoord, 0).x;
    uvec4 components =
        uvec4(stencil_val, (uvec3(depth_val) >> uvec3(24u, 16u, 8u)) & 0x000000FFu);
    frag_color = vec4(components) / (exp2(8.0) - 1.0);
}
