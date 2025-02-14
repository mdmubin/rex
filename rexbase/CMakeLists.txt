project(rexbase)

# base directory configurations
set(rex_inc_dir ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(rex_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

# project sources
set(rex_base_inc
    ${rex_inc_dir}/rex/assert.hpp
    ${rex_inc_dir}/rex/atomic.hpp
    ${rex_inc_dir}/rex/config.hpp
    ${rex_inc_dir}/rex/iterator.hpp
    ${rex_inc_dir}/rex/limits.hpp
    ${rex_inc_dir}/rex/types.hpp
    ${rex_inc_dir}/rex/type_traits.hpp
)
set(rex_base_src
    ${rex_src_dir}/assert.cpp
)

# build project sources
add_library(rexbase ${rex_base_src} ${rex_base_inc})

# project include directory configuration
target_include_directories(rexbase PUBLIC  ${rex_inc_dir})
target_include_directories(rexbase PRIVATE ${rex_src_dir})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(rexbase PRIVATE atomic)
endif()