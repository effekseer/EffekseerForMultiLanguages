add_library(EffekseerCore STATIC
  EffekseerBackendCore.h
  EffekseerBackendCore.cpp
  EffekseerEffectCore.h
  EffekseerEffectCore.cpp
  EffekseerManagerCore.h
  EffekseerManagerCore.cpp)

target_compile_features(EffekseerCore PUBLIC cxx_std_17)
target_include_directories(EffekseerCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(required_renderers EffekseerRendererGL)
if(WIN32)
  list(APPEND required_renderers EffekseerRendererDX9 EffekseerRendererDX11)
endif()
foreach(renderer IN LISTS required_renderers)
  if(NOT TARGET ${renderer})
    message(FATAL_ERROR "The bindings require ${renderer}. Enable its upstream BUILD option.")
  endif()
endforeach()

# Renderer targets propagate the Effekseer headers and link dependencies.
target_link_libraries(EffekseerCore PUBLIC Effekseer ${required_renderers})
if(NOT WIN32)
  find_package(OpenGL REQUIRED)
  # OpenGL must follow the renderer archive when linking with --as-needed.
  target_link_libraries(EffekseerRendererGL PUBLIC OpenGL::GL)
endif()
