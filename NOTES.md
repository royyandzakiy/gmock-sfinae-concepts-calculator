## Conan Install
```shell
# CLANG
conan install . -of build-clang --build=missing -s compiler=clang -s compiler.version=20 -s compiler.runtime_type=Release -s compiler.cppstd=23 -c tools.cmake.cmaketoolchain:generator="Ninja" -s build_type=Debug
# Configure: use CMake tools, use `conan-release` auto-generated preset
# Build: use CMake tools, use `conan-release` auto-generated preset
cmake -B build-clang -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build-clang --parallel 20
build-clang\src\myapp.exe
build-clang\test\unit_tests.exe

# MSVC
conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=static -s compiler.cppstd=23 -s tools.cmake.cmaketoolchain:generator="Visual Studio 17 2022" -s build_type=Debug
# Configure: use CMake tools, use `msvc` preset
# Build: use CMake tools, use `msvc-release` preset
cmake -B build-msvc -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build-msvc --parallel 20
build-msvc\src\Debug\myapp.exe
build-msvc\test\Debug\unit_tests.exe

# GCC
conan install . -of build-gcc --build=missing -s compiler=gcc -s compiler.version=15 -s compiler.libcxx=libstdc++ -s compiler.cppstd=23 -s tools.cmake.cmaketoolchain:generator="MinGW Makefiles" -s build_type=Debug
# Configure: use CMake tools, use `conan-release` auto-generated preset
# Build: use CMake tools, use `conan-release` auto-generated preset
cmake -B build-gcc -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build-gcc --parallel 20
build-gcc\src\myapp.exe
build-gcc\test\unit_tests.exe
```