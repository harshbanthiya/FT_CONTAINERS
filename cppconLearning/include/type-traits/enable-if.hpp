#pragma once

namespace ft
{
    template<bool Condition, typename T = void> struct enable_if{};
    template<typename T> struct enable_if<true, T> {using type =  T;};

    template<bool Condition, typename T = void> using enable_if_t = typename enable_if<Condition, T>::type;

    // Bool if_t is not in stl but it will be helpful later to do SFINAE to overload constructors 
    template<bool Condition> using bool_if_t = enable_if_t<Condition, bool>;
    
    /*
        Easiest way to add a defaulted template non-type parameter of type `bool_if_t`:

        template<bool_if_t<make_explicit> = true>
        explicit Foo(const Foo&) { ... }

        template<bool_if_t<!make_explicit> = true>
        Foo(const Foo&) { ... }
    */
}