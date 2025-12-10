# Library
add_library(conceptlib STATIC
    conceptlib/calculator.cpp
)
add_library(inheritlib STATIC
	inheritlib/calculator.cpp
)
target_include_directories(conceptlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(inheritlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

# Executable
add_executable(myapp
    main.cpp
)

target_link_libraries(myapp PRIVATE conceptlib inheritlib)