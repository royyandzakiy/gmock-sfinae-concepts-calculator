### Conan Install
```shell
# success
conan install . -of build-clang --build=missing -s compiler=clang -s compiler.version=20 -s compiler.runtime_type=Release -s compiler.cppstd=23 -c tools.cmake.cmaketoolchain:generator=Ninja -c tools.compilation:verbosity=verbose
cmake --preset=conan-release
cmake --build --preset=conan-release

# fail
conan install . -of build-gcc --build=missing -s compiler=gcc -s compiler.version=15 -s compiler.libcxx=libstdc++ -s compiler.cppstd=23 -c tools.compilation:verbosity=verbose
cmake -B build-gcc
cmake --build build-gcc

conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=dynamic -s compiler.cppstd=23 -c tools.compilation:verbosity=verbose
cmake -B build-msvc
cmake --build build-msvc
```