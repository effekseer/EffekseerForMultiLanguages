
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
    EffekseerCore
  )
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
    EffekseerCore
    ${PYTHON_LIBRARIES}
  )

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

