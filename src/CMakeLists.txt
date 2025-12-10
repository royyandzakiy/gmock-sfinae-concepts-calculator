# Library
add_library(templib STATIC
    templib/calculator.cpp
)
target_include_directories(templib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/templib")

# Executable
add_executable(myapp
    main.cpp
)

target_link_libraries(myapp PRIVATE templib)