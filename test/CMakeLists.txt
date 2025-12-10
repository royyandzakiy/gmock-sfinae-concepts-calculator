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
)

target_link_libraries(unit_tests
    PRIVATE 
        conceptlib 
        inheritlib 
        sfinaelib 
        GTest::gtest_main # alt: create own main, use this "GTest::gtest"
        GTest::gmock
)

# =============================================================================
# Custom GoogleTest cmake function to auto detect tests
# =============================================================================
include(GoogleTest)
gtest_discover_tests(unit_tests)