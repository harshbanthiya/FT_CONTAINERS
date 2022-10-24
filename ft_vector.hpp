/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:29:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/24 15:52:33 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <memory>
#include "ft_stdexcept.hpp"
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
        reference                       operator[](size_type index){FT_STL_DEBUG(index < size()); return *(_begin + index);}
        const_reference                 operator[](size_type index) const{FT_STL_DEBUG(index < size()); return *(_begin + index);}
        
        bool                            operator==(vector const &lhs, vector const &rhs) {return(lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));}
        bool                            operator<( vector const &lhs,  vector const &rhs)  {return(std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end()));}
        bool                            operator!=( vector const &lhs,  vector const &rhs) {return !(lhs == rhs);}
        bool                            operator>( vector const &lhs,  vector const &rhs)  {return (rhs < lhs);}
        bool                            operator<=( vector const &lhs,  vector const &rhs) {return !(rhs <lhs);}
        bool                            operator>=( vector const &lhs,  vector const &rhs) {return !(lhs < rhs);}

        /*******************************************************************************/
        /*/////////////////////////////////////////////////////////////////////////////*/
        /*******************************************************************************/

        /*-----------------------------------------------------------------------------*/
        /* Member functions for accessing value ****************************************/
        /*-----------------------------------------------------------------------------*/
        
        reference                       at(size_type index){THROW_OUT_OF_RANGE_IF(!(index < size()), "Vector<T>::at() out of range!"); return ((*this)[index]);}
        const_reference                 at(size_type index) const{THROW_OUT_OF_RANGE_IF(!(index < size()), "Vector<T>::at() out of range!"); return ((*this)[index]);}
        reference                       front(){FT_STL_DEBUG(!(empty())); return (*_begin);}
        const_reference                 front() const{FT_STL_DEBUG(!(empty())); return (*_begin);}
        reference                       back(){FT_STL_DEBUG(!(empty())); return (*(_length - 1));}
        const_reference                 back() const{FT_STL_DEBUG(!(empty())); return (*(_length - 1));}

        iterator                        begin() {return (_begin);}
        const_iterator                  begin() const{return (_begin);}
        iterator                        end(){return (_length);}
        const_iterator                  end() const{return (_length);}

        const_iterator                  cbegin() const{return (begin());};
        const_iterator                  cend() const{return (end());};
        
        //reverse_iterator              rbegin(){return (reverse_iterator(end()));};
        //const_reverse_iterator        rbegin() const{return (const_riterator(end()));};
        //reverse_iterator              rend(){return (reverse_iterator(begin()));};
        //const_reverse_iterator        rend() const{return (const_reverse_iterator(begin()));};

        //const_reverse_iterator        crbegin() const{return (rbegin());};
        //const_reverse_iterator        crend() const{return (rend());};

        /*******************************************************************************/
        /*/////////////////////////////////////////////////////////////////////////////*/
        /*******************************************************************************/

        /*-----------------------------------------------------------------------------*/
        /* Member functions for reporting status ***************************************/
        /*-----------------------------------------------------------------------------*/

        size_type                       size()  const {return (static_cast<size_type>(_length - _begin));}
        size_type                       max_size()  const{return (static_cast<size_type>(-1) / sizeof(T));}
        size_type                       capacity()  const {return (static_cast<size_type>(_capacity - _begin));};
        bool                            empty()  const{return (_begin == _length);}

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*----------------------------------------------------------------------------*/
        /* Member functions for inserting one or more values **************************/
        /*----------------------------------------------------------------------------*/

        template<class Iter>
        void                            assign(Iter first, Iter last){FT_STL_DEBUG(!(last, first)); copy_and_assign(first, last, my_iterator_category(first));}
        void                            assign(size_type n, const value_type& value){fill_and_assign(n, value);}

        template<class Iter>
        iterator                        insert(const_iterator pos, Iter first, Iter last){FT_STL_DEBUG(pos >= begin() && pos <= end() && !(last < first)); return (copy_and_insert(const_cast<iterator>(pos), first, last));}
        iterator                        insert(const_iterator pos, const value_type& value);
        iterator                        insert(const_iterator pos, size_type n, const value_type& value) {FT_STL_DEBUG(pos >= begin() && pos <= end()); return (fill_and_insert(const_cast<iterator>(pos), n, value));}
        void                            push_back(const value_type& value);
 
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
        
        template<class Iter>
        void                            range_initialise(Iter first, Iter last);
        void                            fill_and_initialise(size_type n, const value_type& val);
        void                            initialise_space(size_type n, size_type cap);
        void                            destroy_and_recover(iterator first, iterator last, size_type n);
        
        template<class Iiter>
        void                            copy_and_assign(Iiter first, Iiter last, input_iterator_tag);
        void                            fill_and_assign(size_type n, const value_type& value);
        
        template<class Iiter>
        void                            copy_and_insert(iterator pos, Iiter first, Iiter last);
        iterator                        fill_and_insert(iterator pos, size_type n, const value_type& val);

        void                            resize_if_req();
        void                            pushBackInternal(T const &value);
        void                            reserveCapacity(size_type newCapacity);
        

        /******************************************************************************/
        /*////////////////////////////////////////////////////////////////////////////*/
        /******************************************************************************/

        /*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

    };    
        
} // namespace ft   

#include "ft_vector.cpp"

#endif