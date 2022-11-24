#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator.hpp"

#include <memory>
#include <cstddef>
#include <utility>

#define FT_NOEXCEPT throw()

namespace ft
{

    // Vector base class
	template<typename _T, class _Allocator = std::allocator<_T>()>
	class vector_base
	{
		public:
			typedef _Allocator								    allocator_type;
		
		protected:

			typedef _T										    value_type;
			typedef typename allocator_type::reference	        reference;
			typedef typename allocator_type::const_reference    const_reference;
			typedef typename allocator_type::size_type          size_type;
			typedef typename allocator_type::difference_type    difference_type;
			typedef typename allocator_type::pointer            pointer;
			typedef typename allocator_type::const_pointer      const_pointer;


			pointer											_begin;
			pointer 										_end;
			pointer 										_capacity;
			allocator_type									_a;
		
			// Constructors and Destructor
			
			vector_base() FT_NOEXCEPT;
  			vector_base(const allocator_type& a) FT_NOEXCEPT;
  			vector_base(size_type n);
  			vector_base(size_type n, const allocator_type& alloc);
  			~vector_base() FT_NOEXCEPT {if (_begin) _a.deallocate(_begin, __capacity());}
		
			// Storage Management Functions 

			pointer 	construct_storage(size_type n) {return (n == 0 ? pointer() : _a.allocate(n));}
			void		destruct_storage() FT_NOEXCEPT;

			size_type 	__capacity() const FT_NOEXCEPT { return static_cast<size_type>(_capacity - _begin);}
			size_type 	check_length(size_type n) {if (n > _a.max_size()) throw_length_error("Vector: Size too big"); return n;}

			void 		copy_data(vector_base const &other) FT_NOEXCEPT;
			void 		copy_data(pointer const& _new_begin, pointer const& _new_end, pointer const& new_cap) FT_NOEXCEPT;
			void 		swap_data(vector_base& other) FT_NOEXCEPT;

			// Error Functions 

			void		throw_out_of_range(const char *msg) const {throw std::out_of_range(msg);}
			void		throw_length_error(const char *msg) const {throw std::length_error(msg);}

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
		vector_base<T, _Allocator>::vector_base(size_type n) : _a(std::allocator<T>()) {_begin = construct_storage(n); _end = _begin; _capacity = _begin + n;}

		template<typename T, typename _Allocator>
		vector_base<T, _Allocator>::vector_base(size_type n, const allocator_type& a) : _a(a) {_begin = construct_storage(n); _end = _begin; _capacity = _begin + n;}

		
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
			other._a = tmp_a;
		}

		template<typename T, typename _Allocator>
		void vector_base<T, _Allocator>::destruct_storage() FT_NOEXCEPT
		{
			_a.deallocate(_begin, __capacity());
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
            template <typename U> // copy only when category is random_access
            vector_iter(const vector_iter<U>& _u, typename enable_if<_is_random_access_iterator<U>::value>::type * = 0) FT_NOEXCEPT : it(_u.base()) {}
			vector_iter(iterator_type x) FT_NOEXCEPT : it(x) {}

			const iterator_type& base() const {return it;}

			// Operators 
			
			reference	operator*() const FT_NOEXCEPT {return *it;}
			pointer 	operator->() const FT_NOEXCEPT {return it;}

			vector_iter& operator++() FT_NOEXCEPT {++it; return *this;}
			vector_iter  operator++(int) FT_NOEXCEPT {vector_iter tmp(*this); ++(*this); return (tmp);}

			vector_iter& operator--() FT_NOEXCEPT {--it; return *this;}
			vector_iter  operator--(int) FT_NOEXCEPT {vector_iter tmp(*this); --(*this); return (tmp);}

			vector_iter& operator+=(difference_type n) {it += n; return (*this);}
			vector_iter operator+(difference_type n) const {vector_iter tmp(*this); tmp += n; return (tmp);}
			vector_iter& operator-=(difference_type n) {it -= n; return (*this);}
			vector_iter operator-(difference_type n) const {vector_iter tmp(*this); tmp -=n; return (tmp);}
			
			reference 	operator[](difference_type n) const FT_NOEXCEPT {return it[n];}

 		private:

  			iterator_type														it;

	};

	// Vector Iter Non Member Operations 
	template<typename Iter1, typename Iter2>
	bool operator==(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) {return (x.base() == y.base());}
	template<typename Iter1, typename Iter2>
	bool operator!=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) {return x.base() != y.base();}

	template<typename Iter1, typename Iter2>
    bool operator<(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) {return (x.base() < y.base());}
	template<typename Iter1, typename Iter2>
	bool operator>(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y)  {return (x.base() > y.base());}
	template<typename Iter1, typename Iter2>
	bool operator<=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y)  {return x.base() <= y.base();}
	template<typename Iter1, typename Iter2>
	bool operator>=(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y)  {return x.base() <= y.base();}

	template<typename Iter1, typename Iter2>
	typename vector_iter<Iter1>::difference_type operator-(const vector_iter<Iter1>& x, const vector_iter<Iter2>& y) {return (x.base() - y.base());}
	template<typename Iter1>
	vector_iter<Iter1> operator+(typename vector_iter<Iter1>::difference_type n, const vector_iter<Iter1> x)  {return vector_iter<Iter1>(x.base() + n);}


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
			typedef ft::reverse_iterator<iterator>          	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;


			// Constructor, Destructor and related functions. | * |  

			explicit vector(const allocator_type& alloc = allocator_type()); // Default 
			explicit vector(size_type n);
            explicit vector(size_type n, const value_type& val); // Vector of size n with value no allocator 
			vector(size_type n, const value_type& val, const allocator_type& alloc); // Vector of size n with value 
			
			template <typename InputIterator>   // Construct vector last - first [first, last)		
			vector(InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last, const allocator_type& Alloc = allocator_type()); // Range based initialization 

            template <typename ForwardIterator>   // Construct vector last - first [first, last)		
			vector(ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last, const allocator_type& Alloc = allocator_type()); // Range based initialization 


			vector(const vector<T, Allocator>& x); // Copy constructor 													
			vector&	 operator=(const vector &x); // Assignment operator  


			~vector() FT_NOEXCEPT{ if (this->_begin) {clear(); this->destruct_storage();}} // Destructor 
			allocator_type get_allocator() const FT_NOEXCEPT { return this->_a;}


			// Modifiers 
			template <typename InputIterator>
			void 				        assign(InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last); // == {clear(); insert(begin(), first, last);}
			template <typename ForwardIterator> 
            void 				        assign(ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last); // == {clear(); insert(begin(), first, last);}
			void 				        assign(size_type n, const value_type& u);

			void 				        push_back(const value_type& val);
			void 				        pop_back() FT_NOEXCEPT;

            template <typename InputIterator>
			void 				        insert(iterator position, InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last);
			template <typename ForwardIterator> 
            void 				        insert(iterator position, ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last);
			iterator 			        insert(iterator position, const value_type& val);
			void				        insert(iterator position, size_type n , const value_type& val);
		
			iterator 			        erase(iterator position);
			iterator			        erase(iterator first, iterator last);

			void 				        swap(vector& x){this->swap_data(x);} 
			void 				        clear() FT_NOEXCEPT { if(this->_begin) destroy_from_behind(this->_begin);}	


			// Capacity 
			size_type			        size() const {return ft::distance(this->_begin, this->_end);}
			size_type			        max_size() const { return std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), this->_a.max_size());}
			void 				        resize(size_type n, value_type val = value_type());
			size_type 			        capacity() const {return this->__capacity();}
			bool 				        empty() const {return this->_begin == this->_end;}
			void 				        reserve(size_type n);


			// Element Access 
			reference			        operator[](size_type n) {return reference(*(this->_begin + n));}
			const_reference		        operator[](size_type n) const {return const_reference(*(this->_begin + n));}
			reference 			        at(size_type n) {if (n > this->size()) this->throw_out_of_range("Vector: Out of Range"); return *(this->_begin + n);}
			const_reference 	        at(size_type n) const {if (n > this->size()) this->throw_out_of_range("Vector: Out of Range"); return *(this->_begin + n);}
			reference 			        front() { return *this->_begin;}
			const_reference 	        front() const { return *this->_begin;}
			reference 			        back() { return *(this->_end - 1);}
			const_reference 	        back() const { return *(this->_end - 1);}

			// Iterators 
			iterator 			        begin() FT_NOEXCEPT {return this->_begin;}
			const_iterator 		        begin() const {return this->_begin;}
			iterator 			        end() {return this->_end;}
			const_iterator		        end() const {return this->_end;}
			reverse_iterator		    rbegin() {return reverse_iterator(end());}
			const_reverse_iterator		rbegin() const {return reverse_iterator(end());}
			reverse_iterator		    rend() {return reverse_iterator(begin());}
			const_reverse_iterator		rend() const {return reverse_iterator(begin());}

		private: 

			void				        reconstruct_push_back(const value_type& val);
			void 				        reallocate(size_type n);
			void 				        destroy_from_behind(pointer new_end);		
	};



	// Functions from vector class 
		// -- Vector Constructors

		template<typename T, typename Allocator>
		vector<T, Allocator>::vector(const allocator_type& alloc) : vector_base<T, Allocator>(size_type(), alloc) {}

		template<typename T, typename Allocator>
		vector<T, Allocator>::vector(size_type n) : vector_base<T, Allocator>(n, allocator_type()) { std::uninitialized_fill(this->_begin, this->_begin + n, value_type()); this->_end += n;}

		template<typename T, typename Allocator>
		vector<T, Allocator>::vector(size_type n, const value_type& val) : vector_base<T, Allocator>(n, allocator_type()) {std::uninitialized_fill(this->_begin, this->_begin + n, val); this->_end += n;}

		template<typename T, typename Allocator>
		vector<T, Allocator>::vector(size_type n, const value_type& val, const allocator_type& alloc) : vector_base<T, Allocator>(n, alloc) {std::uninitialized_fill(this->_begin, this->_begin + n, val); this->_end += n;}


        template <typename T, typename Allocator>
        template <typename InputIterator>
        vector<T, Allocator>::vector(InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc) : vector_base<T, Allocator>(size_type(), alloc)
        { for(; first != last; ++first) push_back(*first);}

        template <typename T, typename Allocator>
        template <typename ForwardIterator>
        vector<T, Allocator>::vector(ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last, const allocator_type& alloc) : vector_base<T, Allocator>(static_cast<size_type>(ft::distance(first, last)), alloc)
        { this->_end = std::uninitialized_copy(first, last, this->_begin);}

		// Copy Constructor and Assignment 
		template<typename T, typename Allocator>
		vector<T, Allocator>::vector(const vector<T, Allocator>& other) : vector_base<T, Allocator>(other.capacity())
		{
			clear();
			this->_end = std::uninitialized_copy(other._begin, other._end, this->_begin);
		}

		template<typename T, typename Allocator>
		vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
		{
			if (this != &other)
			{
				if (this->_a != other._a)
				{
					clear();
					this->_a.deallocate(this->_begin, capacity());
					this->_begin = this->_end = this->_capacity = NULL;
					this->_a = other._a;
				}
				assign(other._begin, other._end);
			}
			return (*this);
		}

		// Private Functions from Vector Class

		template<typename T, typename Allocator>
		void 	vector<T, Allocator>::reconstruct_push_back(const value_type& val)
		{
			size_type	_cap = this->capacity();
			size_type 	_max_size = max_size();
			size_type	new_size = _cap > (_max_size >> 1) ? _max_size : _cap << 1;
			if (new_size == 0) new_size = 1;
			reserve(new_size);
			this->_a.construct(this->_end, val);
			++this->_end;
		}
		
		template<typename T, typename Allocator>
		void 	vector<T, Allocator>::reallocate(size_type n)
		{
			vector<T, Allocator> tmp(n);
			std::uninitialized_copy(this->_begin, this->_end, tmp._begin);
			tmp._end = tmp._begin + size();
			this->swap_data(tmp);
		}

		template<typename T, typename Allocator>
		void vector<T, Allocator>::destroy_from_behind(pointer new_end)
		{
			pointer _b = this->_end;
			while (new_end != _b)
			{
				--_b;
				this->_a.destroy(_b);
			}
			this->_end = new_end;
		}

		// Capacity 

		template<typename T, typename Allocator>
		void vector<T, Allocator>::reserve(size_type n)
		{
			size_type new_size = this->check_length(n);
			if (new_size > capacity()) 
                reallocate(new_size);
		}

		template<typename T, typename Allocator>
		void vector<T, Allocator>::resize(size_type n, value_type val)
		{
			size_type prev_size = size();
			if (n < prev_size)
			{
				destroy_from_behind(this->_begin + n);
				return ;
			}
			else if (n > capacity())
				reallocate(n);
			insert(end(), n - prev_size, val);
		}

		// Modifiers 

		template<typename T, typename Allocator>
		void vector<T, Allocator>::assign(size_type n, const value_type& val)
		{
			if (n < capacity())
			{
				clear();
				std::uninitialized_fill(this->_begin, this->_begin + n, val);
				this->_end += n;
			}
			else 
			{
				vector<T, Allocator> tmp(n, val);
				this->swap_data(tmp);
			}
		}

        template <typename T, typename Allocator>
        template <typename InputIterator>
        void vector<T, Allocator>::assign(InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last)
        {
            clear();
            for(; first != last; ++first)
                push_back(*first);
        }

        template <typename T, typename Allocator>
        template <typename ForwardIterator>
        void vector<T, Allocator>::assign(ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last)
        {
            size_type new_n = ft::distance(first, last);
            if (new_n < capacity())
            {
                clear();
                this->_end = std::uninitialized_copy(first, last, this->_begin);
            }
            else 
            {
                vector<T, Allocator> tmp(first, last);
                this->swap_data(tmp);
            }
        }


		template<typename T, typename Allocator>
		void vector<T, Allocator>::push_back(const value_type& val)
		{
			if (this->_end != this->_capacity)
				this->_a.construct(this->_end++, val);
			else 
				reconstruct_push_back(val);
		}

		template<typename T, typename Allocator>
		void vector<T, Allocator>::pop_back() FT_NOEXCEPT
		{
			if(!empty())
				destroy_from_behind(this->_end - 1);
		}

		template<typename T, typename Allocator>
		typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator position, const value_type& val)
		{
			difference_type _diff = position - begin();
			
			if (this->_end == this->_capacity)
				reserve(size_type(capacity() + 1));
			
			pointer			_p = this->_begin + _diff;
			pointer 		_old_end = this->_end;
			
			while (_old_end != _p)
			{
				--_old_end;
				this->_a.construct(_old_end + 1, *(_old_end));
				this->_a.destroy(_old_end);
			}
			this->_a.construct(_p, val);
			++this->_end;
			return (iterator(this->_begin + _diff));
		}

		template<typename T, typename Allocator>
		void	vector<T, Allocator>::insert(iterator position, size_type n, const value_type& val)
		{
			difference_type _diff = position - begin();

			if (size() + n > capacity())
				reserve(size() + n);

			pointer _p = this->_begin + _diff;
			pointer _old_end = this->_end;
			
			while (_old_end != _p)
			{
				--_old_end;
				this->_a.construct(_old_end + n, *(_old_end));
				this->_a.destroy(_old_end);
			}
			std::uninitialized_fill(_p, _p + n, val);
			this->_end += n;
		}

        template <typename T, typename Allocator>
        template <typename InputIterator>
        void vector<T, Allocator>::insert(iterator position, InputIterator first, typename enable_if<_is_input_iterator<InputIterator>::value && !_is_forward_iterator<InputIterator>::value, InputIterator>::type last)
        {
            difference_type _diff = position - begin();
            pointer _p = this->_being + _diff;
            pointer _old_end = this->_end;

            for (int i = 0; first != last; ++first, ++i)
                insert(position + i, *first);
        }

        template <typename T, typename Allocator>
        template <typename ForwardIterator>
        void vector<T, Allocator>::insert(iterator position, ForwardIterator first, typename enable_if<_is_forward_iterator<ForwardIterator>::value, ForwardIterator>::type last)
        {
            difference_type _in_size = ft::distance(first, last);
            difference_type _diff = position - begin();

            if (_in_size <= 0)
                return ;
            if (_in_size + size() > capacity())
                reserve(_in_size + size());
            
            pointer _p = this->_begin + _diff;
            pointer _old_end = this->_end;
            while (_old_end != _p)
            {
                --_old_end;
                this->_a.construct(_old_end + _in_size, *(_old_end));
                this->_a.destroy(_old_end);
            }
            std::uninitialized_copy(first, last, _p);
            this->_end += _in_size;
        }

		template<typename T, typename Allocator>
		typename vector<T, Allocator>::iterator vector<T,Allocator>::erase(iterator position)
		{
			difference_type _diff = position - begin();
			pointer _p = this->_begin + _diff;

			this->_a.destroy(_p);
			this->_a.destroy(std::uninitialized_copy(_p + 1, this->_end--, _p));
			return (iterator(this->_begin + _diff));
		}

		template<typename T, typename Allocator>
		typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
		{
			difference_type _diff = first - begin();
			pointer _p = this->_begin + _diff;

			if (last == end())
			{
				destroy_from_behind(_p);
				return iterator(this->_begin + _diff);
			}

			difference_type	_range = last - first;
			pointer 		_p_last = _p + _range;
			pointer 		_new_end = this->_end - _range;

			for (difference_type i  = 0; i <= _range; ++i)
			{
				this->_a.destroy(_p + i);
				if (i <= this->_end - _p_last)
					this->_a.construct(_p + i, *(_p_last + i));
			}

			destroy_from_behind(_new_end);
			return (iterator(this->_begin + _diff));
		}

		// Non Member Function Overload 
		// Comparison Operators 

		template<typename T, typename Allocator>
		inline bool operator==(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));}
		template<typename T, typename Allocator>
		inline bool operator!=(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return !(lhs == rhs);}
		template<typename T, typename Allocator>
		inline bool operator<(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
		template<typename T, typename Allocator>
		inline bool operator<=(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return !(lhs > rhs);}
		template<typename T, typename Allocator>
		inline bool operator>(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return (rhs < lhs);}
		template<typename T, typename Allocator>
		inline bool operator>=(const vector<T, Allocator>&lhs, const vector<T, Allocator>& rhs){return !(rhs > lhs);}

		template<typename T, typename Allocator>
		inline void swap(ft::vector<T, Allocator>& x, ft::vector<T, Allocator>& y){x.swap(y);}
}


#endif 