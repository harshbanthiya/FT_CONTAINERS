/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/05 15:03:25 by hbanthiy         ###   ########.fr       */
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
        std::size_t     _capacity;
        std::size_t     _length;  
        T*              buffer;

        public:
        Vector(int capacity = 10) : _capacity(capacity), _length(0), buffer(static_cast <T *>(::operator new(sizeof(T) * _capacity))){ std::cout << "Vec constructor called\n";};
        ~Vector()
        {   
            for(std::size_t loop = 0; loop < _length; ++loop)
            {
                buffer[_length - 1 - loop].~T(); // Destroy elements in reverse order 
            }
            ::operator delete(buffer);
        };
        
        Vector(Vector const& rhs) : _capacity(rhs._capacity), _length(rhs._length), buffer(static_cast<T *>(::operator new(sizeof(T) * rhs._capacity)))
        {
            try
            {
                for (std::size_t loop = 0; loop < rhs._length; ++loop)
                    push_back(rhs.buffer[loop]);
            }
            catch(const std::exception& ex)
            {
                ::operator delete(buffer);
                for(std::size_t loop = 0; loop < _length; ++loop)
                    buffer[_length - 1 - loop].~T();
                throw(ex.what());
            }
        };
        
        Vector& operator=(Vector const &rhs)
        {   
                (void )rhs;
                return *this;
        }
        void swap(Vector& other)
        {
            std::swap(_capacity, other._capacity);
            std::swap(_length, other._length);
            std::swap(buffer, other.buffer);
        }
        
        void push_back(T const &value)
        {
            resize_if_req();
            new (buffer + _length) T (value);
            ++_length;
            // handle growing the capacity later 
        }
        
        void pop_back()
        {
            // manually call the destructor 
            --_length;
            buffer[_length].~T();
        }
        private:
            void resize_if_req()
            {
                if (_length == _capacity)
                {
                    
                }
            }
    };    
        
} // namespace ft   


#endif