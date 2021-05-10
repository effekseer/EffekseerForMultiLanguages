
cmake_minimum_required(VERSION 3.15)

project(EffekseerCore CXX)

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

add_dependencies(EffekseerCore Effekseer EffekseerRendererGL)

target_compile_features(EffekseerCore PUBLIC cxx_std_14)