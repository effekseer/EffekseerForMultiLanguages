add_subdirectory(Effekseer)
add_subdirectory(Core)

function(add_effekseer_binding target language)
  set(wrapper "${CMAKE_CURRENT_SOURCE_DIR}/${language}/dll.cpp")
  if(NOT EXISTS "${wrapper}")
    message(FATAL_ERROR "Missing ${wrapper}. Run src/generate_swig_wrapper.bat or .sh before configuring.")
  endif()
  add_library(${target} SHARED "${wrapper}")
  target_link_libraries(${target} PRIVATE EffekseerCore)
endfunction()

if(EFFEKSEER_BUILD_JAVA)
  # Java loads this library. Only JNI headers are consumed; AWT is not used,
  # and the library must not link to a particular JVM installation.
  find_package(JNI REQUIRED COMPONENTS JVM)
  add_effekseer_binding(EffekseerNativeForJava java)
  target_link_libraries(EffekseerNativeForJava PRIVATE JNI::JNI)
endif()

if(EFFEKSEER_BUILD_PYTHON)
  # Prefer the interpreter selected on PATH, including actions/setup-python.
  if(NOT DEFINED Python3_FIND_REGISTRY)
    set(Python3_FIND_REGISTRY LAST)
  endif()
  find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
  add_effekseer_binding(EffekseerNativeForPython python)
  target_link_libraries(EffekseerNativeForPython PRIVATE Python3::Module)
endif()

if(EFFEKSEER_BUILD_CSHARP)
  add_effekseer_binding(EffekseerNativeForCSharp csharp)
endif()

# Python extensions resolve Python API symbols from the hosting interpreter
# on Unix. Java and C# libraries must resolve all symbols at link time.
if(UNIX AND NOT APPLE)
  foreach(binding EffekseerNativeForJava EffekseerNativeForCSharp)
    if(TARGET ${binding})
      target_link_options(${binding} PRIVATE "LINKER:--no-undefined")
    endif()
  endforeach()
endif()
