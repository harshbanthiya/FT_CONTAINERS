#include <iostream>
#include "catch.hpp"
#include "../Ft_vector/ft_vector.hpp"
#include <string>
#include <vector>

TEST_CASE("FT_VECTOR_CONSTRUCTOR TEST", "[VECTOR]")
{   
    SECTION("Default copy constructor or your implementation is making a shallow copy")
    {
        ft::Vector<int> x;
        x.push_back(100);
        ft::Vector<int> y;
        y = x;
        ft::Vector<int> z;
        z.push_back(200);

        std::vector<int> xv;
        xv.push_back(100);
        std::vector<int> yv;
        yv = xv;
        std::vector<int> zv;
        zv.push_back(200);
       
        REQUIRE(xv[0] == 100);
        REQUIRE(yv[0] == 100);
        REQUIRE(zv[0] == 200);

        REQUIRE(x[0] == 100);
        REQUIRE(y[0] == 100);
        REQUIRE(z[0] == 200);
       
    }
}

