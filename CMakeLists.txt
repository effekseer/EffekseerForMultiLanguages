cmake_minimum_required(VERSION 3.24)

# Match the minimum supported by the bundled Effekseer runtime.
if(APPLE AND NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0" CACHE STRING "Minimum macOS deployment version")
endif()

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" EFFEKSEER_RELEASE_VERSION LIMIT_COUNT 1)
project(EffekseerForMultiLanguages VERSION ${EFFEKSEER_RELEASE_VERSION} LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(EFFEKSEER_BUILD_JAVA "Build Java native bindings" ON)
option(EFFEKSEER_BUILD_PYTHON "Build Python native bindings" ON)
option(EFFEKSEER_BUILD_CSHARP "Build C# native bindings" ON)
option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use the shared MSVC runtime (/MD instead of /MT)" OFF)

# The bindings implement OpenGL and, on Windows, DX9/DX11. Do not build
# unrelated editor tools or backends by default. Explicit cache options win.
option(BUILD_EXAMPLES "Build upstream Effekseer examples" OFF)
option(BUILD_TOOLS "Build upstream Effekseer tools" OFF)
option(BUILD_DX12 "Build upstream DirectX 12 renderer" OFF)
option(BUILD_METAL "Build upstream Metal renderer" OFF)

if(MSVC)
  if(USE_MSVC_RUNTIME_LIBRARY_DLL)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()
endif()

add_subdirectory(src)
