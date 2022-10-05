#include <compare>
#include <iostream>
#include <initializer_list>
 
namespace std {
  // class template ft_vector
  template<class T, class Allocator = allocator<T>> class ft_vector;
 
  template<class T, class Allocator>
    constexpr bool operator==(const ft_vector <T, Allocator>& x,
                              const ft_vector<T, Allocator>& y);
  //template<class T, class Allocator>
    //constexpr /*synth-three-way-result*/<T> operator<=>(const ft_vector<T, Allocator>& x,
                                                       // const ft_vector<T, Allocator>& y);
 
  template<class T, class Allocator>
    constexpr void swap(ft_vector<T, Allocator>& x, ft_vector<T, Allocator>& y)
      noexcept(noexcept(x.swap(y)));
 
  template<class T, class Allocator, class U>
    constexpr typename ft_vector<T, Allocator>::size_type
      erase(ft_vector<T, Allocator>& c, const U& value);
  template<class T, class Allocator, class Predicate>
    constexpr typename ft_vector<T, Allocator>::size_type
      erase_if(ft_vector<T, Allocator>& c, Predicate pred);
 
  // class ft_vector<bool>
  template<class Allocator> class ft_vector<bool, Allocator>;
 
 /*
  // hash support
  template<class T> struct hash;
  template<class Allocator> struct hash<ft_vector<bool, Allocator>>;
 */

  namespace pmr {
    template<class T>
      using ft_vector = std::ft_vector<T, polymorphic_allocator<T>>;
  }
}


namespace std {
  template<class T, class Allocator = allocator<T>>
  class ft_vector {
  public:
    // types
    using value_type             = T;
    using allocator_type         = Allocator;
    using pointer                = typename allocator_traits<Allocator>::pointer;
    using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using size_type              = /* implementation-defined */;
    using difference_type        = /* implementation-defined */;
    using iterator               = /* implementation-defined */;
    using const_iterator         = /* implementation-defined */;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
 
    // construct/copy/destroy
    constexpr ft_vector() noexcept(noexcept(Allocator())) : ft_vector(Allocator()) { }
    constexpr explicit ft_vector(const Allocator&) noexcept;
    constexpr explicit ft_vector(size_type n, const Allocator& = Allocator());
    constexpr ft_vector(size_type n, const T& value, const Allocator& = Allocator());
    template<class InputIt>
      constexpr ft_vector(InputIt first, InputIt last, const Allocator& = Allocator());
    constexpr ft_vector(const ft_vector& x);
    constexpr ft_vector(ft_vector&&) noexcept;
    constexpr ft_vector(const ft_vector&, const Allocator&);
    constexpr ft_vector(ft_vector&&, const Allocator&);
    constexpr ft_vector(initializer_list<T>, const Allocator& = Allocator());
    constexpr ~ft_vector();
    constexpr ft_vector& operator=(const ft_vector& x);
    constexpr ft_vector& operator=(ft_vector&& x)
      noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
               allocator_traits<Allocator>::is_always_equal::value);
    constexpr ft_vector& operator=(initializer_list<T>);
    template<class InputIt>
      constexpr void assign(InputIt first, InputIt last);
    constexpr void assign(size_type n, const T& u);
    constexpr void assign(initializer_list<T>);
    constexpr allocator_type get_allocator() const noexcept;
 
    // iterators
    constexpr iterator               begin() noexcept;
    constexpr const_iterator         begin() const noexcept;
    constexpr iterator               end() noexcept;
    constexpr const_iterator         end() const noexcept;
    constexpr reverse_iterator       rbegin() noexcept;
    constexpr const_reverse_iterator rbegin() const noexcept;
    constexpr reverse_iterator       rend() noexcept;
    constexpr const_reverse_iterator rend() const noexcept;
 
    constexpr const_iterator         cbegin() const noexcept;
    constexpr const_iterator         cend() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;
 
    // capacity
    [[nodiscard]] constexpr bool empty() const noexcept;
    constexpr size_type size() const noexcept;
    constexpr size_type max_size() const noexcept;
    constexpr size_type capacity() const noexcept;
    constexpr void      resize(size_type sz);
    constexpr void      resize(size_type sz, const T& c);
    constexpr void      reserve(size_type n);
    constexpr void      shrink_to_fit();
 
    // element access
    constexpr reference       operator[](size_type n);
    constexpr const_reference operator[](size_type n) const;
    constexpr const_reference at(size_type n) const;
    constexpr reference       at(size_type n);
    constexpr reference       front();
    constexpr const_reference front() const;
    constexpr reference       back();
    constexpr const_reference back() const;
 
    // data access
    constexpr T*       data() noexcept;
    constexpr const T* data() const noexcept;
 
    // modifiers
    template<class... Args> constexpr reference emplace_back(Args&&... args);
    constexpr void push_back(const T& x);
    constexpr void push_back(T&& x);
    constexpr void pop_back();
 
    template<class... Args>
      constexpr iterator emplace(const_iterator position, Args&&... args);
    constexpr iterator insert(const_iterator position, const T& x);
    constexpr iterator insert(const_iterator position, T&& x);
    constexpr iterator insert(const_iterator position, size_type n, const T& x);
    template<class InputIt>
      constexpr iterator insert(const_iterator position,
                                InputIt first, InputIt last);
    constexpr iterator insert(const_iterator position, initializer_list<T> il);
    constexpr iterator erase(const_iterator position);
    constexpr iterator erase(const_iterator first, const_iterator last);
    constexpr void     swap(ft_vector&)
      noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value ||
               allocator_traits<Allocator>::is_always_equal::value);
    constexpr void     clear() noexcept;
  };
 
  template<class InputIt, class Allocator = allocator</*iter-value-type*/<InputIt>>>
    ft_vector(InputIt, InputIt, Allocator = Allocator())
      -> ft_vector</*iter-value-type*/<InputIt>, Allocator>;
 
  // swap
  template<class T, class Allocator>
    constexpr void swap(ft_vector<T, Allocator>& x, ft_vector<T, Allocator>& y)
      noexcept(noexcept(x.swap(y)));
}