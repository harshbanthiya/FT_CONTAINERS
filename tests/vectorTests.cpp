#include <iostream>
#include "catch.hpp"
#include "../ft_vector.hpp"
#include <string>
#include <vector>

TEST_CASE("FT_VECTOR_CONSTRUCTOR TEST", "[VECTOR]")
{   
    SECTION("Default copy constructor or your implementation is making a shallow copy")
    {
        ft::vector<int> v1;
        ft::vector<int> v2(10);
        //ft::vector<int> v3(10, 1);
        //ft::vector<int> v4(a, a + 5);
        //ft::vector<int> v5(v2);
        //ft::vector<int> v6(std::move(v2));
        //ft::vector<int> v7{ 1,2,3,4,5,6,7,8,9 };
        ft::vector<int> v8, v9, v10;
        
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

