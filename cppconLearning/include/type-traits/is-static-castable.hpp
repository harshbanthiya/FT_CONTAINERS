#pragma once

#include "integral_constant.hpp"
#include "../utility/decval.hpp"

namespace ft
{
    template <class T, class U, class Enable>   struct is_static_castable_impl                                                      : false_type {};
    template <class T, class U>                 struct is_static_castable_impl<T, U, decltype(void(static_cast<U>(declval<T>())))>  : true_type {};

    template <typename From, typename To>
    struct is_static_castable : public is_static_castable_impl<From, To, void>::type {};

    template <typename From, typename To>
    inline constexpr bool is_static_castable_v = is_static_castable<From, To>::value;
}


