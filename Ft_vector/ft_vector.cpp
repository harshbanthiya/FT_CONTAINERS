/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:55 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/06 15:12:20 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_CPP
#define FT_VECTOR_CPP 

#include "ft_vector.hpp"
namespace ft
{   
    template<typename T>
    Vector<T>::Vector(int capacity) : _capacity(capacity), _length(0), buffer(static_cast <T *>(::operator new(sizeof(T) * _capacity)))
    { 
        std::cout << "Vec constructor called\n";    
    }
    
    template<typename T>
    Vector<T>::~Vector()
    {
        for(std::size_t loop = 0; loop < _length; ++loop)
        {
            buffer[_length - 1 - loop].~T(); // Destroy elements in reverse order 
        }
        ::operator delete(buffer);
    }
    
    template<typename T>
    Vector<T>::Vector(Vector const& rhs) : _capacity(rhs._capacity), _length(rhs._length), buffer(static_cast<T *>(::operator new(sizeof(T) * rhs._capacity)))
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
    }
    // To get the strong exception guarantee, I need to dump in a intermediate buffer, a copy swap 
    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T> const &rhs)
    {   
        if (&rhs == this)
            return (*this);
        // Create Copy 
        std::size_t tmpCap = rhs._length;
        std::size_t tmpSize = 0;
        T*          tmpBuffer = static_cast<T*>(::operator new(sizeof(T) * tmpCap));
        
        for (std::size_t loop = 0; loop < _length; ++loop)
        {
            //Destroy in reverse 
            buffer[_length - 1 - loop].~T();
        }
        _length = 0;
        // Reset buffer and copy all 
        for (std::size_t loop = 0; loop < _length; ++loop)
        {
            push_back(rhs.buffer[loop]);
        }
        return (*this);
    }
    
    template<typename T>
    void Vector<T>::swap(Vector& other)
    {
            std::swap(_capacity, other._capacity);
            std::swap(_length, other._length);
            std::swap(buffer, other.buffer);
    }

    template<typename T>    
    void Vector<T>::push_back(T const &value)
    {
        resize_if_req();
        new (buffer + _length) T (value);
        ++_length;
            // handle growing the capacity later 
    }

    template<typename T>
    void Vector<T>::pop_back()
    {
            // manually call the destructor 
            --_length;
            buffer[_length].~T();
    }

}


#endif
