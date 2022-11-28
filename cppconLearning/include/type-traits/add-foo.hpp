#pragma once 

#include "remove-foo.hpp"

namespace ft
{
    template <class T, class Enable>    struct  add_lvalue_reference_impl                               {using type = T;};
    template <class T>                  struct  add_lvalue_reference_impl<T, remove_reference_t<T&>>    {using type = T&;};

    template <class T, class Enable>    struct  add_pointer_impl                                        {using type = T;};
    template <class T, class Enable>    struct  add_pointer_impl<T, remove_pointer_t<T*>>               {using type = T*;};

    template <class T, class Enable>    struct  add_rvalue_reference_impl                               {using type = T;};
    template <class T, class Enable>    struct  add_rvalue_reference_impl<T, remove_reference_t<T&>>    {using type = T&&;};


    template <class T> struct add_const             {using type = const T;};
    template <class T> struct add_cv                {using type = const volatile T;};
    template <class T> struct add_lvalue_reference  : add_lvalue_reference_impl<T, remove_reference_t<T>> {};
    template <class T> struct add_pointer           : add_pointer_impl<remove_reference_t<T>, remove_reference_t<T>> {};
    template <class T> struct add_rvalue_reference  : add_rvalue_reference_impl<T, remove_reference_t<T>> {};
    template <class T> struct add_volatile          : {using type = volatile T;};

    template <class T> using add_const_t = typename add_const<T>::type;
    template <class T> using add_cv_t = typename add_cv<T>::type;
    template <class T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
    template <class T> using add_pointer_t = typename add_pointer<T>::type;
    template <class T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
    template <class T> using add_volatile_t = typename add_volatile<T>::type;
}

/*
    add_foo<T> & remove_foo<T> type traits 
    generally are the format " add a qualifier to 'T', unless the resulting construct would be forbidden by the language"
    in which case leave 'T' alone. 

    We can express this idea in a straightforward manner via SFINAE ; we just get into a SFINAE context
    and try matching 'T' against 'remove_foo_t<foo T>' 

    However in cases of 'add_const, add_volatile and add_cv'; we dont even need to apply SFINAE
    Because the language permits adding those qualifiers to all types, even when the result is just 'T' again
    For example : int& const is same type as int&

*/