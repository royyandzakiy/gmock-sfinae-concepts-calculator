# Library
add_library(templatelib STATIC
    templatelib/calculator.cpp
)
add_library(inheritlib STATIC
inheritlib/calculator.cpp
)
target_include_directories(templatelib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/templatelib")
target_include_directories(inheritlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inheritlib")

# Executable
add_executable(myapp
    main.cpp
)

target_link_libraries(myapp PRIVATE templatelib inheritlib)