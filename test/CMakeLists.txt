# =============================================================================
# Dependencies
# =============================================================================
find_package(GTest REQUIRED)

# =============================================================================
# Main Executable
# =============================================================================
add_executable(unit_tests
	test_inherit_calculator.cpp
    test_concept_calculator.cpp
    test_sfinae_calculator.cpp
    test_main.cpp
)

target_link_libraries(unit_tests
    PRIVATE 
        conceptlib 
        inheritlib 
        sfinaelib 
        GTest::gmock
        GTest::gtest # alt: "GTest::gtest_main", beware, fails to find tests with msvc
)

# =============================================================================
# Custom GoogleTest cmake function to auto detect tests
# =============================================================================
include(GoogleTest)
gtest_discover_tests(unit_tests)