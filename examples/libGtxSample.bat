cd /d %~dp0
cd ..
mkdir build
cd build

cmake -D BUILD_DX12=OFF ..
cmake --build . --config Release

copy src\cpp\Release\EffekseerNativeForJava.dll ..\examples\libGdxSample\core\assets\EffekseerNativeForJava.dll

cd /d %~dp0

cd ../src/java/

ant build

copy ..\build_java\Effekseer.jar ..\..\examples\libGdxSample\core\libs\Effekseer.jar
