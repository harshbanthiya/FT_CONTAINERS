/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/11/17 10:38:23 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Iterator.hpp"
#include <iterator>


namespace ft
{
    template<typename T, typename Allocator = std::allocator<T> > 
    class vector
    {
        
        public:
        
        typedef Allocator                                       allocator_type;
        typedef  T                                              value_type;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::difference_type        difference_type;
        typedef value_type*                                     iterator;
        typedef const value_type*                               const_iterator;
    
        
        /* Constructors and destructor *************************************************/

        vector(const Allocator& = Allocator()); // Default constructor 
        explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator());  
        // constructs a vector size n and initializes all its elements with value

        // copy constructor
        vector(const vector<T, Allocator>& x);

        template<typename InputIterator>
        vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
        // constructs a vector of size last - first and initializes it with copies of elements in that range [first, last)

        // Assignment Operator 
        vector<T, Allocator>& operator=(const vector<T, Allocator>& x);

        template<typename InputIterator>
        void assign(InputIterator first, InputIterator last);
        // {clear(), insert(begin(), first, last);}
        void assign(size_type n, const T& u);
        // {clear(), insert(begin(), n, u);}

        void reserve(size_type n);

        // Destructor 
        ~vector();

        void swap(vector<T, Allocator>& x);

        /* Comparison operators *************************************************/

        template<typename T, typename Allocator>
        bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
        
        template <typename T, typename Allocator>
        bool operator<(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
        // Return true if x is lexicographically less than y, false otherwise

        /* Element Access operators *************************************************/

        

        /*-----------------------------------------------------------------------------*/
        /* Member functions for accessing value ****************************************/
        /*-----------------------------------------------------------------------------*/
        
        reference                       at(size_type index){validateIndex(index); return ((*this)[index]);}
        const_reference                 at(size_type index) const{validateIndex(index); return ((*this)[index]);}
        reference                       front(){return (*_begin);}
        const_reference                 front() const{return (*_begin);}
        reference                       back(){return (*(_length - 1));}
        const_reference                 back() const{return (*(_length - 1));}

        iterator                        begin();
        const_iterator                  begin() const {return (_begin);}
        iterator                        end(){return (_length);}
        const_iterator                  end() const{return (_length);}
        
        //reverse_iterator              rbegin(){return (reverse_iterator(end()));};
        //const_reverse_iterator        rbegin() const{return (const_riterator(end()));};
        //reverse_iterator              rend(){return (reverse_iterator(begin()));};
        //const_reverse_iterator        rend() const{return (const_reverse_iterator(begin()));};

        const_iterator                  cbegin() const{return (begin());};
        const_iterator                  cend() const{return (end());};
        //const_reverse_iterator        crbegin() const{return (rbegin());};
        //const_reverse_iterator        crend() const{return (rend());};

        /*******************************************************************************/
        /*/////////////////////////////////////////////////////////////////////////////*/
        /*******************************************************************************/

        /*-----------------------------------------------------------------------------*/
        /* Member functions for reporting status ***************************************/
        /*-----------------------------------------------------------------------------*/

        size_type                       size()  const;
        size_type                       max_size()  const;

        size_type                       capacity()  const;
        bool                            empty()  const;

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*----------------------------------------------------------------------------*/
        /* Member functions for inserting one or more values **************************/
        /*----------------------------------------------------------------------------*/

        template<class Iter>
        void                            assign(Iter first, Iter last);
        void                            assign(size_type n, const value_type& value);

        template<class Iter>
        iterator                        insert(const_iterator pos, Iter first, Iter last);
        iterator                        insert(const_iterator pos, const value_type& value);
        iterator                        insert(const_iterator pos, value_type& value);
        iterator                        insert(const_iterator pos, size_type n, const value_type& value);

        void                            push_back(const value_type& value);
        void                            push_back(value_type& value);


        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*----------------------------------------------------------------------------*/
        /* Member functions for deleting one or more values ***************************/
        /*----------------------------------------------------------------------------*/

        iterator                        erase(const_iterator pos);
        iterator                        erase(const_iterator first, const_iterator last);
        void                            clear(){erase(begin(), end());}
        void                            pop_back();

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*----------------------------------------------------------------------------*/
        /* Miscellaneous member functions *********************************************/
        /*----------------------------------------------------------------------------*/
        
        void                            swap(vector& other);
        void                            reserve(size_type capacityUpperBound);
        void                            resize(size_type new_size, const value_type& val = T());
        void                            resize(size_type new_size){ return resize(new_size, value_type()); }
        
        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/        

        /*----------------------------------------------------------------------------*/
        /* Private variables and functions ********************************************/
        /*----------------------------------------------------------------------------*/
        private:
        
        allocator_type                  _alloc;
        iterator                        _begin; 
        iterator                        _length; 
        iterator                        _capacity;
        
        void                            fill_and_initialise(size_type n, const value_type& val);
        void                            initialise_space(size_type n, size_type cap);
        template<class Iter>
        void                            range_initialise(Iter first, Iter last);
        void                            destroy_and_recover(iterator first, iterator last, size_type n);
        
        template<class Iiter>
        void                            copy_and_assign(Iiter first, Iiter last, input_iterator_tag);
        void                            fill_and_assign(size_type n, const value_type& value);
        
        template<class Iiter>
        void                            copy_and_insert(iterator pos, Iiter first, Iiter last);
        iterator                        fill_and_insert(iterator pos, size_type n, const value_type& val);
        void                            reallocate_insert(iterator pos, const value_type& val);

        void                            resize_if_req();
        void                            pushBackInternal(T const &value);
        void                            validateIndex(size_type index) const {if (index >= _length) throw std::out_of_range("Out of Range");};
        void                            reserveCapacity(size_type newCapacity);
        
        size_type                       get_new_capacity(size_type add_size);

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif