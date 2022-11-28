#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
    template <typename InputIterator1, typename InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false ;
            ++first1, ++first2;
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1, ++first2;
        }
        return true;
    }

    template <typename InputIterator1, typename InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1, ++first2;
        }
        return (first2 != last2);
    }

    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1 < *first2))
                return true;
            ++first1, ++first2;
        }
        return (first2 != last2);
    }

    template <typename T>
    const T& min(const T& x, const T& y) {return ((x < y) ? x : y);}

    template <typename It, typename Allocator>
    pointer (pointer dst, It start, It end, Allocator &alloc)
    {
        for (; start != end; ++dst, (void)++start) {
            alloc_.construct(dst, *start);
        }
        return dst;
    }

    pointer construct_range(pointer dst, const_pointer end, const_reference value)
    {
        for (; dst != end; ++dst) {
            alloc_.construct(dst, value);
        }
        return dst;
    }

    template <typename T, typename Iter, class Alloc>
    void uninitialized_fill(Iter begin, Iter end, const T& val, Alloc& a)
    {
        size_t i = 0;
        
        for (; begin + i != end; ++i) 
            a.construct(begin + i, val);
        
    }

    template<class It, class FwdIt, class Alloc>
    FwdIt   uninitialized_copy(It first, It last, FwdIt dest, Alloc& a)
    {
        FwdIt s = dest;
        a.allocate(last - first);
        for (; first != last; ++first, (void) ++dest)
        {
            a.construct(dest, *first);
        }
        return dest;
    }

}


#endif