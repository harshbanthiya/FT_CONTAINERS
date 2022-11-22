#pragma once 

#include "../type-traits/priority_tag.hpp"
#include "../utility/decval.hpp"

#include <cstddef>

namespace ft
{
    template <class Ptr>
    auto pointer_element_type(Ptr&, priority_tag<1>) ->typename Ptr::element_type;

    template <template <class...> class SomePointer, class T, class... Vs>
    auto pointer_element_type(SomePointer<T, Vs...>&, priority_tag<0>) -> T;

    template <class P> auto pointer_difference_type(priority_tag<1>) -> typename P::difference_type;
    template <class P> auto pointer_difference_type(priority_tag<0>) -> ptrdiff_t;
    template <class P> auto pointer_difference_type_t = decltype(pointer_difference_type<P>(priority_tag<1> {}));

    template <class U, class Ptr>
    auto pointer_rebind(Ptr&, priority_tag<1>) -> typename Ptr::template rebind<U>;

    template <class U, template<class...> class SomePointer, class T, class... Vs>
    auto pointer_rebind(SomePointer<T, Vs...>&, priority_tag<0>) -> SomePointer<U, Vs...>;

    template <class Ptr>
    struct pointer_traits
    {
        using pointer = Ptr;
        using element_type = decltype(pointer_element_type(declval<Ptr&>(), priority_tag<1> {}));
        using difference_type = pointer_difference_type_t<Ptr>;

        template <class U> using rebind = decltype(pointer_rebind<U>(declval<Ptr&>(), priority_tag<1>{}));
    };

    template <class T>
    struct pointer_traits<T*>
    {
        using pointer = T*;
        using element_type = T;
        using difference_type = ptrdiff_t;

        template<class U> using rebind = U*;
    };

}


/*

    What is a "pointer" ?

    The standard is full of types that a reasonable person might call pointer - like.
    Obv there is T* and shared_ptr<T> and unique_ptr<T>
    Iterators are dereferencable and arithmetical 
    T& looks like a pointer but isnt 

    What counts as pointer for the purpose of pointer_traits ?

    Not shared ptr ; or iterators ; Because no allocator would ever give out shared ptr is response 
    to allocation request 

    What is rebind ?

    pointer_traits<P>::rebind<U> and the allocator_traits<A>::rebind_alloc<U>
    both of them have the same purpose and same essential motivation untangling the mess 
    that started when the Standard decided that the syntax for allocators should be 

    std::list<int, std::allocator<int>> lst;

    See std::list gets an allocator that know how to allocate ints but std::list doesnt want to 
    allocate ints, it wants to allocate some node of awkward size, std::list_node<int, typename std::allocator<int>::pointer>

    - So the library needs some way to take allocator<int> and turn it into an <allocator<Node ..>
        thats what rebind does 
    
    making std::allocator_traits<std::allocator<int>>::rebind_alloc<Node> evaluate to std::allocator<Node>

        So what does my fancy pointer type actually need to implement?
    --------------------------------------------------------------

    The Standard `pointer_traits` is extremely convoluted in its requirements
    and defaults.

    Q: Why does my fancy pointer type need to provide a nested typedef `difference_type`?
    Shouldn't `decltype(p - p)` be good enough?

    A: `decltype(p - p)` fails to work for fancy pointers to `void`, since void pointers
    generally can't be subtracted. But if you don't provide `difference_type`, the trait
    will default to `ptrdiff_t`, which is invariably correct.

    Q: Why does my fancy pointer type need to provide a nested typedef `element_type`?
    Shouldn't `decltype(*p)` be good enough?

    A: Again, `decltype(*p)` fails to work for fancy pointers to `void`.

    Q: Do I *actually* need to provide `element_type`, though?

    A: Well, not usually. The Standard `pointer_traits` actually has a special case for
    any fancy-pointer type that looks like `Foo<Bar, Baz...>`: it will assume that if
    you're messing with `pointer_traits` for such a type, then a good default behavior
    would be to assume that `element_type` is `Bar` and that `rebind<U>` is
    `Foo<U, Baz...>`. This is completely crazy from a philosophical point of view
    (the core language doesn't assign any magical meaning to the first template parameter!),
    but it does work very conveniently in practice. It means that generally you don't
    have to define `element_type` or `rebind` — and of course you basically never have
    to define `difference_type`, because `ptrdiff_t` is always an okay choice.

    Q: Why does my fancy pointer type need to provide nested typedefs `value_type`,
    `reference`, `pointer`, `difference_type`, and `iterator_category`?

    A: Because every fancy pointer type (if it's going to be typedeffed as `A::pointer`
    for any allocator `A`) must also be a random-access iterator type, as required by
    [allocator.requirements]/5. And that means that we need `iterator_traits<P>` to be
    populated; but `iterator_traits<P>` is populated only for types that provide all
    five of those nested typedefs. So you have to provide them all.

    Ironically, this means that a type that wants to be a "fancy pointer" needs to
    spend more time worrying about *iterator* traits than about *pointer* traits!

    Clang's libc++ containers actually go out of their way to do iteration
    (e.g. `std::copy`) only on raw `T*`, never on fancy pointers. But GNU's libstdc++
    does iteration on fancy pointers all the time; e.g. in `vector::resize`. So if
    you want your fancy pointers to work on libstdc++, you'd better make sure they're
    safe for use as iterators.


*/