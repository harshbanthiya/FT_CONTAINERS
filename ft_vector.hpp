/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/20 11:25:55 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "MyIterator.hpp"

namespace ft
{
    template<typename T, class Allocator = std::allocator<T> > 
    class vector
    {
        // Typedefs to use throughout 
        public:

        typedef Allocator                                       allocator_type;
        
        typedef typename allocator_type::value_type             value_type;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::difference_type        difference_type;

        typedef value_type*                                     iterator;
        typedef const value_type*                               const_iterator;
        /* 
            typedef std::reverse_iterator<iterator> reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        */
        
        public:

        //default constructor which constructs an empty container
        vector();

        explicit vector(size_type n);

        // Fill constructor which constructs a container with n elements with value val
        explicit vector(size_type n, const value_type& val = value_type());
        
        // range constructor which constructs a container with range first to last
        template<class InputIterator>
        vector(InputIterator first, InputIterator last);



        ~vector();
        
        // Copy Constructor 
        vector(vector const& rhs);
        vector<T, Allocator>&          operator=(vector<T, Allocator> const &rhs);

        // Methods 
        void                swap(vector& other);

        // Non Mutating Functions 
        size_type           size() const{return (static_cast<size_type>(_length - _begin));}
        bool                empty() const{return (_begin == _length);}

        // Validated element access 
        reference           at(size_type index){validateIndex(index); return ((*this)[index]);}
        const_reference     at(size_type index) const{validateIndex(index); return ((*this)[index]);}

        // Non Validated element access 
        reference           operator[](size_type index);
        const_reference     operator[](size_type index) const;
        reference           front(){return (*_begin);}
        const_reference     front() const{return (*_begin);}
        reference           back(){return (*(_length - 1));}
        const_reference     back() const{return (*(_length - 1));}

        // Iterators 
        iterator            begin(){return (_begin);}
        //reverse_iterator           rbegin(){return (reverse_iterator(end()));};
        const_iterator      begin() const{return (_begin);}
        //const_reverse_iterator     rbegin() const{return (const_riterator(end()));};

        iterator            end(){return (_length);}
        //reverse_iterator    rend(){return (reverse_iterator(begin()));};
        const_iterator      end() const{return (_length);}
        //const_reverse_iterator     rend() const{return (const_reverse_iterator(begin()));};

        const_iterator      cbegin() const{return (begin());};
        //const_reverse_iterator     crbegin() const{return (rbegin());};
        const_iterator      cend() const{return (end());};
        //const_reverse_iterator     crend() const{return (rend());};

        //Comparison Operators 
        //bool                operator!=(vector const &rhs) const {return !(*this == rhs);};
        //bool                operator==(vector const &rhs) const {return (size() == rhs.size() && std::equal(begin(), end(), rhs.begin()));};
        
        // Mutating Functions 
        void                push_back(T const &value);
        void                pop_back();
        void                reserve(size_type capacityUpperBound);

        private:
        
        allocator_type      _alloc;
        iterator           _begin; 
        iterator           _length; 
        iterator           _capacity;
        
        void                fill_and_initialise(size_type n, const value_type& val);
        void                initialise_space(size_type n, size_type cap );
        template<class Iter>
        void                range_initialise(Iter first, Iter last);
        void                destroy_and_recover(iterator first, iterator last, size_type n);
        void                resize_if_req();
        void                pushBackInternal(T const &value);
        void                validateIndex(size_type index) const {if (index >= _length) throw std::out_of_range("Out of Range");};
        void                reserveCapacity(size_type newCapacity);
    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif