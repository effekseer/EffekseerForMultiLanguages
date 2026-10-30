#!/usr/bin/env bash
set -euo pipefail

# checkout initializes Effekseer without recursing into its dependencies.
# Runtime bindings do not build the Vulkan shader compiler or editor tools.
# Skip only SPIRV-Cross: its test data exceeds Windows checkout path limits.
effekseer=src/cpp/Effekseer
llgi="$effekseer/Dev/Cpp/3rdParty/LLGI"
git -C "$effekseer" submodule update --init Dev/Cpp/3rdParty/LLGI
git -C "$llgi" config submodule.thirdparty/SPIRV-Cross.update none
git submodule update --init --recursive
