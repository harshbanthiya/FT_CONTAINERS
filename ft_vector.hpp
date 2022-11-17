#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "Iterator.hpp"

#define FT_NOEXCEPT throw()

namespace ft
{

	// Vector base class
	template<typename _T, class _Allocator = std::allocator<_T>()>
	class vector_base
	{
		public:
		
			typedef _Allocator								allocator_type;
			typedef allocator_traits<allocator_type>		_alloc_traits;
			typedef typename _alloc_traits::size_type		size_type;
		
		protected:

			typedef _T										value_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename _alloc_traits::difference_type difference_type;
			typedef typename _alloc_traits::pointer 		pointer;
			typedef typename _alloc_traits::const_pointer 	const_pointer;

			pointer											_begin;
			pointer 										_end;
			pointer 										_capacity;
			allocator_type									_a;
		
			// Constructors and Destructor
			
			vector_base() FT_NOEXCEPT;
  			vector_base(const allocator_type& a) FT_NOEXCEPT;
  			vector_base(size_type n);
  			vector_base(size_type n, const allocator_type& alloc);
  			~vector_base() FT_NOEXCEPT {if (__begin) _a_.deallocate(_begin_, capacity());}
		
			// Storage Management Functions 

			pointer 	construct_storage(size_type n) {return (n == 0 ? pointer() : _a.allocate(n));}
			void		destruct_storage() FT_NOEXCEPT;

			size_type 	capacity() const FT_NOEXCEPT { return static_cast<size_type>(_capacity - _begin);}
			size_type 	check_length(size_type n) {if (n > a.max_size()) _throw_length_error("Vector: Size too big"); return n;}

			void 		copy_data(vector_base const &other) FT_NOEXCEPT;
			void 		copy_data(pointer const& _new_begin, pointer const& _new_end, pointer const& new_cap) FT_NOEXCEPT;
			void 		swap_data(vector_base& other) FT_NOEXCEPT;

			// Error Functions 

			void		_throw_out_of_range(const char *msg) const {throw std::out_of_range(msg);}
			void		_throw_length_error(const char *msg) const {throw std::length_error(msg);}

		private:

			vector_base(const vector_base& other) {(void)other;}
			vector_base& operator=(const vector_base& other) {(void) other;}
	};


	// Functions from vector base class 
		// -- Vector Base Constructors

		template<typename T, typename _Allocator>
		vector_base<T, _Allocator>::vector_base() FT_NOEXCEPT : _begin(NULL), _end(NULL), _capacity(NULL), _a(std::allocator<T>()) {}

		template<typename T, typename _Allocator>
		vector_base<T, _Allocator>::vector_base(const allocator_type& a) FT_NOEXCEPT : _begin(NULL), _end(NULL), _capacity(NULL), _a(a) {}

		template<typename T, typename _Allocator>
		vector_base<T, _Allocator>::vector_base(size_type n) FT_NOEXCEPT : _a(std::allocator<T>()) {_begin = construct_storage(n); _end = _begin; _capacity = _begin + n;}

		template<typename T, typename _Allocator>
		vector_base<T, _Allocator>::vector_base(size_type n, const allocator_type& a) FT_NOEXCEPT : _a(a) {_begin = construct_storage(n); _end = _begin; _capacity = _begin + n;}

		
		// -- Vector Base Storage Management 

		template<typename T, typename _Allocator>
		void vector_base<T, _Allocator>::copy_data(vector_base const& other) FT_NOEXCEPT {_begin = other._begin; _end = other._end; _capacity = other._capacity;}

		template<typename T, typename _Allocator>
		void vector_base<T, _Allocator>::copy_data(pointer const& b, pointer const& e, pointer const& c)  FT_NOEXCEPT {_begin = b; _end = e; _capacity = c;}

		template<typename T, typename _Allocator>
		void vector_base<T, _Allocator>::swap_data(vector_base &other) FT_NOEXCEPT
		{
			pointer tmp_begin(_begin);
			pointer tmp_end(_end);
			pointer tmp_cap(_capacity);
			allocator_type tmp_a(_a);

			this->copy_data(other);
			this->_a = other._a;
			other.copy_data(tmp_begin, tmp_end, tmp_cap);
			other.a - tmp_a;
		}

		template<typename T, typename _Allocator>
		void vector_base<T, _Allocator>::destruct_storage() FT_NOEXCEPT
		{
			_a.deallocate(_begin, capacity());
			_end = _begin = _capacity = NULL;
		}
	

	// Vector Iterator Class 
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

  			iterator_type														it;

	};

	// Vector Non Member Operations 
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

	template<typename Iter1, typename Iter2>
	inline typename vector_iter<Iter1>::difference_type operator-(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) FT_NOEXCEPT {return (x.base() - y.base());}
	template<typename Iter1>
	inline vector_iter<Iter1> operator+(typename vector_iter<Iter1>::difference_type n, const vector_iter<Iter1> x) FT_NOEXCEPT {x += n; return (x);}

	// Vector main class 
	template <typename T, typename Allocator = std::allocator<T> >
	class vector : private vector_base<T, Allocator>
	{
		static_assert(!std::is_same<bool, T>::value, "vector<bool> is not supported in my containers implementation.");
		
		private: 
			typedef vector_base<T, Allocator>					base;

		public:

			typedef T                                        	value_type;
			typedef Allocator                         			allocator_type;
			typedef typename base::reference       				reference;
			typedef typename base::const_reference 				const_reference;
			typedef typename base::size_type       				size_type;
			typedef typename base::difference_type 				difference_type;
			typedef typename base::pointer         				pointer;
			typedef typename base::const_pointer   				const_pointer;

			typedef vector_iter<pointer>						iterator;
			typedef vector_iter<const_pointer>                  const_iterator;
			//typedef ft::reverse_iterator<iterator>          	reverse_iterator;
			//typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;


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
			iterator	begin;
			iterator 	end;
			iterator 	capacity;
	};
}

#endif /* ******************************************************* FT_VECTOR_H */