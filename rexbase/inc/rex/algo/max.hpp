#pragma once

#include <initializer_list>

namespace rex
{

/// @brief Get the greater value between `a` and `b`.
template <typename t>
constexpr const t &max(const t &a, const t &b)
{
    return (a > b) ? a : b;
}

/// @brief Get the greater value between `a` and `b` using the comparison function `cmpFn`.
/// @note `cmpFn(a, b)` is expected to check whether `a` is less than `b`.
template <typename t, typename cmp>
constexpr const t &max(const t &a, const t &b, cmp cmpFn)
{
    return cmpFn(a, b) ? b : a;
}

/// @brief Get the greatest value in the initializer list.
template <typename t>
constexpr t max(std::initializer_list<t> values)
{
    auto maxIter = values.begin();
    for (auto current = values.end(); current != values.end(); ++current)
    {
        if (*maxIter < *current)
        {
            maxIter = current;
        }
    }
    return maxIter;
}

/// @brief Get the greatest value in the initializer list using the comparison function `cmpFn`.
/// @note `cmpFn(a, b)` is expected to check whether `a` is less than `b`.
template <typename t, typename cmp>
constexpr t max(std::initializer_list<t> values, cmp cmpFn)
{
    auto maxIter = values.begin();
    for (auto current = values.begin(); current != values.end(); ++current)
    {
        if (cmpFn(*maxIter, *current))
        {
            maxIter = current;
        }
    }
    return *maxIter;
}

} // namespace rex