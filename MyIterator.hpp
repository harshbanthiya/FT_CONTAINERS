/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyIterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:59:30 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/24 13:12:35 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYITERATOR_HPP
# define MYITERATOR_HPP

# include <iostream>
# include <string>
# include <iterator>

namespace ft
{
	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template<class MyIterator>
	struct my_iterator_traits
	{
		typedef typename MyIterator::difference_type difference_type;
		typedef typename MyIterator::value_type value_type;
		typedef typename MyIterator::pointer pointer;
		typedef typename MyIterator::reference reference;
		typedef typename MyIterator::iterator_category iterator_category;
	};

	template<class T>
	struct my_iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	
	template<class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
	struct MyIterator
	{
		typedef T         value_type;
    	typedef Distance  difference_type;
    	typedef Pointer   pointer;
    	typedef Reference reference;
    	typedef Category  iterator_category;
	};

	/*********************************************************/

	// Extract information like category of iter, extract distance type of iter and value_type of iter 

		// Helper Function that returns the category of iterator 
	template<class MyIterator>
	typename my_iterator_traits<MyIterator>::iterator_category
	my_iterator_category(const MyIterator&)
	{
		typedef typename my_iterator_traits<MyIterator>::iterator_category Category;
		return (Category());
	}
		// Helper Functions that returns the distance type of iter
	template<class MyIterator>
	typename my_iterator_traits<MyIterator>::difference_type *
	my_distance_type(const MyIterator&)
	{
		return (static_cast<typename my_iterator_traits<MyIterator>::difference_type *>(0));
	}
		// Helper Function that returns the value type of iter
	template<class MyIterator>
	typename my_iterator_traits<MyIterator>::value_type *
	my_value_type(const MyIterator&)
	{
		return (static_cast<typename my_iterator_traits<MyIterator>::value_type *>(0));
	}

	/*********************************************************/

	// Distance and Advance Basic Functions 
	// General format distance --> overloaded with sub function with specific itercategory 

		// Distance between random access tag 
	template<class RandomIterator>
	typename my_iterator_traits<RandomIterator>::diffference_type
	distance_sub (RandomIterator first, RandomIterator last, random_access_iterator_tag)	
	{
		return (last - first);
	}

		// Distance between input iter tag 
	template<class InputIterator>
	typename my_iterator_traits<InputIterator>::diffference_type
	distance_sub (InputIterator first, InputIterator last, input_iterator_tag)	
	{
		typename my_iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return (n);
	}

		// Main Distance 
	template<class InputIterator>
	typename my_iterator_traits<InputIterator>::diffference_type
	distance (InputIterator first, InputIterator last)
	{
		return (distance_sub(first, last, my_iterator_category(first)));
	}

	// Advance Functions


		// Advance input iter tag
	template<class InputIterator, class Distance>
	void advance_sub (InputIterator& i, Distance n, input_iterator_tag)
	{
		while(n--)
			++i;
	}

	// Advance bidirectional tag
	template<class BidirectionalIterator, class Distance>
	void advance_sub (BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
	{
		if (n >= 0)
		{
			while (n--)
				++i;
		}
		else 
		{
			while (n++)
				--i;
		}
	}

	// Advance random_access_iterator tag
	template<class RandomIterator, class Distance>
	void advance_sub (RandomIterator& i, Distance n, random_access_iterator_tag)
	{
		i += n;
	}

	template<class InputIterator, class Distance>
	void advance (InputIterator& i, Distance n)
	{
		advance_sub(i, n, my_iterator_category(i));
	}
}

#endif /* ****************************************************** MYITERATOR_H */