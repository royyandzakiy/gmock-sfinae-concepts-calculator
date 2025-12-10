cmake_minimum_required(VERSION 3.28..3.31)

# =============================================================================
# Compiler Configuration
# =============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_policy(SET CMP0091 NEW)

# =============================================================================
# Conan Pre-configure
# =============================================================================
# include(cmake/conan-preconfigure.cmake)

# =============================================================================
# Project Configuration
# =============================================================================
project(cmake_project_template 
    LANGUAGES CXX
    VERSION 1.0.0
)

if(MSVC)
    add_compile_options(/W4 /permissive-)
    # add_compile_options(/WX) # more strict
else()
    # Clang/GCC
    add_compile_options(-Wall -Wextra)
    # add_compile_options(-Werror -pedantic) # more strict
endif()

# =============================================================================
# Dependencies
# =============================================================================
# find_package(fmt REQUIRED)

# =============================================================================
# Main Executable
# =============================================================================
add_subdirectory(src)

# Tests (built only when enabled)
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)