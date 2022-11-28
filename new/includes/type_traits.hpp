/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:43:24 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/11/28 11:06:14 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

#include <cstddef>

#define FT_NOEXCEPT throw()

namespace ft
{
    template <typename Type, Type V>
    struct integral_constant
    {
        static const Type value = V;

        typedef Type               value_type;
        typedef integral_constant   type;

        operator value_type() const FT_NOEXCEPT {return V;}
        const value_type operator() () const FT_NOEXCEPT {return V;}
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <bool, typename T = void>
    struct enable_if{};

    template <typename T>
    struct enable_if<true, T> {typedef T type;};

    template <typename T>
    struct _remove_cv {typedef T type;};

    template <typename T>
    struct _remove_cv<const T> {typedef T type;};

    template <typename T>
    struct _remove_cv<volatile T> {typedef T type;};

    template <typename T>
    struct _remove_cv<const volatile T> {typedef T type;};

    template <typename T>
    struct remove_cv {typedef typename _remove_cv<T>::type type;};

    template <class T>  struct _is_integral                        : false_type {};
    template <>         struct _is_integral<bool>                  : true_type {};
    template <>         struct _is_integral<char>                  : true_type {};
    template <>         struct _is_integral<signed char>           : true_type {};
    template <>         struct _is_integral<unsigned char>         : true_type {};
    template <>         struct _is_integral<wchar_t>               : true_type {};
    template <>         struct _is_integral<char16_t>              : true_type {};
    template <>         struct _is_integral<char32_t>              : true_type {};
    template <>         struct _is_integral<short>                 : true_type {};
    template <>         struct _is_integral<unsigned short>        : true_type {};
    template <>         struct _is_integral<int>                   : true_type {};
    template <>         struct _is_integral<unsigned int>          : true_type {};
    template <>         struct _is_integral<long>                  : true_type {};
    template <>         struct _is_integral<unsigned long>         : true_type {};
    template <>         struct _is_integral<long long>             : true_type {};
    template <>         struct _is_integral<unsigned long long>    : true_type {};

    template <typename T>
    struct is_integral : _is_integral<typename remove_cv<T>::type> {};
    
    template <typename T, typename U>
    struct is_same : false_type {};

    template <typename T>
    struct is_same<T, T> : true_type {};

    template <typename>
    struct void_t {typedef void type;};
    
}

#endif 