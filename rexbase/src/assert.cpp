#include "rex/assert.hpp"
#include <cstdio>
#include <cstdlib>

void rex::assert_fail(cstr cnd, cstr msg, cstr file, cstr func, i32 line)
{
    // NOTE: For now we keep it simple, report error and then abort program. Might add more sophisticated mechanisms for
    // handling this later.
    std::fprintf(stderr, "[FATAL ERROR] Assertion failure! %s\n\tAssert condition: %s\n\tIn file: %s:%d func: %s\n",
                 msg, cnd, file, line, func);
    std::abort();
}