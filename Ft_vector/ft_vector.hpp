/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/07 12:45:20 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>

namespace ft
{
    template<typename T>
    class Vector
    {
        public:
        std::size_t     _capacity;
        std::size_t     _length;  
        T*              buffer;

        public:
        Vector(int capacity = 10);
        ~Vector();
        
        // Copy Constructor 
        Vector(Vector const& rhs);
        Vector<T>& operator=(Vector<T> const &rhs);

        // Methods 
        void swap(Vector& other);
        void push_back(T const &value);
        void pop_back();
        void reserve(std::size_t capacityUpperBound);
        
        private:
        void resize_if_req();
        void pushBackInternal(T const &value);
        void reserveCapacity(std::size_t newCapacity);
    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif