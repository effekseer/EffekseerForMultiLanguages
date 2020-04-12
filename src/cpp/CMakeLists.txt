
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
    ${JNI_INCLUDE_DIRS}
  )

  target_link_libraries(EffekseerNativeForJava
    PRIVATE
    Effekseer
    EffekseerRendererGL
    EffekseerCore
  )
endif()

