# config variables
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(rex_test_enabled 1)
    set(rex_main_project 1)
else()
    set(rex_test_enabled 0)
    set(rex_main_project 0)
endif()

option(REX_TESTING_ENABLED "Option for building tests." ${rex_test_enabled})

# set project C++ standard
if(rex_main_project)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_DEBUG_POSTFIX "_dbg")