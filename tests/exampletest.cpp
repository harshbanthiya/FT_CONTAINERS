#include <iostream>
#include "catch.hpp"
#include "../Ft_vector/ft_vector.hpp"
#include <string>

TEST_CASE("FT_VECTOR", "[VECTOR]")
{   
    SECTION("Default copy constructor or your implementation is making a shallow copy")
    {
        ft::Vector<int> x (100);
        ft::Vector<int> y(x);
        ft::Vector<int> z(200);
    
       z = x;
       // REQUIRE(node->getNext() == nullptr);
    }
    SECTION("TESTING DEEP COPY AND SIMPLE PUSHBACK POP_BACK")
    {
        ft::Vector<int> xx(100);
        ft::Vector<int> xy(100);

        xx.push_back(400);
        xy.push_back(400);
        xx.pop_back();
        xy.pop_back();

        
    }
}

TEST_CASE("My LinkedList", "[LINKED LIST]")
{
    SECTION("EMPTY LIST")
    {
        std::string a = "foo";
        std::string b = "foo";
        REQUIRE(a == b);
    }
}

