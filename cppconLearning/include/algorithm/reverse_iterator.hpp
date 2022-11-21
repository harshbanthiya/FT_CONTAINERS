#pragma once

#include "advance.hpp"
#include "iterator-tags.hpp"
#include "../traits-classes/is-foo-iterator.hpp"
#include "../traits-classes/iterator-traits.hpp"

#include <utility>

namespace ft
{
    template <class It>
    struct reverse_iterator
    {
        static_assert(is_bidirectional_iterator_v<It>, "Requires bidirectional iterators or better");

        using value_type = typename iterator_traits<It>::value_type;
        using difference_type = typename iterator_traits<It>::difference_type;
        using pointer = typename iterator_traits<It>::pointer;
        using reference = typename iterator_traits<It>::reference;
        using iterator_category  = typename iterator_traits<It>::iterator_category;
        
        using iterator_type = It;

        constexpr reverse_iterator() = default;
        constexpr explicit reverse_iterator(It x) : m_base(std::move(x)) {}

        // Notice - this is also the copy constructor 
        template <class U>
        constexpr reverse_iterator(const reverse_iterator<U>& u) : m_base(u.base()) {}

        // Notice - this is also our copy assignment operator 
        template <class U>
        constexpr reverse_iterator& operator=(const reverse_iterator<U>& u)
        {
            m_base = u.base();
            return (*this);
        }

        constexpr It base() const {return m_base;}

        constexpr reference operator*() const {return *prev(base());}
        constexpr pointer   operator->() const {return &*prev(base());}

        constexpr reference operator[](difference_type n) const {return *(base() - n - 1);} 

        constexpr reverse_iterator& operator++() {--m_base; return *this;}
        constexpr reverse_iterator& operator++(int) {auto result = *this; --m_base; return result;}
        constexpr reverse_iterator& operator--() {++m_base; return *this;}
        constexpr reverse_iterator& operator--(int) {auto result = *this; ++m_base; return result;}
        
        constexpr reverse_iterator& operator+=(difference_type n) {m_base -= n; return *this;}
        constexpr reverse_iterator& operator-=(difference_type n) {m_base += n; return *this;}

        private:

        It  m_base;
    
    };

    template<class It> constexpr reverse_iterator<It> operator+(reverse_iterator<It> r, iterator_difference_t<It> n) {return r += n; }
    template<class It> constexpr reverse_iterator<It> operator-(reverse_iterator<It> r, iterator_difference_t<It> n) {return r -= n; }
    template<class It> constexpr reverse_iterator<It> operator+(iterator_difference_t<It> n, reverse_iterator<It> r) {return r += n; }
    template<class It> constexpr iterator_difference_t<It> operator-(reverse_iterator<It> a, reverse_iterator<It> b) {return b.base() - a.base(); }

    template<class A, class B> constexpr bool operator==(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() == b.base();} 
    template<class A, class B> constexpr bool operator!=(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() != b.base();} 
    template<class A, class B> constexpr bool operator<(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() > b.base();} 
    template<class A, class B> constexpr bool operator<=(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() >= b.base();} 
    template<class A, class B> constexpr bool operator>(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() < b.base();} 
    template<class A, class B> constexpr bool operator>=(const reverse_iterator<A> &a, const reverse_iterator<B> &b) {return a.base() <= b.base();} 
}

/*
    
*/