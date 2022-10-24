/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/24 16:10:05 by hbanthiy         ###   ########.fr       */
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
#include "MyIterator.hpp"

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
    
        /*-----------------------------------------------------------------------------*/
        /* Constructors and destructor *************************************************/
        /*-----------------------------------------------------------------------------*/

        vector();
        ~vector();
        vector(vector const& rhs);

        explicit vector(size_type n); 
        explicit vector(size_type n, const value_type& val);
        template<class InputIterator>
        vector(InputIterator first, InputIterator last);

        /*******************************************************************************/
        /*/////////////////////////////////////////////////////////////////////////////*/
        /*******************************************************************************/

        /*-----------------------------------------------------------------------------*/
        /* Overloaded operators ********************************************************/
        /*-----------------------------------------------------------------------------*/

        vector<T, Allocator>&           operator=(vector<T, Allocator> const &rhs);
        reference                       operator[](size_type index);
        const_reference                 operator[](size_type index) const;
        
        bool                            operator==(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
        bool                            operator<(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
        bool                            operator!=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
        bool                            operator>(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
        bool                            operator<=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);
        bool                            operator>=(const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs);

        /*******************************************************************************/
        /*/////////////////////////////////////////////////////////////////////////////*/
        /*******************************************************************************/

        /*-----------------------------------------------------------------------------*/
        /* Member functions for accessing value ****************************************/
        /*-----------------------------------------------------------------------------*/
        
        reference                       at(size_type index){validateIndex(index); return ((*this)[index]);}
        const_reference                 at(size_type index) const{validateIndex(index); return ((*this)[index]);}
        reference                       front(){return (*_begin);}
        const_reference                 front() const{return (*_begin);}
        reference                       back(){return (*(_length - 1));}
        const_reference                 back() const{return (*(_length - 1));}

        //reverse_iterator              rbegin(){return (reverse_iterator(end()));};
        const_iterator                  begin() const{return (_begin);}
        //const_reverse_iterator        rbegin() const{return (const_riterator(end()));};

        iterator                        end(){return (_length);}
        //reverse_iterator              rend(){return (reverse_iterator(begin()));};
        const_iterator                  end() const{return (_length);}
        //const_reverse_iterator        rend() const{return (const_reverse_iterator(begin()));};

        const_iterator                  cbegin() const{return (begin());};
        //const_reverse_iterator        crbegin() const{return (rbegin());};
        const_iterator                  cend() const{return (end());};
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
        void                            clear();
        void                            pop_back();

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*----------------------------------------------------------------------------*/
        /* Miscellaneous member functions *********************************************/
        /*----------------------------------------------------------------------------*/
        
        void                            swap(vector& other);
        void                            reserve(size_type capacityUpperBound);
        void                            resize(size_type new_size);
        void                            resize(size_type new_size, const value_type& val);
        
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
        void                            resize_if_req();
        void                            pushBackInternal(T const &value);
        void                            validateIndex(size_type index) const {if (index >= _length) throw std::out_of_range("Out of Range");};
        void                            reserveCapacity(size_type newCapacity);

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif