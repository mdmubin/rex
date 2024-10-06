#pragma once

namespace rex {

/// @brief Marks that the value being iterated over can be written to.
struct output_iterator_tag {};

/// @brief Marks that the value being iterated over can be read from.
struct input_iterator_tag {};

/// @brief Marks that the iterator may be incremented.
struct forward_iterator_tag : input_iterator_tag {};

/// @brief Marks that the iterator may be both incremented and decremented.
struct bidirectional_iterator_tag : forward_iterator_tag {};

/// @brief Marks that the iterator may be moved to any value in constant time.
struct random_access_iterator_tag : bidirectional_iterator_tag {};

} // namespace rex