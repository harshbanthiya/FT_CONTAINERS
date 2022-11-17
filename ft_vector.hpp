#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "Iterator.hpp"

#define FT_NOEXCEPT throw()

namespace ft
{
	template<typename iter>
	class vector_iter
	{
		public:

			typedef iter 																iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<iterator_type>::value_type 			value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type 		difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer 				pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference 				reference;

			// Constructor 
			vector_iter() FT_NOEXCEPT {}
			vector_iter(iterator_type x) FT_NOEXCEPT : it(x) {}

			iterator_type base() const FT_NOEXCEPT {return it;}

			// Operators 
			
			reference	operator*() const FT_NOEXCEPT {return *it;}
			pointer 	operator->() const FT_NOEXCEPT {return it;}

			vector_iter& operator++() FT_NOEXCEPT {++it; return *this;}
			vector_iter  operator++(int) FT_NOEXCEPT {vector_iter tmp(*this); ++(*this); return (tmp);}

			vector_iter& operator--() FT_NOEXCEPT {--it; return *this;}
			vector_iter  operator--(int) FT_NOEXCEPT {vector_iter tmp(*this); --(*this); return (tmp);}

			vector_iter operator+(difference_type n) const FT_NOEXCEPT {vector_iter tmp(*this); tmp += n; return (tmp);}
			vector_iter operator+=(difference_type n) FT_NOEXCEPT {it += n; return (*this);}
			vector_iter operator-(difference_type n) const FT_NOEXCEPT {return (*this + (-n));}
			vector_iter operator-=(difference_type n) FT_NOEXCEPT {*this += -n; return (*this);}
			
			reference 	operator[](difference_type n) const FT_NOEXCEPT {return it[n];}


 		private:

  			iterator_type																it;

	};


	template<typename Iter1, typename Iter2>
	inline bool operator==(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (x.base() == y.base());}
	template<typename Iter1, typename Iter2>
	inline bool operator!=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return !(x.base() == y.base());}

	template<typename Iter1, typename Iter2>
	inline bool operator<(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (x.base() < y.base());}
	template<typename Iter1, typename Iter2>
	inline bool operator>(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (y < x);}
	template<typename Iter1, typename Iter2>
	inline bool operator<=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return !(y < x);}
	template<typename Iter1, typename Iter2>
	inline bool operator>=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return !(x < y);}

	//template<typename Iter1, typename Iter2>
	//inline bool operator-(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (x.base() < y.base());}
	//template<typename Iter1, typename Iter2>
	//inline bool operator>(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (y < x);}


	template <typename T, typename Allocator = std::allocator<T>()>
	class vector
	{
		public:

			typedef T                                        	value_type;
			typedef Allocator                                	allocator_type;
			typedef typename allocator_type::reference       	reference;
			typedef typename allocator_type::const_reference 	const_reference;
			typedef typename allocator_type::size_type       	size_type;
			typedef typename allocator_type::difference_type 	difference_type;
			typedef typename allocator_type::pointer         	pointer;
			typedef typename allocator_type::const_pointer   	const_pointer;

			typedef vector_iter									iterator;
			typedef vector_iter                   				const_iterator;
			typedef ft::reverse_iterator<iterator>          	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;


			// Constructor, Destructor and related functions. | * |  

			vector(const Allocator& = Allocator()); // Default 
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator()); // Vector of size n with value 
			
			vector(const vector<T, Allocator>& x); // Copy constructor 
			
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator()); // Range based initialization 
																							 // Construct vector last - first [first, last)		

			vector<T, Allocator>&		operator=(const vector<T, Allocator> &x); // Assignment operator  

			~vector(); // Destructor 

			// Assign 
			template<typename InputIterator>
			void assign(InputIterator first, InputIterator last); // == {clear(); insert(begin(), first, last);}
			void assign(size_type n, const T& u);

			void reserve(size_type n);
			void swap(vector<T, Allocator>& x);

		private:

	};
}

#endif /* ******************************************************* FT_VECTOR_H */