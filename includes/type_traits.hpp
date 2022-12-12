/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:43:24 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/12/12 13:36:29 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS
# define TYPE_TRAITS

#define FT_NOEXCEPT throw()

namespace ft
{
    template <typename Type, Type V>
    struct integral_constant
    {
        typedef integral_constant<Type, V>      type;
        typedef Type                            value_type;
       
        static const Type value = V;
        
        operator value_type() const FT_NOEXCEPT {return V;}
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

    template <class T>  struct _is_integral                        : public false_type {};
    template <>         struct _is_integral<bool>                  : public true_type {};
    template <>         struct _is_integral<char>                  : public true_type {};
    template <>         struct _is_integral<signed char>           : public true_type {};
    template <>         struct _is_integral<unsigned char>         : public true_type {};
    template <>         struct _is_integral<wchar_t>               : public true_type {};
    template <>         struct _is_integral<short>                 : public true_type {};
    template <>         struct _is_integral<unsigned short>        : public true_type {};
    template <>         struct _is_integral<int>                   : public true_type {};
    template <>         struct _is_integral<unsigned int>          : public true_type {};
    template <>         struct _is_integral<long>                  : public true_type {};
    template <>         struct _is_integral<unsigned long>         : public true_type {};
    template <>         struct _is_integral<long long>             : public true_type {};
    template <>         struct _is_integral<unsigned long long>    : public true_type {};

    template <typename T>
    struct is_integral : public _is_integral<typename remove_cv<T>::type> {};
    
    template <typename T, typename U>
    struct is_same : public false_type {};

    template <typename T>
    struct is_same<T, T> : public true_type {};

    template <typename>
    struct void_t {typedef void type;};
    
}

#endif 