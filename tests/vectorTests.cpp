#include <iostream>
#include "catch.hpp"
#include "../ft_vector.hpp"
#include <string>
#include <vector>

TEST_CASE("FT_VECTOR_CONSTRUCTOR TEST", "[VECTOR]")
{   
    SECTION("Default copy constructor or your implementation is making a shallow copy")
    {
        ft::vector<int> x;
        ft::vector<int> y;
       // y = x;
        ft::vector<int> z;
     
    /*
    
        std::vector<int> xv;
        xv.push_back(100);
        std::vector<int> yv;
        yv = xv;
        std::vector<int> zv;
        zv.push_back(200);
    */
       
       // REQUIRE(xv[0] == 100);
        //REQUIRE(yv[0] == 100);
       // REQUIRE(zv[0] == 200);

       // REQUIRE(x[0] == 100);
       // REQUIRE(y[0] == 100);
       // REQUIRE(z[0] == 200);
       
    }
}

