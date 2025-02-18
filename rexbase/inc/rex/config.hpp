#pragma once

/* PLATFORM DETECTION */
#if defined(__linux) || defined(__linux__)
    #define REX_PLATFORM_LINUX 1
    #define REX_PLATFORM_STRING "linux"
#elif defined(_WIN32) || defined(_WIN64)
    #define REX_PLATFORM_WINDOWS 1
    #define REX_PLATFORM_STRING "windows"
#else
    #error unrecognized platform
#endif

/* COMPILER DETECTION */
#if defined(REX_PLATFORM_LINUX)
    #if defined(__clang__)
        #define REX_COMPILER_CLANG 1
        #define REX_COMPILER_STRING "clang"
        #define REX_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
    #elif defined(__GNUC__)
        #define REX_COMPILER_GCC 1
        #define REX_COMPILER_STRING "gcc"
        #define REX_COMPILER_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
    #else
        #error unrecognized compiler.
    #endif
#elif defined(REX_PLATFORM_WINDOWS)
    #if defined(__clang__)
        #define REX_COMPILER_CLANG 1
        #if defined(_MSC_VER)
            #define REX_COMPILER_CLANG_CL 1
            #define REX_COMPILER_STRING "clang-cl"
        #elif defined(__MINGW32__) || defined(__MINGW64__)
            #define REX_COMPILER_MINGW_CLANG 1
            #define REX_COMPILER_STRING "mingw-clang"
        #else
            #define REX_COMPILER_STRING "clang"
        #endif
        #define REX_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
    #elif defined(_MSC_VER)
        #define REX_COMPILER_MSVC 1
        #define REX_COMPILER_STRING "msvc"
        #define REX_COMPILER_VERSION _MSC_VER
    #elif defined(__GNUC__)
        #define REX_COMPILER_GCC 1
        #if defined(__MINGW32__) || defined(__MINGW64__)
            #define REX_COMPILER_MINGW_GCC 1
            #define REX_COMPILER_STRING "mingw-gcc"
        #else
            #define REX_COMPILER_STRING "gcc"
        #endif
        #define REX_COMPILER_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
    #else
        #error unrecognized compiler.
    #endif
#else
    #error cannot determine compiler on unrecognized platform.
#endif

/* ARCHITECTURE DETECTION */
#if defined(REX_PLATFORM_LINUX)
    #if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__)
        #define REX_ARCHITECTURE_X64 1
        #define REX_ARCHITECTURE_STRING "x64"
    #else
        #error unrecognized platform architecture.
    #endif
#elif defined(REX_PLATFORM_WINDOWS)
    #if defined(_M_X64) || defined(_M_AMD64)
        #define REX_ARCHITECTURE_X64 1
        #define REX_ARCHITECTURE_STRING "x64"
    #else
        #error unrecognized platform architecture.
    #endif
#else
    #error cannot determine architecture on unrecognized platform.
#endif

/* DEBUG HELPERS */

#define REX_CURRENT_FILE __FILE__
#define REX_CURRENT_LINE __LINE__
#if defined(REX_COMPILER_MSVC)
    #define REX_CURRENT_FUNC __FUNCSIG__
#else
    #define REX_CURRENT_FUNC __PRETTY_FUNCTION__
#endif

/* HELPER for __has_builtin */
#if defined(__has_builtin)
    #define REX_HAS_BUILTIN(X) __has_builtin(X)
#else
    #define REX_HAS_BUILTIN(X) 0
#endif

/* UNREACHABLE */
#if defined(REX_COMPILER_MSVC)
    #define REX_UNREACHABLE() __assume(false)
#elif REX_HAS_BUILTIN(__builtin_unreachable)
    #define REX_UNREACHABLE() __builtin_unreachable()
#endif

/* MISC. MACROS */

// Concatenate two raw tokens
#define REX_CONCAT(A, B) REX_CONCAT_(A, B)
#define REX_CONCAT_(A, B) A##B

// Convert to a C-style string
#define REX_STRINGIFY(...) REX_STRINGIFY_(__VA_ARGS__)
#define REX_STRINGIFY_(...) #__VA_ARGS__

// Convert to wide char string
#define REX_STRINGIFY_W(...) REX_CONCAT(L, REX_STRINGIFY(__VA_ARGS__))

// Mark a value as unused.
#define REX_UNUSED(X) static_cast<void>(X)