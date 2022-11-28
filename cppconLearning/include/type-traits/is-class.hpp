#pragma once 

#include "compiler_magic.hpp"
#include "integral_constant.hpp"
#include "priority_tag.hpp"

namespace ft
{
    template <typename T, typename = int T::*>
    auto is_class_impl(priority_tag<1>) -> bool_constant<!is_union_v<T>>;

    template<typename T>
    auto is_class_impl(priority_tag<0>) -> false_type;

    template <class T> struct is_class : decltype(is_class_impl<T>(priority_tag<1>())) {};
    template <class T> inline constexpr bool is_class_v = is_class<T>::value;
}