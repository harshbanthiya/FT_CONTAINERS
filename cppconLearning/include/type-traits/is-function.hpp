#pragma once 

#include "integral_constant.hpp"
#include "is-foo.hpp"

namespace ft
{
    template <class T> struct is_non_abominable_function : false_type {};
    template <class R, class... A> struct is_non_abominable_function<R(A...)> : true_type {};
    template <class R, class... A> struct is_non_abominable_function<R(A..., ...)> : true_type {};
    template <class T> inline constexpr bool is_non_abominable_function_v = is_non_abominable_function<T>::value;

    template <typename T> inline constexpr bool is_function_v = !is_const_v<const T> && !is_reference_v<T>;
    template <typename T> struct is_function : bool_constant<is_function_v<T>> {};

    template <class T> inline constexpr bool is_abominable_function_v = is_function_v<T> && !is_non_abominable_function_v<T>;
    template <class T> struct is_abominable_function : bool_constant<is_abominable_function_v<T>> {};

    template <typename T> inline constexpr bool is_member_function_pointer_v = is_member_pointer_v<T> && is_function_v<remove_pointer_t<T>>; 
    template <typename T> struct is_member_function_pointer : bool_constant<is_member_function_pointer_v<T>> {};

    template <typename T> inline constexpr bool is_member_object_pointer_v = is_member_pointer_v<T> && !is_function_v<remove_pointer_t<T>>; 
    template <typename T> struct is_member_object_pointer : bool_constant<is_member_object_pointer_v<T>> {};

    template <typename T> inline constexpr bool is_referencable_v = is_object_v<T> || is_non_abominable_function_v<T> || is_reference_v<T>;
    template <typename T> struct is_refereneable : bool_constant<is_referencable_v<T>> {};
    

}

/*
    Function types and reference types are the only C++ types which are not affected by the 'const' qualifier
    if "!is_const_v<const T>" and "T" is not a reference type, then T must be a function type

    is_abominable_function, is_non_abominable_function
    ___________________________________________________

    Most day to day functions are of the type ‘Ret(Args..)‘
    However that doesnt include C style voradic functions like printf type ‘Ret(Args.., ...)‘

    There is also the a family of functions called abominable function types 
        - these are the functions that you get by taking a pointer-to-qualifier-member-function 
            such as void (MyClass::*)(int) const and without the pointer void (int) const
        
        - for each normal function type (like void(int)) there are 11 abominable function types:
            - void (int) const
            - void (int) volatile
            - void (int) const volatile
            - void (int) & 
            - void (int) const &
            - void (int) volatile &
            - void (int) const volatile &
            - void (int) &&
            - void (int) const &&
            - void (int) volatile &&
            - void (int) const volatile &&

    The standard does not supply a type trait for "abominable" function types, but 'add_pointer<T>' needs to
    detect when 'T' is an abominable function type and refrain from adding '*' in that case 

    is_referencable
    __________________

    Standard defines "referancable type" as "an object type 
        and a function type that does not have cv qualifiers or ref qualifiers [ A non abominable function type], 
        or a reference type" Again no trait is provided for this by the Standard

*/