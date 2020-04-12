
cmake_minimum_required(VERSION 3.15)

project(EffekseerCore CXX)

add_library(
  EffekseerCore
  STATIC
  EffekseerBackendCore.cpp
  EffekseerEffectCore.cpp
  EffekseerManagerCore.cpp)

target_include_directories(
  EffekseerCore
  PUBLIC
  ../Effekseer/Dev/Cpp/Effekseer/
  ../Effekseer/Dev/Cpp/EffekseerRendererGL/
)