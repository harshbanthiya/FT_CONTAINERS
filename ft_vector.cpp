/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:55 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/13 14:13:43 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_CPP
#define FT_VECTOR_CPP 

#include "ft_vector.hpp"
namespace ft
{   
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(const allocator_type& alloc) : _alloc(alloc), _capacity(2), _length(0), buffer(_alloc.allocate(_capacity))
    {
        std::uninitialized_fill(buffer, buffer + _capacity, 0);
    }

    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type num, const T& val, const Allocator& a) : _alloc(a)
    {
        _capacity = num;
        _length = num;
        buffer = _alloc.allocate(num);

        // initialize elements 
        std::uninitialized_fill_n(buffer, num, val);     
    }

    template<typename T, typename Allocator>
    vector<T, Allocator>::~vector()
    {
        for(std::size_t loop = 0; loop < _length; ++loop)
        {
            buffer[_length - 1 - loop].~T(); // Destroy elements in reverse order 
        }
        ::operator delete(buffer);
        std::cout << "Vec Destructor called\n";    
    }
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(vector<T, Allocator> const& rhs) : _capacity(rhs._capacity), _length(0), buffer(static_cast<T *>(::operator new(sizeof(T) * _capacity)))
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
     
    template <typename T, typename Allocator>
    vector<T, Allocator>& vector<T, Allocator>::operator=(vector<T, Allocator> const &rhs)
    {   
        if (&rhs == this)
            return (*this);

        // Create tmp stack vector in function scope, frees itself automatically 
        // at closing brace of this function 
        vector tmp(rhs);
        
        // Swap
        tmp.swap(*this);
        
        return (*this);
    }
    
    template<typename T, typename Allocator>
    void vector<T, Allocator>::reserve(size_type capacityUpperBound)
    {
        // reserve never shrinks memory
        if (capacityUpperBound <= _capacity)
            return ;
        if (capacityUpperBound > _capacity)
            reserveCapacity(capacityUpperBound);
    }
    

    template<typename T, typename Allocator>
    void vector<T, Allocator>::resize_if_req()
    {
        if (_length == _capacity)
        {
            // Create tmp obj with larger capacity
            std::size_t     newCapacity = std::max(2.0, _capacity * 1.5);
            reserveCapacity(newCapacity);
        }
    }
    
    template<typename T, typename Allocator>
    void vector<T, Allocator>::pushBackInternal(T const &value)
    {
        uninitialized_fill(buffer, _length, value);
        ++_length;
    }

    template<typename T, typename Allocator>
    void vector<T, Allocator>::reserveCapacity(size_type newCapacity)
    {
        // Allocate new memory
        T * tmp_buffer = _alloc.allocate(newCapacity);
        // Copy old elements into new memory
        std::uninitialized_copy(buffer, buffer + _length, tmp_buffer);
        // Destroy old elements 
        for (size_type i = 0; i < _length; ++i)
            _alloc.destroy(&buffer[i]);
        // Deallocate old memory
        _alloc.deallocate(buffer, _capacity);

        // Update
        _capacity = newCapacity;
        buffer = tmp_buffer;
    }
    

    template<typename T, typename Allocator>
    void vector<T, Allocator>::swap(vector<T, Allocator>& other)
    {
        std::swap(_capacity, other._capacity);
        std::swap(_length, other._length);
        std::swap(buffer, other.buffer);
    }

    template<typename T, typename Allocator>    
    void vector<T, Allocator>::push_back(T const &value)
    {
        resize_if_req();
        pushBackInternal(value);
    }

    template<typename T, typename Allocator>
    void vector<T, Allocator>::pop_back()
    {
            // manually call the destructor 
            --_length;
            buffer[_length].~T();
    }   

} // namespace 

#endif
