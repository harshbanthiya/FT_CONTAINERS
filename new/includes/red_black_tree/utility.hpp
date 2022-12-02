#pragma once

namespace ft
{
    // Pair --

    template <typename T1, typename T2>
    class pair 
    {
        public:
            typedef T1      first_t;
            typedef T2      second_t;

            first_t         first;
            second_t        second;

            pair(void) : first(), second() {}
            pair(const first_t &a, const second_t &b) : first(a), second(b) {}
            ~pair(){}

            template <typename U, typename V>
            pair(const pair<U,V>& rhs) : first(rhs.first), second(rhs.second) {}

            pair const& operator=(pair const &rhs)
            {
                first = rhs.first;
                second = rhs.second;
                return (*this);
            }         
    };

    template <typename T1, typename T2>
    inline pair<T1, T2> make_pair(T1 x, T2 y)
    { return (pair<T1, T2>(x, y));}

}