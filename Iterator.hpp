/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:50:58 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/11/20 12:31:49 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
    
    // Iterator Traits 
    template <typename iterator>
    struct iterator_traits
    {

        typedef typename iterator::difference_type      difference_type;
        typedef typename iterator::value_type           value_type;
        typedef typename iterator::pointer              pointer;
        typedef typename iterator::reference            reference;
        typedef typename iterator::iterator_category    iterator_category;
    };

    // Iterator Traits for Random Access and Const Random Access 
    
    template <typename T>
    struct iterator_traits< T* >
    {

        typedef  ptrdiff_t                      difference_type;
        typedef  T                              value_type;
        typedef  T*                             pointer;
        typedef  T&                             reference;
        typedef  random_access_iterator_tag     iterator_category;
    };

    template <typename T>
    struct iterator_traits< const T* >
    {

        typedef  ptrdiff_t                      difference_type;
        typedef  T                              value_type;
        typedef  const T*                       pointer;
        typedef  const T&                       reference;
        typedef  random_access_iterator_tag     iterator_category;
    };


    // Base Iterator Class as defined in std 
    template < typename Category, typename T, 
            typename Difference = ptrdiff_t, typename Pointer = T*,
            typename Reference = T& > 
    struct iterator
    {
        typedef T               value_type;
        typedef Difference      difference_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
        typedef Category        iterator_category;
    };

    // We need tags when you want to overload the constructor; 
    // not with different parameters instead with same parameters and different behaviours 

    struct output_iterator_tag {};
    struct input_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag: public forward_iterator_tag {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    // Implementation of Distance on iterators 
    template <typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type __distance(
    _InputIterator __first, _InputIterator __last, ft::input_iterator_tag) 
    {
        typename iterator_traits<_InputIterator>::difference_type d(0);
        for (; __first != __last; ++__first) 
            ++d;
        return d;
    }

    template <typename _RandIterator>
    inline typename iterator_traits<_RandIterator>::difference_type __distance(_RandIterator __first, _RandIterator __last,
    ft::random_access_iterator_tag) 
    {
        return __last - __first;
    }

    template <typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type distance(
    _InputIterator first, _InputIterator last) 
    {
        return ft::__distance(first, last, typename iterator_traits<_InputIterator>::iterator_category());
    }
    
    // Implementation of Advance on iterators 
    //advance's version of input_iterator_tag
    
    template <class InputIterator, class Distance>
    void __advance(InputIterator& i, Distance n, input_iterator_tag)
    {
        while (n--) 
            ++i;
    }

    //Advance's version of bidirectional_iterator_tag
    template <class BidirectionalIterator, class Distance>
    void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
    {
    if (n >= 0)
        while (n--)  ++i;
    else
        while (n++)  --i;
    }

    //Advance's version of random_access_iterator_tag
    template <class RandomIter, class Distance>
    void __advance(RandomIter& i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n)
    {
        ft::__advance(i, n,typename iterator_traits<InputIterator>::iterator_category());
    }
}









#endif 