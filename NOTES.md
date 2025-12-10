## Conan Install
```shell
# CLANG (works)
conan install . -of build-clang --build=missing -s compiler=clang -s compiler.version=20 -s compiler.runtime_type=Release -s compiler.cppstd=23 -c tools.cmake.cmaketoolchain:generator=Ninja -c tools.compilation:verbosity=verbose
# Configure: use CMake tools, use `conan-release` auto-generated preset
# Build: use CMake tools, use `conan-release` auto-generated preset

# MSVC (works)
conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=static -s compiler.cppstd=23 -c tools.compilation:verbosity=verbose
# Configure: use CMake tools, use `msvc` preset
# Build: use CMake tools, use `msvc-release` preset

# GCC (doesn't wark)
conan install . -of build-gcc --build=missing -s compiler=gcc -s compiler.version=15 -s compiler.libcxx=libstdc++ -s compiler.cppstd=23 -c tools.compilation:verbosity=verbose 
cmake -B build-gcc -G "MinGW Makefiles" -D CMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -D CMAKE_BUILD_TYPE=Release
cmake --build build-gcc
```