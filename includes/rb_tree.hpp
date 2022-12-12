/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:19:12 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/12/12 13:13:29 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

#define FT_NOEXCEPT throw()

namespace ft
{
    enum tree_node_color {RED = false, BLACK = true};

    // Declarations to use algo in cpp file 
    struct tree_node_base;
    
    tree_node_base* tree_increment(tree_node_base *x) FT_NOEXCEPT;
    const tree_node_base* tree_increment(const tree_node_base *x) FT_NOEXCEPT ;
    tree_node_base* tree_decrement(tree_node_base *x) FT_NOEXCEPT;
    const tree_node_base* tree_decrement(const tree_node_base *x) FT_NOEXCEPT;
    void    tree_rotate_left(tree_node_base* const x, tree_node_base *& root);
    void    tree_rotate_right(tree_node_base * const x, tree_node_base *&root);
    void   tree_insert_and_fixup(const bool insert_left, tree_node_base *x,
                                    tree_node_base *p, tree_node_base &header) FT_NOEXCEPT;
    tree_node_base *tree_erase_and_fixup(tree_node_base *const z,
                                        tree_node_base &header) FT_NOEXCEPT;
    tree_node_base*     _minimum(tree_node_base *x) FT_NOEXCEPT;
    const tree_node_base* _minimum(const tree_node_base *x) FT_NOEXCEPT;
    tree_node_base*     _maximum(tree_node_base *x) FT_NOEXCEPT;
    const tree_node_base* _maximum(const tree_node_base *x) FT_NOEXCEPT;

    struct tree_node_base
    {
        typedef tree_node_base          *base_ptr;
        typedef const tree_node_base    *const_base_ptr;

        tree_node_color                 color;
        base_ptr                        parent;
        base_ptr                        left_child;
        base_ptr                        right_child;  
    };

    struct tree_header
    {
        tree_node_base          header;
        std::size_t             node_count;

        tree_header() {header.color = RED; tree_reset();}
        void tree_reset();
        void tree_move_data(tree_header &other);
    };

    template <typename key_compare>
    struct tree_key_compare
    {
        key_compare     key_cmp;

        tree_key_compare() : key_cmp() {}
        tree_key_compare(const key_compare &other) : key_cmp(other) {}
    };

    // Node for rb tree
    template <typename value>
    struct tree_node : public tree_node_base
    {
        typedef tree_node<value>    *_Link_type;

        value                       value_field;
        value                       *value_ptr() {return &value_field;}
        const value                 *value_ptr() const {return &value_field;} 
    };

    // Iterator Tree 
    template <typename T>
    struct tree_iterator : public iterator<bidirectional_iterator_tag, T>
    {
        typedef T                               value_type;
        typedef T&                              reference; 
        typedef T*                              pointer;
        typedef bidirectional_iterator_tag      iterator_category;
        typedef ptrdiff_t                       difference_type; 

        typedef tree_iterator<T>                iterator_type;
        typedef tree_node_base::base_ptr        _Base_ptr;
        typedef tree_node<T>*                   _Link_type;

        _Base_ptr                                node;

        tree_iterator() : node() {}
        tree_iterator(const tree_iterator &other) : node(other.node) {}
        explicit  tree_iterator(_Base_ptr x) : node(x) {}

        reference operator*() const FT_NOEXCEPT {return *static_cast<_Link_type>(node)->value_ptr();}
        pointer   operator->() const FT_NOEXCEPT {return static_cast<_Link_type>(node)->value_ptr();}

        iterator_type &operator++() FT_NOEXCEPT {node = tree_increment(node); return *this;}
        iterator_type operator++(int) FT_NOEXCEPT   {iterator_type tmp(*this); ++(*this); return tmp;}
        iterator_type &operator--() FT_NOEXCEPT {node = tree_decrement(node); return *this;}
        iterator_type operator--(int) FT_NOEXCEPT   {iterator_type tmp(*this); --(*this); return tmp;}
         
        friend bool operator== (const iterator_type &lhs, const iterator_type &rhs) FT_NOEXCEPT
        { return lhs.node == rhs.node; }

        friend bool operator!= (const iterator_type &lhs, const iterator_type &rhs) FT_NOEXCEPT
        { return lhs.node != rhs.node; }
    };

    // Const Iterator Overload for Tree
    template <typename T>
    struct tree_const_iterator : public iterator<bidirectional_iterator_tag, T>
    {
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference; 
        typedef bidirectional_iterator_tag      iterator_category;
        typedef ptrdiff_t                       difference_type; 

        typedef tree_iterator<T>                iterator;
        typedef tree_const_iterator<T>          const_iterator_type;
        typedef tree_node_base::const_base_ptr  _Base_ptr;
        typedef const tree_node<T>*             _Link_type;

        _Base_ptr                                node;

        tree_const_iterator() FT_NOEXCEPT: node() {}
        explicit  tree_const_iterator(_Base_ptr x) FT_NOEXCEPT : node(x) {}
        tree_const_iterator(const tree_const_iterator &other) : node(other.node) {}
        tree_const_iterator(iterator it) : node(it.node) {}

        iterator remove_const() const FT_NOEXCEPT {return iterator(const_cast<typename iterator::_Base_ptr>(node));}
        reference operator*() const FT_NOEXCEPT {return *static_cast<_Link_type>(node)->value_ptr();}
        pointer   operator->() const FT_NOEXCEPT {return static_cast<_Link_type>(node)->value_ptr();}

        const_iterator_type &operator++() FT_NOEXCEPT {node = tree_increment(node); return *this;}
        const_iterator_type operator++(int) FT_NOEXCEPT   {const_iterator_type tmp(*this); ++(*this); return tmp;}
        const_iterator_type &operator--() FT_NOEXCEPT {node = tree_decrement(node); return *this;}
        const_iterator_type operator--(int) FT_NOEXCEPT   {const_iterator_type tmp(*this); --(*this); return tmp;}
         
        friend bool operator== (const const_iterator_type &lhs, const const_iterator_type &rhs) FT_NOEXCEPT
        { return lhs.node == rhs.node; }

        friend bool operator!= (const const_iterator_type &lhs, const const_iterator_type &rhs) FT_NOEXCEPT
        { return lhs.node != rhs.node; }
    };

    // Red Black Tree Class with key, value, key of value functor, Comparing function and allocator
    template <typename Key, typename Value, typename KeyofVal, typename Compare = std::less<Key>, typename Alloc = std::allocator<Value> >
    class rb_tree
    {
        private :

        typedef tree_node_base                          *_Base_ptr;
        typedef const tree_node_base                    *_Const_Base_ptr;
        typedef tree_node<Value>                        *_Link_type;
        typedef const tree_node<Value>                  *_Const_Link_type;

        public :

        typedef Key                                     key_type;
        typedef Value                                   value_type;
        typedef value_type*                             pointer;
        typedef const value_type*                       const_pointer;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
        typedef Alloc                                   allocator_type;

        typedef tree_iterator<value_type>               iterator;
        typedef tree_const_iterator<value_type>         const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        
        typedef typename Alloc::template rebind<tree_node<Value> >::other
            _Node_allocator;
        
        private :

        // Impl data of tree - Node allocator: rebind the allocator ; tree_key_compare : key compare functor ; tree_header: head of the tree
        template <typename _key_compare>
        struct tree_impl : public _Node_allocator, public tree_key_compare<_key_compare>, public tree_header
        {
            typedef tree_key_compare<_key_compare>      _Base_key_compare;

            tree_impl() : _Node_allocator () {}
            tree_impl(const tree_impl &other) : _Node_allocator(other), _Base_key_compare(other.key_cmp), tree_header() {}
            tree_impl(const _key_compare &_cmp, const _Node_allocator &_a) : _Node_allocator(_a), _Base_key_compare(_cmp) {}

        };

        tree_impl<Compare>                              impl;
        
        _Node_allocator &_get_Node_allocator()  {return this->impl;}
        const _Node_allocator &_get_Node_allocator() const  {return this->impl;}
        
        _Link_type  _allocate_node() {return _get_Node_allocator().allocate(1);}
        void        _deallocate_node(_Link_type p) {_get_Node_allocator().deallocate(p, 1);}
        
        void        _construct_node(_Link_type _nd, const value_type &x) {get_allocator().construct(_nd->value_ptr(), x);}
        void        _destroy_node(_Link_type p) {get_allocator().destroy(p->value_ptr());}

        _Link_type  _create_node(const value_type& x) 
        {   
            _Link_type tmp = _allocate_node();
            _construct_node(tmp, x);
            return tmp;
        }

        // clone node to get a clone of node with same value and color 
        _Link_type  _clone_node(_Link_type  x)
        {
            _Link_type  tmp = this->_create_node(*x->value_ptr());
            tmp->color = x->color;
            tmp->left_child = NULL;
            tmp->right_child = NULL;
            return tmp; 
        }

        // Get Specific Nodes returning base node pointer type 
        _Base_ptr&  _root() {return this->impl.header.parent;}
        _Const_Base_ptr _root() const {return this->impl.header.parent;}

        _Base_ptr&  _leftmost() {return this->impl.header.left_child;}
        _Const_Base_ptr  _leftmost() const {return this->impl.header.left_child;}

        _Base_ptr&  _rightmost() {return this->impl.header.right_child;}
        _Const_Base_ptr  _rightmost() const {return this->impl.header.right_child;}
    
        _Base_ptr   _end() {return &this->impl.header;}
        _Const_Base_ptr _end() const {return &this->impl.header;}

        static _Base_ptr _S_minimum(_Base_ptr x) {return _minimum(x);}
        static _Const_Base_ptr _S_minimum(_Const_Base_ptr x) {return _minimum(x);}
        
        static _Base_ptr _S_maximum(_Base_ptr x) {return _maximum(x);}
        static _Const_Base_ptr _S_maximum(_Const_Base_ptr x) {return _maximum(x);}

        // Return Key Type
        static const Key &_S_key(_Const_Link_type x) {return KeyofVal()(*x->value_ptr());}
        static const Key &_S_key(_Const_Base_ptr x) {return _S_key(static_cast<_Const_Link_type>(x));}

        // Return Node Types 
        _Link_type  _begin() {return static_cast<_Link_type>(this->impl.header.parent);}
        _Const_Link_type  _begin() const {return static_cast<_Link_type>(this->impl.header.parent);}
        
        static _Link_type _S_left(_Base_ptr x) {return static_cast<_Link_type>(x->left_child);}
        static _Const_Link_type _S_left(_Const_Base_ptr x) {return static_cast<_Link_type>(x->left_child);}
    
        static _Link_type _S_right(_Base_ptr x) {return static_cast<_Link_type>(x->right_child);}
        static _Const_Link_type _S_right(_Const_Base_ptr x) {return static_cast<_Link_type>(x->right_child);}
    
        // Helper Functions
        
        // Get position to insert  & insert with hint 
        ft::pair<_Base_ptr, _Base_ptr> _get_insert_unique_position(const key_type& k);
        ft::pair<_Base_ptr, _Base_ptr> _get_insert_hint_unique_position(const_iterator _pos, const key_type &_k);

        _Link_type _copy_tree(_Link_type x, _Base_ptr p);
        _Link_type _copy_tree(const rb_tree &nt)
        {
            _Link_type root = _copy_tree(const_cast<_Link_type>(nt._begin()), _end()); // Copy whole tree
            _leftmost() = _S_minimum(root); // Updating info in the struct header 
            _rightmost() = _S_maximum(root); 
            impl.node_count = nt.impl.node_count;
            return root;
        }

        void _delete_node(_Link_type p){ _destroy_node(p); _deallocate_node(p);}
        void _erase_without_balancing(_Link_type x);
        void _erase_helper(const_iterator position);
        void _erase_helper(const_iterator first, const_iterator last);

        iterator lower_bound_helper(_Link_type x, _Base_ptr y, const key_type &k);
        const_iterator lower_bound_helper(_Const_Link_type x, _Const_Base_ptr y, const key_type &k) const;
        iterator upper_bound_helper(_Link_type x, _Base_ptr y, const key_type &k);
        const_iterator upper_bound_helper(_Const_Link_type x, _Const_Base_ptr y, const key_type &k) const;
        iterator _insert_helper(_Base_ptr x, _Base_ptr p, const value_type& v);


        // Constructors and Destructors 
        public :

        rb_tree() {}
        rb_tree(const Compare &cmp, const allocator_type &a = allocator_type()) : impl(cmp, _Node_allocator(a)) {}
        rb_tree(const rb_tree &other) : impl(other.impl) {if (other._root() != NULL) _root() = _copy_tree(other);}
        ~rb_tree() {_erase_without_balancing(_begin());}
        rb_tree &operator=(const rb_tree &other)
        {
            if (this != &other)
            {
                this->clear();
                impl.key_cmp = other.impl.key_cmp;
                if (other._root() != NULL)
                    _root() = _copy_tree(other);
            }
            return (*this);
        }

        // Public Member Functions 

        // Accessors 
        Compare key_comp() const {return impl.key_cmp;}
        iterator begin() {return iterator(impl.header.left_child);}
        const_iterator begin() const {return const_iterator(impl.header.left_child);}
        iterator end() {return iterator(&impl.header);}    
        const_iterator end() const {return const_iterator(&impl.header);}    
        reverse_iterator rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        reverse_iterator rend() {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
    
        // Capacity 
        bool empty() const {return impl.node_count == 0;}
        size_type max_size() const {return ft::min(_get_Node_allocator().max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));}
        size_type size() const {return impl.node_count;}

        // Modifiers 
        void erase(iterator position) {_erase_helper(position);}
        void erase(const_iterator position) {_erase_helper(position);}
        size_type erase(const key_type &v);
        void erase(iterator first, iterator last) {_erase_helper(first, last);}
        void erase(const_iterator first, const_iterator last) {_erase_helper(first, last);}
        void clear() {_erase_without_balancing(_begin()); impl.tree_reset();}
        void swap(rb_tree &nt);
        ft::pair<iterator, bool> insert_unique(const value_type& v);
        iterator insert_unique_with_hint(const_iterator position, const value_type &v);
        template <typename InputIter>
        void insert_range(InputIter first, InputIter last)
        {
            for(; first != last; ++first)
                insert_unique_with_hint(end(), *first);
        }

        // Operations 

        // Find will help get the node if key exists else return end()
        iterator find(const key_type &k)
        {
            iterator found = lower_bound_helper(_begin(), _end(), k);
            if (impl.key_cmp(k, _S_key(found.node)) || found == end())
                return (end());
            return found;
        }

        const_iterator find(const key_type &k) const 
        {
            const_iterator found = lower_bound_helper(_begin(), _end(), k);
            if (impl.key_cmp(k, _S_key(found.node)) || found == end())
                return (end());
            return found;
        }

        size_type count(const key_type &k) const
        {
            const_iterator found = find(k);
            return (found == end() ? 0 : 1);
        }

        iterator lower_bound(const key_type &k) {return lower_bound_helper(_begin(), _end(), k);}
        const_iterator lower_bound(const key_type &k) const {return lower_bound_helper(_begin(), _end(), k);}
        iterator upper_bound(const key_type &k) {return upper_bound_helper(_begin(), _end(), k);}
        const_iterator upper_bound(const key_type &k) const {return upper_bound_helper(_begin(), _end(), k);}

        pair<iterator, iterator> equal_range(const key_type &k);
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
        
        allocator_type get_allocator() const { return allocator_type(_get_Node_allocator());}

        // Print
        void print_tree();
        static void print_tree(const std::string &prefix, _Link_type x, bool isLeft);
    };



    // Get unique position to insert (key to get position)
    // ret_pair.first : if not null, insert left else insert right 
    // ret_pair.second : if not NULL, parent of node to insert; if null, regard as false which the node will not insert
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    ft::pair <typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_Base_ptr,
                typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_Base_ptr> 
            rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_get_insert_unique_position(const key_type& k)
    {
        typedef ft::pair<_Base_ptr, _Base_ptr> ret_pair;
        _Link_type x = _begin(); // root
        _Base_ptr y = _end(); // header

        bool cmp = true;

        // Check left or right, until we find the leaf node ; Y will be the leaf  
        while (x != NULL)
        {
            y = x;
            cmp = impl.key_cmp(k, _S_key(x));
            x = cmp ? _S_left(x) : _S_right(x);
        }

        iterator j = iterator (y);
        if (cmp)
        {
            if (j == begin())             // leftmost
                return (ret_pair(x, y));  // (Null, leaf)
            --j;                          // decrement node
        }

        if (impl.key_cmp(_S_key(j.node), k)) // Compare before leaf and k 
            return (ret_pair(x, y));         // Return (NULL, leaf)
        return ret_pair(j.node, NULL);       // else return (decremented leaf, NULL(false))
    }


    // Get unique position when hint is given 
    // Hint is where k should be inserted 
    // ret_pair.first : if not null, insert left else insert right 
    // ret_pair.second : if not NULL, parent of node to insert; if null, regard as false which the node will not insert
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    ft::pair <typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_Base_ptr,
                typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_Base_ptr> 
            rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_get_insert_hint_unique_position(const_iterator pos, const key_type& k)
    {
        iterator position = pos.remove_const();
        typedef ft::pair<_Base_ptr, _Base_ptr> ret_pair;

        if (position.node == _end()) // header
        {
            if (size() > 0 && impl.key_cmp(_S_key(_rightmost()), k))
                return (ret_pair(NULL, _rightmost()));
            else 
                return (_get_insert_unique_position(k));
        }
        else if (impl.key_cmp(k, _S_key(position.node))) // less than position
        {
            iterator before = position;
            if (position.node == _leftmost())
                return ret_pair(_leftmost(), _leftmost());
            else if (impl.key_cmp(_S_key((--before).node), k))
            {
                if (_S_right(before.node) == NULL)
                    return ret_pair(NULL, before.node);
                else 
                    return ret_pair(position.node, position.node);
            }
            else 
                return _get_insert_unique_position(k);
        }
        else if (impl.key_cmp(_S_key(position.node), k)) // greater than position 
        {
            iterator after = position;
            if (position.node == _rightmost())
                return ret_pair(NULL, _rightmost());
            else if (impl.key_cmp(k, _S_key((++after).node)))
            {
                if (_S_right(position.node) == NULL)
                    return ret_pair(NULL, position.node);
                else 
                    return ret_pair(after.node, after.node);
            }
            else 
                return _get_insert_unique_position(k);
        }
        else // equal to the position. Keys cannot be same
            return ret_pair(position.node, NULL); 
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator 
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_insert_helper(_Base_ptr x, _Base_ptr p, const value_type& v)
    {
        bool    insert_left = (x != 0 || p == _end() || impl.key_cmp(KeyofVal()(v), _S_key(p)));
        _Link_type z = this->_create_node(v);
        tree_insert_and_fixup(insert_left, z, p, this->impl.header);
        ++impl.node_count;
        return iterator(z);
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    ft::pair<typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator, 
    bool>
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::insert_unique(const value_type& v)
    {
        typedef ft::pair<iterator, bool> ret_pair;

        ft::pair<_Base_ptr, _Base_ptr> ret = _get_insert_unique_position(KeyofVal()(v)); // get position based key of v
        if (ret.second)
            return ret_pair(_insert_helper(ret.first, ret.second, v), true);
        return ret_pair(iterator(ret.first), false);
    } 

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::insert_unique_with_hint(const_iterator position, const value_type& v)
    {
        ft::pair<_Base_ptr, _Base_ptr> ret = _get_insert_hint_unique_position(position, KeyofVal()(v));
        if (ret.second)
            return _insert_helper(ret.first, ret.second, v);
        return iterator(ret.first);
    }

    // Copy tree including the header of the tree 
    // x is root of new tree, p first, end() and then parent of x
    // return tree
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_Link_type
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_copy_tree(_Link_type x, _Base_ptr p)
    {
        _Link_type top = _clone_node(x); // Clone data from current node 
        top->parent = p;                // Link Parent 

        if (x->right_child)
            top->right_child = _copy_tree(_S_right(x), top); // copy right until NULL
        
        p = top;
        x = _S_left(x);

        while (x != NULL) // copy left until NULL
        {
            _Link_type y = _clone_node(x);
            p->left_child = y;
            y->parent = p;
            if (x->right_child)
                y->right_child = _copy_tree(_S_right(x), y); // if left has right copy again
            p = y;
            x = _S_left(x);
        }
        return top;
    }


    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    void  rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_erase_without_balancing(_Link_type x)
    {
        while (x != NULL)
        {
            _erase_without_balancing(_S_right(x));
            _Link_type y = _S_left(x);
            _delete_node(x);
            x = y;
        }
    }

    // Erase helper functions to erase a specific node and rebalance 
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    void rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_erase_helper(const_iterator position)
    {
        _Link_type y = static_cast<_Link_type>(tree_erase_and_fixup(const_cast<_Base_ptr>(position.node), impl.header));
        _delete_node(y);
        --impl.node_count;
    }

    // Erase helper function to erase in range and rebalance 
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    void rb_tree<Key, Val, KeyofVal, Compare, Alloc>::_erase_helper(const_iterator first, const_iterator last)
    {
        if (first == begin() && last == end())
            clear();
        else 
        {
            while (first != last)
                _erase_helper(first++);
        }
    }    

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::size_type
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::erase(const key_type& v)
    {
        ft::pair<const_iterator, const_iterator> p = equal_range(v);
        const size_type prev_size = size();
        _erase_helper(p.first, p.second);
        return (prev_size - size());
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    void rb_tree<Key, Val, KeyofVal, Compare, Alloc>::swap(rb_tree &nt)
    {
        if (_root() == NULL)
        {
            if (nt._root() != NULL)
                impl.tree_move_data(nt.impl);
        }
        else if (nt.root() == NULL)
                nt.impl.tree_move_data(impl);
        else 
        {
            ft::swap(_root(), nt._root());
            ft::swap(_leftmost(), nt._leftmost());
            ft::swap(_rightmost(), nt._rightmost());

            _root()->parent = _end();
            nt._root()->parent = nt._end();
            ft::swap(impl.node_count, nt.impl.node_count);
        }
        ft::swap(_get_Node_allocator(), nt._get_Node_allocator());
    }

    // Returns elements greater than or equal to key
    // x starting node ; y backup node ; k key to compare 
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::lower_bound_helper(_Link_type x, _Base_ptr y, const key_type &k)
    {
        while (x != NULL)
        {
            if (!impl.key_cmp(_S_key(x), k))
            {
                y = x;
                x = _S_left(x);
            }
            else 
                x = _S_right(x);
        }
        return iterator(y);
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::const_iterator
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::lower_bound_helper(_Const_Link_type x, _Const_Base_ptr y, const key_type &k) const
    {
        while (x != NULL)
        {
            if (!impl.key_cmp(_S_key(x), k))
            {
                y = x;
                x = _S_left(x);
            }
            else 
                x = _S_right(x);
        }
        return const_iterator(y);
    }


    // Returns the element greater than key
    // x starting node; y backup node; k key to compare 
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::upper_bound_helper(_Link_type x, _Base_ptr y, const key_type &k)
    {
        while (x != NULL)
        {
            if (impl.key_cmp(k, _S_key(x)))
            {
                y = x;
                x = _S_left(x);
            }
            else 
                x = _S_right(x);
        }
        return iterator(y);
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::const_iterator
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::upper_bound_helper(_Const_Link_type x, _Const_Base_ptr y, const key_type &k) const
    {
        while (x != NULL)
        {
            if (impl.key_cmp(k, _S_key(x)))
            {
                y = x;
                x = _S_left(x);
            }
            else 
                x = _S_right(x);
        }
        return const_iterator(y);
    }

    // Returns the range containing the given key in the container.
    // first >= key second > key
    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    ft::pair <typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator,
                typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::iterator>
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::equal_range(const key_type &k)
    {
        _Link_type x = _begin();
        _Base_ptr y = _end();

        while (x != NULL)
        {
            if (impl.key_cmp(_S_key(x), k))
                x = _S_right(x);
            else if (impl.key_cmp(k, _S_key(x)))
            {
                y = x;
                x = _S_left(x);
            }
            else // key of x == k 
            {
                _Link_type x_up(x);
                _Base_ptr y_up(y);

                y = x;
                x = _S_left(x);
                x_up = _S_right(x_up);

                return ft::pair<iterator, iterator> (lower_bound_helper(x, y, k), upper_bound_helper(x_up, y_up, k));
            }
        }
        return ft::pair<iterator, iterator>(iterator(y), iterator(y));
    }

    template <typename Key, typename Val, typename KeyofVal, typename Compare, typename Alloc>
    ft::pair <typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::const_iterator,
                typename rb_tree<Key, Val, KeyofVal, Compare, Alloc>::const_iterator>
    rb_tree<Key, Val, KeyofVal, Compare, Alloc>::equal_range(const key_type &k) const
    {
        _Const_Link_type x = _begin();
        _Const_Base_ptr y = _end();

        while (x != NULL)
        {
            if (impl.key_cmp(_S_key(x), k))
                x = _S_right(x);
            else if (impl.key_cmp(k, _S_key(x)))
            {
                y = x;
                x = _S_left(x);
            }
            else // key of x == k 
            {
                _Const_Link_type x_up(x);
                _Const_Base_ptr y_up(y);

                y = x;
                x = _S_left(x);
                x_up = _S_right(x_up);

                return ft::pair<const_iterator, const_iterator> (lower_bound_helper(x, y, k), upper_bound_helper(x_up, y_up, k));
            }
        }
        return ft::pair<const_iterator, const_iterator>(const_iterator(y), const_iterator(y));
    }

}


#endif 