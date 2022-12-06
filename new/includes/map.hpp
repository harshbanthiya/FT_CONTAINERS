#ifndef MAP_HPP
#define MAP_HPP


#include <functional>
#include "algorithm.hpp"
#include "utility.hpp"
#include "red_black_tree/rb_tree.hpp"


#define FT_NOEXCEPT throw()

namespace ft
{
    template <typename Key, typename T, 
            typename Compare = std::less<Key>,
            class Allocator = std::allocator<std::pair<const Key, T> > >
    class map
    {
        public:
        
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef Compare                                     key_compare;
            typedef Allocator                                   allocator_type;
            typedef std::pair<const key_type, mapped_type>      value_type;

        private :

            typedef rb_tree<key_type, value_type, ft::select_first<value_type>, key_compare, allocator_type> _base;

            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::size_type          size_type;
            typedef typename allocator_type::difference_type    difference_type;

            typedef typename _base::iterator                    iterator;
            typedef typename _base::const_iterator              const_iterator;
            typedef typename _base::reverse_iterator            reverse_iterator;
            typedef typename _base::const_reverse_iterator      const_reverse_iterator;
            typedef typename _base::differnce_type              difference_type;
            typedef typename _base::size_type                   size_type;


        class value_compare : public binary_function < value_type, value_type, bool>
        {
            friend class map<Key, T, Compare, Allocator>;
            protected: 
                Compare         comp;
                value_compare(Compare c) : comp(c) {}

            public:
                bool operator() (const value_type& x, const value_type& y) const 
                {return (comp(x.first, y.first);)}
        };
    
        private :
        _base       tree;


        // Constructors 
        public :
        explicit map(const key_compare &cmp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(cmp, alloc) {}

        template <typename InputIter>
        map(InputIter first, InputIter last, const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(cmp, alloc) {tree.insert_range(first, last);}

        map(const map& other) : tree(other.treee) {}

        map& operator=(const map& other)
        {
            if (this != &other)
                tree = other.tree;
            return *this;
        }

        ~map() {}


        // Iterators 
        iterator    begin() FT_NOEXCEPT {return iterator(tree.begin());}
        const_iterator    begin() const FT_NOEXCEPT {return const_iterator(tree.begin());}
        iterator    end() FT_NOEXCEPT {return iterator(tree.end());}
        const_iterator    end() const FT_NOEXCEPT {return const_iterator(tree.end());}
        reverse_iterator    rbegin() FT_NOEXCEPT {return iterator(tree.rbegin());}
        const_reverse_iterator    rbegin() const FT_NOEXCEPT {return const_iterator(tree.rbegin());}
        reverse_iterator    rend() FT_NOEXCEPT {return iterator(tree.rend());}
        const_reverse_iterator    rend() const FT_NOEXCEPT {return const_iterator(tree.rend());}

        // Capacity
        bool empty() const FT_NOEXCEPT {return tree.empty();}
        size_type size() const FT_NOEXCEPT {return tree.size();}
        size_type max_size() const FT_NOEXCEPT {return tree.max_size();}

        // Element Access
        mapped_type& operator[](const key_type& k)
        {
            iterator it = lower_bound(k);
            if (it == end() || key_compare()(k, (*it).first))
                it = insert(it, value_type(k, mapped_type()));
            return (*it).second;
        }

        mapped_type& at(const key_type& k)
        {
            iterator it = lower_bound(k);
            if (it == end() || key_compare()(k, (*it).first))
                throw std::out_of_range("Map: out of range");
            return (*it).second;
        }   

        const mapped_type& at(const key_type& k) const
        {
            iterator it = lower_bound(k);
            if (it == end() || key_compare()(k, (*it).first))
                throw std::out_of_range("Map: out of range");
            return (*it).second;
        }   

        // Modifiers 
        pair<iterator, bool> insert(const value_type& val)
        {
            return tree.insert_unique(val);
        }
        iterator insert(iterator position, const value_type& val)
        {
            return tree.insert_unique_with_hint(position, val);
        }
        template <typename InputIter>
        void insert(InputIter first, InputIter last)
        {
            tree.insert_range(first, last);
        }

        void erase(iterator position) {tree.erase(position);}
        size_type erase(const key_type& k) {return tree.erase(k);}
        void erase(iterator first, iterator last) {tree.erase(first, last);}
        void swap(map &other) {tree.swap(other.tree);}
        void clear() {tree.clear()};

          // observers
        key_compare key_comp() const { return tree.key_comp(); }
        value_compare value_comp() const { return value_compare(tree.key_comp()); }

        // operations
        iterator find(const key_type& k) { return tree.find(k); }
        const_iterator find(const key_type& k) const { return tree.find(k); }

        size_type count(const key_type& k) const { return tree.count(k); }

        iterator lower_bound(const key_type& k) { return tree.lower_bound(k); }
        const_iterator lower_bound(const key_type& k) const {
            return tree.lower_bound(k);
        }

        iterator upper_bound(const key_type& k) { return tree.upper_bound(k); }
        const_iterator upper_bound(const key_type& k) const {
            return tree.upper_bound(k);
        }

        pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
            return tree.equal_range(k);
        }
        pair<iterator, iterator> equal_range(const key_type& k) {
            return tree.equal_range(k);
        }

        allocator_type get_allocator() const {
            return allocator_type(tree.get_allocator());
        }
        
    } ;
    
    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator==(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                    const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator!=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                    const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return !(lhs == rhs);
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator<(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end());
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator>(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return rhs < lhs;
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator<=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                    const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return !(rhs < lhs);
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    bool operator>=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                    const ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    return !(lhs < rhs);
    }

    template <typename _Key, typename _T, typename _Compare, typename _Alloc>
    void swap(ft::map<_Key, _T, _Compare, _Alloc>& lhs,
            ft::map<_Key, _T, _Compare, _Alloc>& rhs) {
    lhs.swap(rhs);
    }
}

#endif