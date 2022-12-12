/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:36:48 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/12/12 13:40:15 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILITY_HPP
# define UTILITY_HPP
#include <functional>
namespace ft
{

	//utility pair -- can hold two different types

	template <typename T1, typename T2>
	struct pair
	{

		typedef	T1	first_type;
		typedef	T2	second_type;

		T1	first;
		T2	second;

		pair(): first(), second() {}
		template <typename U1, typename U2> 
		pair (const pair<U1, U2> &pr): first(pr.first), second(pr.second) {}
		pair(const T1 &a, const T2 &b): first(a),  second(b) {}

		pair&	operator=(pair const &right)
		{
			first = right.first;
			second = right.second;

			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return lhs.first < rhs.first ||
			(!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs < rhs);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(rhs < lhs);
	}

	//function template to return a pair object with two different types
	//making it inline to improve code execution time

	template <typename T1, typename T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	// Swap and select first 
	template <typename T>
	void swap(T &x, T& y)
	{
		T tmp(x);
		x = y;
		y = tmp;
	}

	template <typename pair>
	struct select_first
	{
		typename pair::first_type &operator()(pair &x) const {return x.first;}
		const typename pair::first_type &operator()(const pair &x) const {return x.first;}
	};

	template <typename T>
	struct identity
	{
		T &operator()(T &x) const {return x;} 
		const T &operator() (const T &x) const {return x;}
	};

} //end namespace

#endif
