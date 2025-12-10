# Library
add_library(mylib STATIC
    mylib/calculator.cpp
)
target_include_directories(mylib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/mylib")

# Executable
add_executable(myapp
    main.cpp
)

target_link_libraries(myapp PRIVATE mylib)