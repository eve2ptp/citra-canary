// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string_view>

namespace DefaultINI {

constexpr std::string_view pack_config_file = R"(
[Info]
# The name of the pack (without whitespaces)
name =

# The author of the pack (without whitespaces)
author =

[Options]
# When enabled this option will skip mipmap uploads to surfaces, instead generating
# them from the base level. Might result in graphical glitches. It is intended for legacy packs only.
# 0: Off (Default), 1 : On
skip_mipmap =
# Whether to flip png files on upload. Having this option disabled allows the loader to skip
# decode time flipping the files to what the game expects. It is intended for legacy packs only.
# 0: Off (Default), 1 : On
flip_png_files =
# Whether to use the new faster hashing method to calculate the texture hashes. This significantly
# reduces texture loading stutter.
# 0: Off, 1 : On Default
use_new_hash =

# Below section allows to map individual hashes to specific filenames
#[Hashes]
#DBD0A793F2756679 = bottom_screen.png
)";

} // namespace DefaultINI
