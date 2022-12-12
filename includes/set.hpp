/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:17:51 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/12/12 13:25:49 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "rb_tree.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"

namespace ft
{
    template <typename Key, typename Compare = std::less<Key>,
    typename Alloc = std::allocator<Key> >
    class set
    {
        public :

        typedef Key                                         key_type;
        typedef key_type                                    value_type;
        typedef Compare                                     key_compare;
        typedef key_compare                                 value_compare;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference; 
        typedef typename allocator_type::const_reference    const_reference; 
        typedef typename allocator_type::pointer            pointer; 
        typedef typename allocator_type::const_pointer      const_pointer;

        private :
        typedef rb_tree<Key, Key, ft::identity<Key>, key_compare, allocator_type> _base;

        public :
        typedef typename _base::const_iterator              iterator;
        typedef typename _base::const_iterator              const_iterator;
        typedef typename _base::const_reverse_iterator      reverse_iterator;
        typedef typename _base::const_reverse_iterator      const_reverse_iterator;
        typedef typename _base::difference_type             difference_type;
        typedef typename _base::size_type                   size_type;

        private :
        _base   tree;

        public :

        // Constructors and Destructors 

        explicit set(const key_compare &cmp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(cmp, alloc) {}
        
        template <typename InputIter>
        set(InputIter first, InputIter last, const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(cmp, alloc) { tree.insert_range(first, last);}

        set(const set& other) : tree(other.tree) {}
        
        set& operator=(const set& other)
        {
            if (this != &other)
                tree = other.tree;
            return (*this);
        }

        ~set() {}

        // Iterators 

        iterator begin() FT_NOEXCEPT {return iterator(tree.begin());}
        const_iterator begin() const FT_NOEXCEPT {return const_iterator(tree.begin());}

        iterator end() FT_NOEXCEPT {return iterator(tree.end());}
        const_iterator end() const FT_NOEXCEPT {return const_iterator(tree.end());}
    
        reverse_iterator rbegin() FT_NOEXCEPT {return tree.rbegin();}
        const_reverse_iterator rbegin() const FT_NOEXCEPT {return tree.rbegin();}

        reverse_iterator rend() FT_NOEXCEPT {return tree.rend();}
        const_reverse_iterator rend() const FT_NOEXCEPT {return tree.rend();}

        // Capacity
        bool empty() const FT_NOEXCEPT {return tree.empty();}
        size_type size() const FT_NOEXCEPT {return tree.size();}
        size_type max_size() const FT_NOEXCEPT {return tree.max_size();}

        // Modifiers 

        pair<iterator, bool> insert(const value_type& val)
        { return tree.insert_unique(val);}
        iterator insert(iterator position, const value_type& val)
        { return tree.insert_unique_with_hint(position, val);}
        template <typename InputIter>
        void insert(InputIter first, InputIter last)
        { tree.insert_range(first, last);}

        void erase(iterator position) {tree.erase(position);}
        size_type erase(const key_type& k){return tree.erase(k);}
        void erase(iterator first, iterator last) { tree.erase(first, last);}

        void swap(set &other) {tree.swap(other.tree);}
        void clear() {tree.clear();}

        // Observers 
        key_compare key_comp() const {return tree.key_comp();}
        value_compare value_comp() const {return value_compare(tree.key_comp());}

        // Operations 
        iterator find(const value_type& k) const {return tree.find(k).remove_const();}
        size_type count(const value_type& k) const {return tree.count(k);}

        iterator lower_bound(const value_type& k) {return tree.lower_bound(k);}
        const_iterator lower_bound(const value_type& k) const {return tree.lower_bound(k);}
        
        iterator upper_bound(const value_type& k) {return tree.upper_bound(k);}
        const_iterator upper_bound(const value_type& k) const {return tree.upper_bound(k);}
        
        pair<iterator, iterator> equal_range(const value_type &k) {return tree.equal_range(k);}
        pair<const_iterator, const_iterator> equal_range(const value_type &k) const {return tree.equal_range(k);}

        allocator_type get_allocator() const {return allocator_type(tree.get_allocator());}
    
        template <typename T1, typename C1, typename A1>
        friend bool operator==(const set& lhs, const set& rhs);
        template <typename T1, typename C1, typename A1>
        friend bool operator<(const set& lhs, const set& rhs);
    };

    template <typename T, typename Compare, typename Alloc>
    bool operator==(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}

    template <typename T, typename Compare, typename Alloc>
    bool operator!=(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return !(lhs == rhs);}

    template <typename T, typename Compare, typename Alloc>
    bool operator<(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    template <typename T, typename Compare, typename Alloc>
    bool operator>(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return (rhs < lhs);}

    template <typename T, typename Compare, typename Alloc>
    bool operator<=(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return !(rhs < lhs);}

    template <typename T, typename Compare, typename Alloc>
    bool operator>=(const ft::set<T, Compare, Alloc> &lhs, const ft::set<T, Compare, Alloc> &rhs)
    { return !(lhs < rhs);}

    template <typename T, typename Compare, typename Alloc>
    void swap(ft::set<T, Compare, Alloc> &lhs, ft::set<T, Compare, Alloc> &rhs)
    { lhs.swap(rhs); }

}


#endif