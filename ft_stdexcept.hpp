/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdexcept.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:02:31 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/11/10 14:16:47 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDEXCEPT_HPP
#define FT_STDEXCEPT_HPP

#include <stdexcept>
#include <cassert>

namespace ft
{
    #define FT_STL_DEBUG(expr) \
        (assert(expr))

    #define THROW_LENGTH_ERROR_IF(expr, what) \
        if ((expr)) throw std::length_error(what)
    #define THROW_OUT_OF_RANGE_IF(expr, what) \
        if ((expr)) throw std::out_of_range(what)
    #define THROW_RUNTIME_ERROR_IF(expr, what) \
        if ((expr)) throw std:runtime_error(what)
}

#endif