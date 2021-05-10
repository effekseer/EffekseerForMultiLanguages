
project(cpp)

set(BUILD_EXAMPLES OFF)
add_subdirectory(Effekseer)
add_subdirectory(Core)

add_library(EffekseerNativeForJava
  SHARED
  java/dll.cpp
)

find_package(JNI)

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
    Effekseer
    EffekseerRendererGL
    EffekseerCore
  )
  target_compile_features(EffekseerNativeForJava PRIVATE cxx_std_14)
endif()




find_package(PythonLibs)

  add_library(EffekseerNativeForPython
      SHARED
      python/dll.cpp
  )

  target_include_directories(
    EffekseerNativeForPython
    PRIVATE
    Effekseer/Dev/Cpp/Effekseer/
    Effekseer/Dev/Cpp/EffekseerRendererGL/
    ${PYTHON_INCLUDE_DIRS}
  )

  target_link_libraries(EffekseerNativeForPython
    PRIVATE
    Effekseer
    EffekseerRendererGL
    EffekseerCore
    ${PYTHON_LIBRARIES}
  )
  target_compile_features(EffekseerNativeForPython PRIVATE cxx_std_14)

add_library(EffekseerNativeForCSharp
  SHARED
  csharp/dll.cpp
)

target_link_libraries(EffekseerNativeForCSharp
  PRIVATE
  Effekseer
  EffekseerRendererGL
  EffekseerCore
)

target_include_directories(
  EffekseerNativeForCSharp
  PRIVATE
  Effekseer/Dev/Cpp/Effekseer/
  Effekseer/Dev/Cpp/EffekseerRendererGL/
)

target_compile_features(EffekseerNativeForCShar PRIVATE cxx_std_14)
