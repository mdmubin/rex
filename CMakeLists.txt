cmake_minimum_required(VERSION 3.22)

project(librex)

include("cmake/config.cmake")

add_subdirectory(rexbase)

# tests
if (REX_TESTING_ENABLED)
    include("cmake/test-framework.cmake")
    add_subdirectory(testing)
endif()