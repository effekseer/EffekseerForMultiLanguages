## EffekseerForMultiLanguages

Effekseer for C#, Java and Python

### Requirements
- git
- Python 3 with development headers (CI uses Python 3.12)
- C++ compiler
- cmake (3.15 or later)
- swig
- JDK (If you develop it for JVM)
- ant (If you develop it for JVM)

### Build

```
git clone https://github.com/effekseer/EffekseerForMultiLanguages.git
cd EffekseerForMultiLanguages
git submodule update --init --recursive
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
