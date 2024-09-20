#pragma once

#include "rex/types.hpp"
#include "rex/config.hpp"

namespace rex
{

/// @brief Reports the assertion failure, and then aborts the program.
/// @param cnd The condition string.
/// @param msg The assertion message.
/// @param file The file in which the assertion failed.
/// @param func The function in which the assertion failed.
/// @param line The line in which the assertion failed.
void assert_fail(cstr cnd, cstr msg, cstr file, cstr func, i32 line);

} // namespace rex

/* ASSERTION MACROS */
#if !defined(REX_DISABLE_ASSERTS) && !defined(NDEBUG)
    #if !defined(REX_USE_C_ASSERT)
        #define REX_ASSERT(cnd)                                                                                        \
            ((cnd) ? static_cast<void>(0)                                                                              \
                   : rex::assert_fail(REX_STRINGIFY(cnd), "", REX_CURRENT_FILE, REX_CURRENT_FUNC, REX_CURRENT_LINE))
        #define REX_ASSERT_MSG(cnd, msg)                                                                               \
            ((cnd) ? static_cast<void>(0)                                                                              \
                   : rex::assert_fail(REX_STRINGIFY(cnd), msg, REX_CURRENT_FILE, REX_CURRENT_FUNC, REX_CURRENT_LINE))
    #else
        #include <cassert>
        #define REX_ASSERT(cnd) assert(cnd)
        #define REX_ASSERT_MSG(cnd, msg) assert(!!(cnd) && (msg))
    #endif
#else
    #define REX_ASSERT(...) static_cast<void>(0)
    #define REX_ASSERT_MSG(...) static_cast<void>(0)
#endif