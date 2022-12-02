#pragma once
#include "iostream"
#include "rb_tree.hpp"
#include <map>

#define FT_NOEXCEPT throw()

namespace ft
{
    template <typename Key, typename T, 
            typename Compare = std::less<Key>,
            class Allocator = std::allocator<std::pair<const Key, T> > >
    class Map
    {
        public:
        
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;
            typedef std::pair<const key_type, mapped_type>      value_type;

            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::difference_type    difference_type;

            // bidirectional iterators only 
                //typedef implementation-defined                   iterator;
                //typedef implementation-defined                   const_iterator;
                // typedef std::reverse_iterator<iterator>          reverse_iterator;
                // typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;


        class value_compare : public binary_function < value_type, value_type, bool>
        {
            protected: 
                Compare         comp;
                value_compare(Compare c) : comp(c) {}

            public:
                bool operator() (const value_type& x, const value_type& y) const 
                {return (comp(x.first, y.first);)}
        };

        // Constructors 
        map()FT_NOEXCEPT(is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
        explicit map(const key_compare& comp);
        map(const key_compare& comp, const allocator_type& a);
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare());
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp, const allocator_type& a);
        map(const map& m); iv
        map(map&& m) FT_NOEXCEPT(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
        explicit map(const allocator_type& a);
        map(const map& m, const allocator_type& a);
        map(map&& m, const allocator_type& a);
        map(initializer_list<value_type> il, const key_compare& comp = key_compare());
        map(initializer_list<value_type> il, const key_compare& comp, const allocator_type& a);
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const allocator_type& a)
            : map(first, last, Compare(), a) {}  // C++14
        map(initializer_list<value_type> il, const allocator_type& a)
        : map(il, Compare(), a) {}  // C++14
        ~map();
        

    } ;

}
