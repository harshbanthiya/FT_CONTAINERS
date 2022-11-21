#pragma once

#include "../type-traits/add-foo.hpp"

namespace ft
{
    template <class T> auto declval() noexcept -> add_rvalue_reference_t<T>;
}