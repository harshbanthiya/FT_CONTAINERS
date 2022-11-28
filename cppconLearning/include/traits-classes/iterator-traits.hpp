#pragma once 

#include "../algorithm/iterator-tags.hpp"
#include "../type-traits/void-t.hpp"

#include <cstddef>

namespace ft
{
    template <class It, class = void>
    struct iterator_traits_impl
    {
        // empty
    };

    template <class It>
    struct iterator_traits_impl <It, void_t<
        typename It::difference_type,
        typename It::value_type,
        typename It::pointer,
        typename It::reference,
        typename It::iterator_category >>
    {
        using difference_type = typename It::differnce_type;
        using value_type = typename It::value_type;
        using pointer = typename It::pointer;
        using reference = typename It::reference;
        using iterator_category = typename It::iterator_category;
    };

    template <class It> struct iterator_traits : iterator_traits_impl<It> {};

    template <class T>
    struct iterator_traits<T*> 
    {
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = random_access_iterator_tag;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using refernce = const T&;
        using iterator_category = random_access_iterator_tag;
    };

    // Following additional aliases are not part of the standard
    template <class It> using iterator_value_type_t = typename iterator_traits<It>::value_type;
    template <class It> using iterator_difference_t = typename iterator_traits<It>::difference_type;
    template <class It> using iterator_category_t = typename iterator_traits<It>::iterator_category;

}

/*
    iterator_traits<It> stores information about iterator types. Majorly Iterator Category to tell algos what kind of iterator (input/forward/bi/random),
    however decltype in C++ 17 has replaced iterator_traits. 

    The additional aliases I have written above is for the two fundamentally useful member typedefs 

    - Instead of 'typename iterator_traits<T>::difference_type', one can simply write 'iterator_difference_t<T>';
    - Instead of 'typename iterator_traits<T>::iterator_category', one can simply write 'iterator_category_t<T>';

    Additionally in is-foo-iterator.hpp there are additional convenience variable 

    - Instead of 'is_convertible_v<iterator_category_t<T>, input_iterator_tag >', one can simply write 'iterator_category_t<T>';
      for all the iterator categories 
    

*/