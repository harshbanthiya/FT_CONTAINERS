/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:35:18 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/12/12 11:38:41 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
    template <typename InputIterator1, typename InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false ;
            ++first1, ++first2;
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1, ++first2;
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1, ++first2;
        }
        return (first2 != last2);
    }

    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1 < *first2))
                return true;
            ++first1, ++first2;
        }
        return (first2 != last2);
    }

    template <typename T>
    const T& min(const T& x, const T& y) {return ((x < y) ? x : y);}
}

#endif