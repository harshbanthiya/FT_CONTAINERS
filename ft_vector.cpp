/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:39:55 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/24 15:54:52 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_CPP
#define FT_VECTOR_CPP 

#include "ft_vector.hpp"
namespace ft
{
    /*----------------------------------------------------------------------------*/
    /* Private Member functions ***************************************************/
    /*----------------------------------------------------------------------------*/
    
    template<typename T, typename Allocator>
    void vector<T,Allocator>::initialise_space(size_type n, size_type cap)
    {
        try
        {
            _begin = static_cast<T*>(_alloc.allocate(cap));
            _length = _begin + n;
            _capacity = _begin + cap;
        }
        catch(...)
        {
            _begin = nullptr;
            _length = nullptr;
            _capacity = nullptr;
            throw ;
        }
    }

    template<typename T, typename Allocator>
    void vector<T,Allocator>::fill_and_initialise(size_type n, const value_type &val)
    {
        const size_type init_size = std::max(static_cast<size_type>(16), n);
        initialise_space(n, init_size);
        std::uninitialized_fill_n(_begin, n, val);
    }

    template<typename T, typename Allocator>
    template<class Iter>
    void vector<T,Allocator>::range_initialise(Iter first, Iter last)
    {
        const size_type init_size = std::max(static_cast<size_type>(last - first),
                                                static_cast<size_type>(16));
        initialise_space(static_cast<size_type>(last - first), init_size);
        std::copy(first, last, _begin);
    }

    template<typename T, typename Allocator>
    void  vector<T, Allocator>::destroy_and_recover(iterator first, iterator last, size_type n)
    {
        for(iterator i = first; i <= last; ++i)
        {
            i->~T();
        }
        _alloc.deallocate(first, n);
    }

    /*******************************************************************************/
    /*/////////////////////////////////////////////////////////////////////////////*/
    /*******************************************************************************/
    
    
    /*-----------------------------------------------------------------------------*/
    /* Constructors and destructor *************************************************/
    /*-----------------------------------------------------------------------------*/
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector() : _alloc(std::allocator<T>())
    {
        try
        {
            _begin = static_cast<T*>(_alloc.allocate(16));
            _length = _begin;
            _capacity = _begin + 16;
            std::cout << "Constructor super default, no except called\n";
        }
        catch(...)
        {
            _begin = nullptr;
            _length = nullptr;
            _capacity = nullptr;
        }
        
    }
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type n) : _alloc(std::allocator<T>())
    {
        fill_and_initialise(n, value_type());
        std::cout << "Constructor with number of elements called\n";
    }
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type num, const value_type& val) : _alloc(std::allocator<T>())
    {
        fill_and_initialise(num, val);
        std::cout <<  "Constructor with number of elements and their values called\n";
    }

    template<typename T, typename Allocator>
    template<class InputIterator>    
    vector<T, Allocator>::vector(InputIterator first, InputIterator last) : _alloc(std::allocator<T>())
    {
            FT_STL_DEBUG(!(last < first));
            range_initialise(first, last);
            std::cout <<  "Range Constructor called\n";
    }
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::~vector()
    {
        destroy_and_recover(_begin, _length, _capacity - _begin);
        _begin = _length = _capacity = nullptr; 
        std::cout <<  "Destructor called\n"; 
    }
    
    template<typename T, typename Allocator>
    vector<T, Allocator>::vector(vector<T, Allocator> const& rhs)
    {
        range_initialise(rhs._begin, rhs._length);
    }
    
    /*******************************************************************************/
    /*/////////////////////////////////////////////////////////////////////////////*/
    /*******************************************************************************/

    /*-----------------------------------------------------------------------------*/
    /* Operator overloaders *************************************************/
    /*-----------------------------------------------------------------------------*/
    
    template <typename T, typename Allocator> // copy assignment operator
    vector<T, Allocator>& vector<T, Allocator>::operator=(vector<T, Allocator> const &rhs)
    {   

            if (this != &rhs)
            {
                const std::size_t len = rhs.size();
                if (len > (_capacity - _begin))
                {
                    vector tmp(rhs._begin, rhs._length);
                    swap(tmp);
                }
                else if ((_capacity - _begin) >= len)
                {
                    std::copy(rhs._begin, rhs._length, _begin); // Destructor call check here
                    _length = _begin + len;
                }
                else
                {
                    std::copy(rhs._begin, rhs._begin + rhs.size(), _begin);
                    std::uninitialized_copy(rhs._begin + size(), rhs._length, _length);
                    _capacity  = _length = _begin + len;
                }
            }
        return (*this);
    }

    /*******************************************************************************/
    /*/////////////////////////////////////////////////////////////////////////////*/
    /*******************************************************************************/
    
    /*----------------------------------------------------------------------------*/
    /* Member functions for inserting one or more values **************************/
    /*----------------------------------------------------------------------------*/

    template<typename T, typename Allocator>
    void vector<T,Allocator>::fill_and_assign(size_type n, const value_type& val)
    {
        if (n < capacity())
        {
            vector tmp(n, val);
            swap(tmp);
        }
        else if (n > size())
        {
            std::fill(_begin(), _length(), val);
            _length = std::uninitialized_fill_n(_length, n - size(), val);
        }
        else 
        {
            erase(std::fill_n(_begin, n, val), _length);
        }
    }

    template<typename T, typename Allocator>
    template<typename Iiter>
    void vector<T,Allocator>::copy_and_assign(Iiter first, Iiter last, input_iterator_tag)
    {
        iterator curr = _begin;
        for (; first != last && curr != _length; ++first, ++curr)
            *curr = *first;
        if (first == last)
            erase(curr, _length);
        else 
            insert(_length, first, last);
    }

    template<typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::fill_and_insert(vector<T, Allocator>::iterator pos, size_type n, const value_type& val)
    {
        if (n == 0)
            return (pos);
        const size_type xpos = pos - _begin;
        const value_type value_copy = val;
        if (static_cast<size_type>(_capacity - _length) >= n)
        {
            // Spare space is greater than or equal ot increased spaces
            const size_type after_elems = _length - pos;
            iterator old_len = _length;
            if (after_elems > n)
            {
                std::uninitialized_copy(_length - n, _length, _length);
                _length += n;
                std::move_backward(pos, old_len - n, old_len);
                std::uninitialized_fill_n(pos, n, value_copy);
            }
            else 
            {
                _length = std::uninitialized_fill_n(_length, n - after_elems, value_copy);
                _length = std::move(pos, old_len, _length);
                std::uninitialized_fill_n(pos, after_elems, value_copy);
            }
        }
        else 
        {
            // if there is not enough space 
            const size_type  new_size = get_new_capacity(n);
            const iterator  new_begin = _alloc.allocate(new_size);
            const iterator  new_length = new_begin;
            
            try
            {
                new_length = std::move(_begin, pos, new_begin);
                new_length = std::uninitialized_fill_n(new_length, n, val);
                new_length = std::move(pos, _length, new_length);
            }   
            catch(...)
            {
                destroy_and_recover(new_begin, new_length, new_size);
                throw;
            }
            _alloc.deallocate(_begin, _capacity - _begin);
            _begin = new_begin;
            _length = new_length;
            _capacity = _begin + new_size;
            
        }
        return (_begin + xpos);
    }
    
    /*******************************************************************************/
    /*/////////////////////////////////////////////////////////////////////////////*/
    /*******************************************************************************/    

    /*
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
    */
} // namespace 

#endif
