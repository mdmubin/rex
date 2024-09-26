#pragma once

#include "rex/traits/conditional.hpp"
#include "rex/traits/extent.hpp"
#include "rex/traits/is_array.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_function.hpp"
#include "rex/traits/is_pointer.hpp"
#include "rex/traits/is_reference.hpp"

namespace rex {

template <typename t>
struct decay {
    using noref = remove_reference_t<t>;
    using type  = conditional_t
    <
        is_array_v<noref>,
        add_pointer_t<remove_extent_t<noref>>,
        conditional_t
        <
            is_function_v<noref>,
            add_pointer_t<noref>,
            remove_cv_t<noref>
        >
    >;
};

/// @brief An alias to a type that is a result of decay operations on `t`.
template <typename t> using decay_t = typename decay<t>::type;

} // namespace rex