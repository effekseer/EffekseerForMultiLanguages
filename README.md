## EffekseerForMultiLanguages

Effekseer for C#, Java and Python

### Requirements
- git
- Python 3 with development headers (CI uses Python 3.12)
- C++ compiler
- cmake (3.24 or later)
- swig
- JDK (If you develop it for JVM)
- ant (If you develop it for JVM)

### Build

```
git clone https://github.com/effekseer/EffekseerForMultiLanguages.git
cd EffekseerForMultiLanguages
git submodule update --init
bash .github/scripts/checkout-runtime-submodules.sh
```

#### Windows

```
cd src
generate_swig_wrapper.bat
cd ..
```

#### Mac, Linux

```
cd src
sh generate_swig_wrapper.sh
cd ..
```


```
cmake -B build -S .
cmake --build build --config Release
```

### CMake options

The default build produces C#, Java and Python native libraries. Generate the
SWIG wrappers before configuring. Upstream editor tools, examples, DX12 and
Metal are disabled by default; the bindings use OpenGL and Windows DX9/DX11.
On Windows, run the submodule initialization commands above in Git Bash.

Use `EFFEKSEER_BUILD_JAVA`, `EFFEKSEER_BUILD_PYTHON` and
`EFFEKSEER_BUILD_CSHARP` to select bindings. Disabled bindings do not require
their language SDKs. For example, to build only the C# library:

```sh
cmake -S . -B build-csharp -DEFFEKSEER_BUILD_JAVA=OFF -DEFFEKSEER_BUILD_PYTHON=OFF
cmake --build build-csharp --config Release
```

Set `JAVA_HOME` to the JDK home (the `Contents/Home` directory for a macOS JDK
bundle), or pass `-DJAVA_HOME:PATH="<jdk-home>"` to CMake. Java uses JNI headers
without linking the binding to AWT or the JVM. Python requires the selected
interpreter's extension-module development headers, not an embedding library.
Library names remain `EffekseerNativeForJava`, `EffekseerNativeForPython` and
`EffekseerNativeForCSharp` for compatibility with the packaging scripts.

macOS requires 12.0 or later, matching the bundled runtime. On MSVC,
`USE_MSVC_RUNTIME_LIBRARY_DLL=ON` selects `/MD`; the default is `/MT`.

## How to use

### libGDX

please see examples

#### Windows

call ```python examples/build_libGtxSample.py ```

## How to Develop

### TODO

https://github.com/effekseer/EffekseerForMultiLanguages/issues

### Requeiments

- swig

### Reference

https://github.com/effekseer/EffekseerForWebGL/blob/master/src/cpp/main.cpp
