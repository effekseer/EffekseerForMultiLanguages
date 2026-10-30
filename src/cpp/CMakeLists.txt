
project(cpp)

set(BUILD_EXAMPLES OFF)
add_subdirectory(Effekseer)
add_subdirectory(Core)

add_library(EffekseerNativeForJava
  SHARED
  java/dll.cpp
)

find_package(JNI REQUIRED)

if(${JNI_FOUND})
  target_include_directories(
    EffekseerNativeForJava
    PRIVATE
    Effekseer/Dev/Cpp/Effekseer/
    Effekseer/Dev/Cpp/EffekseerRendererGL/
    ${JNI_INCLUDE_DIRS}
  )

  target_link_libraries(EffekseerNativeForJava
    PRIVATE
    EffekseerCore
  )
  target_compile_features(EffekseerNativeForJava PUBLIC cxx_std_17)
endif()

# Prefer the Python selected on PATH (including actions/setup-python).
set(Python3_FIND_REGISTRY LAST)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

  add_library(EffekseerNativeForPython
      SHARED
      python/dll.cpp
  )

  target_include_directories(
    EffekseerNativeForPython
    PRIVATE
    Effekseer/Dev/Cpp/Effekseer/
    Effekseer/Dev/Cpp/EffekseerRendererGL/
    ${Python3_INCLUDE_DIRS}
  )

  target_link_libraries(EffekseerNativeForPython
    PRIVATE
    EffekseerCore
    Python3::Python
  )

target_compile_features(EffekseerNativeForPython PUBLIC cxx_std_17)

add_library(EffekseerNativeForCSharp
  SHARED
  csharp/dll.cpp
)

target_link_libraries(EffekseerNativeForCSharp
  PRIVATE
  EffekseerCore
)

target_include_directories(
  EffekseerNativeForCSharp
  PRIVATE
  Effekseer/Dev/Cpp/Effekseer/
  Effekseer/Dev/Cpp/EffekseerRendererGL/
)

target_compile_features(EffekseerNativeForCSharp PUBLIC cxx_std_17)


# Fail at link time instead of shipping libraries that fail to load on Linux.
if(UNIX AND NOT APPLE)
  foreach(binding EffekseerNativeForJava EffekseerNativeForPython EffekseerNativeForCSharp)
    target_link_options(${binding} PRIVATE "LINKER:--no-undefined")
  endforeach()
endif()
