#pragma once

#include "../algorithm/iterator-tags.hpp"
#include "iterator-traits.hpp"
#include "../type-traits/enable-if.hpp"
#include "../type-traits/integral_constant.hpp"
#include "../type-traits/is_convertible.hpp"

namespace ft
{
    template <class It, class Tag, class> struct is_iterator_impl : false_type{};
    template <class It, class Tag>        struct is_iterator_impl<It, Tag, enable_if_t<is_convertible_v<iterator_category_t<It>, Tag>>>    : true_type{};

    template <class It> struct is_input_iterator : is_iterator_impl<It, input_iterator_tag, void> {};
    template <class It> struct is_output_iterator : is_iterator_impl<It, output_iterator_tag, void> {};
    template <class It> struct is_forward_iterator : is_iterator_impl<It, forward_iterator_tag, void> {};
    template <class It> struct is_bidirectional_iterator : is_iterator_impl<It, bidirectional_iterator_tag, void> {};
    template <class It> struct is_random_access_iterator : is_iterator_impl<It, random_access_iterator_tag, void> {};

    template <class It> inline constexpr bool is_input_iterator_v = is_input_iterator<It>::value;
    template <class It> inline constexpr bool is_output_iterator_v = is_output_iterator<It>::value;
    template <class It> inline constexpr bool is_forward_iterator_v = is_forward_iterator<It>::value;
    template <class It> inline constexpr bool is_bidirectional_iterator_v = is_bidirectional_iterator<It>::value;
    template <class It> inline constexpr bool is_random_access_iterator_v = is_random_access_iterator<It>::value;

    template <class It> inline constexpr bool is_iterator_v = is_input_iterator_v<It> || is_output_iterator_v<It>;
    template <class It> struct is_iterator : bool_constant<is_iterator_v<It>> {};

}