project(rex_tests)

set(rex_base_test_src
    test_types.cpp
    test_assert.cpp
    test_traits.cpp
)
add_executable(rex_tests ${rex_base_test_src})
target_link_libraries(rex_tests PRIVATE rexbase)
target_link_libraries(rex_tests PRIVATE GTest::gtest_main)

# find tests and make available to IDEs
include(GoogleTest)
gtest_discover_tests(rex_tests)