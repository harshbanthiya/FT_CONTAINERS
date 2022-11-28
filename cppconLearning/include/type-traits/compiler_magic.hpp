#pragma once 

#include "type-traits/integral_constant.hpp"

// The following type traits can only be achieved by compiler magic

namespace ft
{
    template <class T> struct has_virtual_destructor : bool_constant<__has_virtual_destructor(T)>{};
    template <class T> struct is_abstract : bool_constant<__is_abstract(T)>{};
    template <class T> struct is_aggregate : bool_constant<__is_aggregate(T)>{};
    template <class T> struct is_empty : bool_constant<__is_empty(T)>{};
    template <class T> struct is_enum : bool_constant<__is_enum(T)>{};
    template <class T> struct is_final : bool_constant<__is_final(T)>{};
    template <class T> struct is_literal_type : bool_constant<__is_literal_type(T)>{};
    template <class T> struct is_standard_layout : bool_constant<__is_standard_layout(T)>{};
    template <class T> struct is_trivially_copyable : bool_constant<__is_trivially_copyable(T)>{};
    template <class T> struct is_union  : bool_constant<__is_union(T)> {};

    template <class T> inline constexpr bool has_virtual_destructor_v = __has_virtual_destructor(T);
    template <class T> inline constexpr bool is_abstract_v = __is_abstract(T);
    template <class T> inline constexpr bool is_aggregate_v = __is_aggregate(T);
    template <class T> inline constexpr bool is_empty_v = __is_empty(T);
    template <class T> inline constexpr bool is_enum_v = __is_enum(T);
    template <class T> inline constexpr bool is_final_v = __is_final(T);
    template <class T> inline constexpr bool is_literal_type_v = __is_literal_type(T);
    template <class T> inline constexpr bool is_standard_layout_v = __is_standard_layout(T);
    template <class T> inline constexpr bool is_trivially_copyable_v = __is_trivially_copyable(T);
    template <class T> inline constexpr bool is_union_v = __is_union(T);

    template <class T, class ... Us> struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, Us...)> {};
    template <class T, class U>      struct is_trivially_assignable : bool_constant<__is_trivially_assignable(T, U)> {};

    template <class T, class ... Us> inline constexpr bool is_trivially_constructible_v = __is_trivially_constructible(T, Us...);
    template <class T, class U>      inline constexpr bool is_trivially_assignable_v = __is_trivially_assignable(T, U);

    template <class T> struct underlying_type {using type = __underlying_type(T);};
    template <class T> using underlying_type_t = typename underlying_type<T>::type;
}

/*

is_union    :   queries an attribute of the class for union, because anything you can do with class / struct like inheriting and taking member pointers; 
                you can also do that with union in C++;

is_aggregate, is_literal_type, is_standard_layout, has_virtual_destructor
            :   queries attributes of the class to find out - if the data members are all POD (Plain Old Data) types;
                or if any of them are 'private';
                or if the class has constexpr constructors (this is the key requirement for 'is_literal_type');
                has_virtual_destructor is specifically concerned with destructor not exposed by any other means ;
                is_pod == (is_standard_layout && is_trivial);

is_abstract
            :   since abstract class type do not let to get a value of that type. It is bad to define a function
                whose parameters or return type is abstract, or say to create an array whose element type is abstract; 
                ( Oddly if T is abstract, then SFINAE will apply to T[] but not to T().)
                which means, [ It is acceptable to create the *type* of a function with an abstract return type; however
                it is ill-formed to define an *entity* of such function type.]

                So is_abstract implementation is close to (using SFINAE)
                
                template<class T, class> struct is_abstract_impl : true_type{};
                template<class T> struct is_abstract_impl<T, void_t<T[]> > : false_type {};
                
                template<class T> struct is_abstract : is_abstract_impl<remove_cv_t <T>, void> {};

                
                is_abstract<vector<T>> will give the wrong answer because the T itself is templated class
                and forming T[] in this situation is valid. Therefore compilers provide __is_abstract(T)

is_literal_type
            :   this queries namely the const_expr- ness of any of the constructors of such class. Pretty useless and deprecated now in C++17
                Since the existence of some constexpr is no guarantee of the constexpr-ness of the constructor that you want to use. 

is_final    :   this queries the base-specifier-list of a derived class since it is not SFINAE, we cannot exploit 
                enable_if_t to ask "can I create a class derived from 'T' ? " because if we cannot create such a class. 
                it will be a HARD ERROR

is_empty    :   we cannot ask whether 'sizeof(T) == 0' because in C++ no type is ever allowed to have size 0; even an empty class
                has 'sizeof(T) == 1' ; The compiler does something called Empty Base Optimisation: whereby compilers will lay out two classes 

                struct Derived : public T {int x; };
                struct UnDerived {int x; };

                which means that , the compiler will not lay out any space in Derived for the empty T subobject
                C++03 just asked sizeof (Derived) == sizeof(UnDerived); But this trick stopped working in C++11 
                Becuase T might be final and the final-ness of a class is not exposed by any other means! So compilers 
                has to implement final and must also expose empty for benefit of STL 

is_enum     :   if T is not a fundamental type, i.e an array, a pointer, a reference, a member pointer, a class/union or 
                a function type; then by process of elimination it must be an enum type. However this deductive reasoning fails 
                if the compiler also happens to support additional types 

is_trivially_constructible, is_trivially_assignable 
            :   We dont need to any additional compiler magic to query the triviality of "default" construction, "copy" construction, "move" assignment and so on 

underlying_type 
            :   the underlying type of enum is not exposed by any other means, you can get close by taking sizeof(T) and comparing it to the sizes of all known types 
                and by asking the signed ness by "T(-1) < T(0)"; but that still cannot distinguish between int and long, on platforms where these types have same width


*/