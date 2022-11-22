#pragma once 

#include <cstddef>

namespace ft
{
    // Non Standard functions 
    template <size_t I> struct priority_tag : priority_tag<I - 1> {};
    template <> struct priority_tag<0> {};
}