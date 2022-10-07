/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:55 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/07 12:45:19 by hbanthiy         ###   ########.fr       */
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
    
    // To get the strong exception guarantee, I need to dump in a intermediate buffer
    // essentially creating a copy swap operation. 
     
    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T> const &rhs)
    {   
        if (&rhs == this)
            return (*this);

        // Create copy is function scope, frees itself automatically 
        // at closing brace of this function 
        Vector tmp(rhs);
        
        // Swap
        tmp.swap(*this);
        
        return (*this);
    }
    
    template<typename T>
    void Vector<T>::reserve(std::size_t capacityUpperBound)
    {
        if (capacityUpperBound > _capacity)
            reserveCapacity(capacityUpperBound);
    }
    

    template<typename T>
    void Vector<T>::resize_if_req()
    {
        if (_length == _capacity)
        {
            // Create tmp obj with larger capacity
            std::size_t     newCapacity = std::max(2.0, _capacity * 1.5);
            reserveCapacity(newCapacity);
        }
    }
    
    template<typename T>
    void Vector<T>::pushBackInternal(T const &value)
    {
        new(buffer + _length) T(value);
        ++_length;
    }

    template<typename T>
    void Vector<T>::reserveCapacity(std::size_t newCapacity)
    {
        Vector<T> tmpBuffer(newCapacity);
        std::for_each(buffer, buffer + _length, [&tmpBuffer] (T const& v) {tmpBuffer.pushBackInternal(v);});
        tmpBuffer.swap(*this);
    }
    

    template<typename T>
    void Vector<T>::swap(Vector<T>& other)
    {
        std::swap(_capacity, other._capacity);
        std::swap(_length, other._length);
        std::swap(buffer, other.buffer);
    }

    template<typename T>    
    void Vector<T>::push_back(T const &value)
    {
        resize_if_req();
        pushBackInternal(value);
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
