
#ifndef UTILITY_H
# define UTILITY_H

namespace ft
{

//utility pair -- can hold two different types

template <typename T1, typename T2>
class pair
{
	public:

	typedef	T1	first_type;
	typedef	T2	second_type;

	first_type	first;
	second_type	second;

	pair(void): first(), second() {}
	pair(const first_type & a, const second_type & b): first(a),  second(b) {}
	~pair(void) {}

	template <typename V, typename U> 
	pair (const pair<U, V>& pr): first(pr.first), second(pr.second) {}

	pair const &	operator=(pair const & right)
	{
		first = right.first;
		second = right.second;

		return (*this);
	}
};


//function template to return a pair object with two different types
//making it inline to improve code execution time

template <typename T1, typename T2>
inline pair<T1, T2> make_pair(T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}

} //end namespace

#endif
