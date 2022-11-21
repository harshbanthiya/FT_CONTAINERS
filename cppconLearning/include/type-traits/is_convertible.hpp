#pragma once

#include "integral_constant.hpp"
#include "is-foo.hpp"
#include "is-function.hpp"
#include "../utility/decval.hpp"

namespace ft 
{   
    template <typename From, typename To, bool = is_void_v<From> || is_function_v<To> || is_array_v<To>>
    struct is_convertible_impl
    {
        using type = bool_constant<is_void_v<To>>;
    };

    template <typename From, typename To>
    class is_convertible_impl<From, To, false>
    {
        template <typename T> static void convertible(T);

        template <typename F, typename = decltype(convertible<To>(declval<F>()))>
        static true_type test(int);

        template<typename>
        static false_type test(...);

        public:
        using type = decltype(test<From>(0));
    };

    template <typename From, typename To>
    struct is_convertible : is_convertible_impl<From, To>::type {};

    template <typename From, typename To>
    inline constexpr bool is_convertible_v = is_convertible<From, To>::value;

}


/*
    The three type traits is_convertible, is_static_castable, is_constructible 

    - is_convertible <A, B>   : A value of type 'A' can be used in a context where a value of type 'B' is expected.
        meaning 'A is implicitly convertible to B'. Generally this becomes true if 
        [ A has a (non-explicit) operator B, ] OR 
        [ B has a (non-explicity) constructor B(A)]  {This is never true for B = void}

    - is_constructible <B, A> : Type B has a constructor that accepts a value of type 'A' as its parameter;
        is other words 'B(std::decval<A>()) is well formed. 
        This becomes true if A has a operator B ( even if it is explicit)
        or if B has as constructor B(A) ( even if it is explicit) 
    
    - is_static_castable<A, B> : this is a non standard type trait
        it just means  is_constructible_v<B, A> && !is_convertible_v<A, B>
        is_static_castable<A, B> is true if static_cast<B>(declval<A>()) is well formed
            which means 
            is_static_castable_v<A*, void*> == true &&
            !is_static_castable_v<void*, A*> == true && 
            is_static_castable_v<A, void> == true 
            
            FOR ALL "A" 


*/