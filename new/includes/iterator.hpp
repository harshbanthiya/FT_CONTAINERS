/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:59:26 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/11/23 15:59:26 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "type_traits.hpp"



namespace ft
{
    // tags for the iterators traits 
    #if defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

    typedef     std::input_iterator_tag             input_iterator_tag;
    typedef     std::output_iterator_tag            output_iterator_tag;
    typedef     std::forward_iterator_tag           forward_iterator_tag;
    typedef     std::bidirectional_iterator_tag     bidirectional_iterator_tag;
    typedef     std::random_access_iterator_tag     random_access_iterator_tag;

    #else 

    struct      input_iterator_tag{};
    struct      output_iterator_tag{};
    struct      forward_iterator_tag{}              : input_iterator_tag {};
    struct      bidirectional_iterator_tag{}        : forward_iterator_tag {};
    struct      random_access_iterator_tag{}        : bidirectional_iterator_tag {};

    #endif

    // Iterator base
    template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
    struct iterator
    {
        typedef         T           value_type;
        typedef         Distance    difference_type;
        typedef         Pointer     pointer;
        typedef         Reference   reference;
        typedef         Category    iterator_category;
    };

    template <typename T>
    struct _has_iterator_typedefs 
    {
        private:
            struct _two {char x; char y;};
            template <typename U>
            static _two _test(...) {};
            template <typename U>
            static char _test ( typename ft::void_t <typename U::iterator_category>::type * = 0, 
                                typename ft::void_t <typename U::difference_type>::type * = 0,
                                typename ft::void_t <typename U::value_type>::type * = 0,
                                typename ft::void_t <typename U::reference>::type * = 0,
                                typename ft::void_t <typename U::pointer>::type * = 0 ) {};
        public: 
            static const bool value = sizeof(_test<T>(0, 0, 0, 0, 0)) == 1;
    };  

    template <typename Iter, bool>
    struct iterator_traits_typedefs {};

    template <typename Iter>
    struct iterator_traits_typedefs<Iter, true>
    {
        typedef typename        Iter::iterator_category     iterator_category;
        typedef typename        Iter::value_type            value_type;
        typedef typename        Iter::difference_type       difference_type;
        typedef typename        Iter::pointer               pointer;
        typedef typename        Iter::reference             reference;
    };

    template <typename Iter, bool>
    struct  _iterator_traits {};

    template <typename Iter>
    struct _iterator_traits<Iter, true> : iterator_traits_typedefs < 
                                            Iter, is_same<typename Iter::iterator_category, input_iterator_tag>::value ||
                                                  is_same<typename Iter::iterator_category, output_iterator_tag>::value ||
                                                  is_same<typename Iter::iterator_category, forward_iterator_tag>::value ||
                                                  is_same<typename Iter::iterator_category, bidirectional_iterator_tag>::value ||
                                                  is_same<typename Iter::iterator_category, random_access_iterator_tag>::value > {};
    
    template <typename Iter>
    struct iterator_traits : _iterator_traits<Iter, _has_iterator_typedefs<Iter>::value {};

    // Traits specialisation for pointers 
    template <typename T>
    struct iterator_traits<T *>
    {
        typedef     random_acess_iterator_tag   iterator_category;
        typedef     T                           value_type;
        typedef     ptrdiff_t                   difference_type;
        typedef     T*                          pointer;
        typedef     T&                          reference;
    };

    // Traits specialisation for const pointers 
    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef     random_acess_iterator_tag   iterator_category;
        typedef     typename remove_cv<T>::type value_type;
        typedef     ptrdiff_t                   difference_type;
        typedef     const T*                    pointer;
        typedef     const T&                    reference;
    };

    // Is-foo iterator

    template <typename Iter, 
                bool = _has_iterator_typedefs<iterator_traits<Iter> >::value>
    struct _is_iterator  : false_type 
    {
        typedef void category;
    };

    template <typename Iter>
    struct _is_iterator<Iter, true> : true_type
    {
        typedef typename Iter::iterator_category category;
    };

    template <typename T>
    struct _is_iterator<T *, true> : true_type
    {
        typedef typename iterator_traits<T *>::iterator_category category;
    };

    template <typename Iter>
    struct _is_input_iterator : integral_constant<bool, (           is_same<typename _is_iterator<Iter>::category, input_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, forward_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, bidirectional_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, random_access_iterator_tag>::value ) > {};

    template <typename Iter>
    struct _is_output_iterator : integral_constant<bool, (          is_same<typename _is_iterator<Iter>::category, output_iterator_tag>::value) {};

    template <typename Iter>
    struct _is_forward_iterator : integral_constant<bool, (         is_same<typename _is_iterator<Iter>::category, forward_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, bidirectional_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, random_access_iterator_tag>::value ) {};
    
    template <typename Iter>
    struct _is_bidirectional_iterator : integral_constant<bool, (   is_same<typename _is_iterator<Iter>::category, bidirectional_iterator_tag>::value ||
                                                                    is_same<typename _is_iterator<Iter>::category, random_access_iterator_tag>::value ) {};

    template <typename Iter>
    struct _is_random_access_iterator : integral_constant<bool, (   is_same<typename _is_iterator<Iter>::category, random_access_iterator_tag>::value ) {};


    // Reverse Iterator 

    template <typename Iter>
    class reverse_iterator : iterator < typename iterator_traits<Iter>::iterator_category,
                                        typename iterator_traits<Iter>::value_type,
                                        typename iterator_traits<Iter>::difference_type,
                                        typename iterator_traits<Iter>::pointer,
                                        typename iterator_traits<Iter>::reference > 
    {
        protected:
        
            Iter    current;
        
        public:

            typedef     Iter                                            iterator_type;
            typedef     typename iterator_traits<Iter>::value_type      value_type;      
            typedef     typename iterator_traits<Iter>::difference_type difference_type;      
            typedef     typename iterator_traits<Iter>::reference       reference;      
            typedef     typename iterator_traits<Iter>::pointer         pointer;

            // Constructor
            reverse_iterator() : current() {}
            reverse_iterator(Iter it) : current(it) {}
            template <typename U>
            reverse_iterator(const reverse_iterator<U> &u) : current(u.base()) {}
            template <typename U>
            reverse_iterator &operator=(const reverse_iterator<U> &u)
            {
                current = u.base();
                return (*this);
            }

            Iter    base() const { return current; }

            // Operators 

            reference               operator*() const {Iter tmp = current; return *--tmp;}
            pointer                 operator->() const {return &(operator*());}
            reverse_iterator&       operator++() const {--current; return (*this);}
            reverse_iterator        operator++(int) const {reverse_iterator tmp(*this); --current; return (tmp);}
            reverse_iterator&       operator--() const {++current; return (*this);}
            reverse_iterator        operator--(int) const {reverse_iterator tmp(*this); ++current; return (tmp);}
            reverse_iterator        operator+(difference_type n) const{ return reverse_iterator(current - n);}
            reverse_iterator        operator-(difference_type n) const{ return reverse_iterator(current + n);}
            reverse_iterator&       operator+=(difference_type n) const{ current -= n; return (*this);}
            reverse_iterator&       operator-=(difference_type n) const{ current += n; return (*this);}
            reference               operator[](differnce_type n) const {return *(*this + _n);}
    };

    // Non Member Function overloads for Reverse Iterators 

    template <typename Iter1, typename Iter2>
    bool operator==(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() == rhs.base();}
    template <typename Iter1, typename Iter2>
    bool operator!=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() != rhs.base();}
    template <typename Iter1, typename Iter2>
    bool operator<(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() > rhs.base();}
    template <typename Iter1, typename Iter2>
    bool operator>(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() < rhs.base();}
    template <typename Iter1, typename Iter2>
    bool operator>=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() <= rhs.base();}
    template <typename Iter1, typename Iter2>
    bool operator<=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return lhs.base() >= rhs.base();}
    template <typename Iter1, typename Iter2>
    typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) {return rhs.base() - lhs.base();}
    template <typename Iter>
    reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> &it) {return reverse_iterator<Iter>(it.base() - n);}

    // Distance 
    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last, ft::input_iterator_tag)
    { 
        typename iterator_traits<InputIterator>::difference_type d(0);
        for(; first != last; ++first) 
            ++d; 
        return d;
    }

    template <typename RandIterator>
    inline typename iterator_traits<RandIterator>::difference_type _distance(RandIterator first, RandIterator last, ft::random_access_iterator_tag)
    { 
        return (last - first);
    }

    template <typename InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    { 
        return ft::_distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
    }




}

#endif 