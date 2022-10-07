/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/07 16:41:36 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iterator>

namespace ft
{
    template<typename T>
    class vector
    {
        // Typedefs to use throughout 
        public:
        
        using value_type = T;
        using reference = T&;
        using const_reference = T const&;
        using pointer = T*;
        using const_pointer = T const*;
        using iterator = T*;
        using const_iterator = T const*;
        using riterator = std::reverse_iterator<iterator>;
        using const_riterator = std::reverse_iterator<const_iterator>;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        

        public:

        //Constructors and Destructors 
        vector(int capacity = 10);
        template<typename I>
        vector(I begin, I end);
        ~vector();
        
        // Copy Constructor 
        vector(vector const& rhs);
        vector<T>&          operator=(vector<T> const &rhs);

        // Methods 
        void                swap(vector& other);

        // Non Mutating Functions 
        size_type           size() const{return (_length);};
        bool                empty() const{return (_length == 0);};

        // Validated element access 
        reference           at(size_type index){validateIndex(index); return (buffer[index]);};
        const_reference     at(size_type index) const{validateIndex(index); return (buffer[index]);};

        // Non Validated element access 
        reference           operator[](size_type index){return (buffer[index]);};
        const_reference     operator[](size_type index) const{return (buffer[index]);};
        reference           front(){return (buffer[0]);};
        const_reference     front() const{return (buffer[0]);};
        reference           back(){return (buffer[_length - 1]);};
        const_reference     back() const{return (buffer[_length - 1]);};

        // Iterators 
        iterator            begin(){return (buffer);};
        riterator           rbegin(){return (riterator(end()));};
        const_iterator      begin() const{return (buffer);};
        const_riterator     rbegin() const{return (const_riterator(end()));};

        iterator            end(){return (buffer + _length);};
        riterator           rend(){return (riterator(begin()));};
        const_iterator      end() const{return (buffer + _length);};
        const_riterator     rend() const{return (const_riterator(begin()));};

        const_iterator      cbegin() const{return (begin());};
        const_riterator     crbegin() const{return (rbegin());};
        const_iterator      cend() const{return (end());};
        const_riterator     crend() const{return (rend());};

        //Comparison Operators 
        bool                operator!=(vector const &rhs) const {return !(*this == rhs);};
        bool                operator==(vector const &rhs) const {return (size() == rhs.size() && std::equal(begin(), end(), rhs.begin()));};
        
        // Mutating Functions 
        void                push_back(T const &value);
        void                pop_back();
        void                reserve(std::size_t capacityUpperBound);

        private:
        
        std::size_t         _capacity;
        std::size_t         _length;  
        T*                  buffer;

        void                resize_if_req();
        void                pushBackInternal(T const &value);
        void                validateIndex(size_type index) const {if (index >= _length) throw std::out_of_range("Out of Range");};
        void                reserveCapacity(std::size_t newCapacity);
    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif