
cmake_minimum_required(VERSION 3.15)

project(EffekseerCore C CXX)

FIND_PACKAGE(Threads REQUIRED)

add_library(
  EffekseerCore
  STATIC
  EffekseerBackendCore.h
  EffekseerBackendCore.cpp
  EffekseerEffectCore.h
  EffekseerEffectCore.cpp
  EffekseerManagerCore.h
  EffekseerManagerCore.cpp)

target_include_directories(
  EffekseerCore
  PUBLIC
  ../Effekseer/Dev/Cpp/Effekseer/
  ../Effekseer/Dev/Cpp/EffekseerRendererGL/
)

target_link_libraries(Effekseer PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(EffekseerRendererGL PUBLIC Effekseer)

target_compile_features(EffekseerCore PUBLIC cxx_std_14)

if(NOT WIN32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(
    EffekseerCore
    PUBLIC
      ${OPENGL_LIBRARIES}
      Effekseer
      EffekseerRendererGL
  )
endif()
