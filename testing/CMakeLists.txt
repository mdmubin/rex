project(rex_tests)

set(rex_base_test_src
    test_assert.cpp
    test_limits.cpp
    test_traits.cpp
    test_types.cpp
)
add_executable(rex_tests ${rex_base_test_src})
target_link_libraries(rex_tests PRIVATE rexbase)
target_link_libraries(rex_tests PRIVATE GTest::gtest_main)

# find tests and make available to IDEs
include(GoogleTest)
gtest_discover_tests(rex_tests)