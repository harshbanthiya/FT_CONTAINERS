#include <iostream>
#include "catch.hpp"
#include "../ft_vector.hpp"
#include <string>
#include <algorithm>
#include <vector>

template<typename Container>
Container make(const char s[])
{
    return Container(&s[0], &s[strlen(s)]);
}

TEST_CASE("FT_VECTOR_CONSTRUCTOR TEST", "[VECTOR]")
{   
    SECTION("Simple constructor tests for vector(n) and vector(n, val)")
    {
        ft::vector<char> vector1;
        ft::vector<char> vector2(3, 'x');

        REQUIRE(vector1.size() == 0);
        REQUIRE(vector2.size() == 3);
        REQUIRE(vector2[0] == 'x' && vector2[1] == 'x' && vector2[2] == 'x');
        REQUIRE(vector2 == ft::vector<char>(3, 'x') && vector2 != vector<char>(4, 'x'));
        
    }
    /*
    SECTION("Default copy constructor or your implementation is making a shallow copy")
    {
        /*
        int n = 3;
        ft::vector<int> v1;
        ft::vector<int> v2(10);
        ft::vector<int> v3 = ft::vector<int>(6, 0);
        //ft::vector<int> v4(a, a + 5);
        //ft::vector<int> v5(v2);
        //ft::vector<int> v6(std::move(v2));
        //ft::vector<int> v7{ 1,2,3,4,5,6,7,8,9 };
        ft::vector<int> v8, v9, v10;
        //
        
        char name[] = "George Foreman Grill";
        ft::vector<char> George(name, name + 6);

        ft::vector<char> anotherGeorge(George.begin(), George.end());
        REQUIRE(anotherGeorge == George);

        ft::vector<char> son1(George); 
        REQUIRE(son1 == anotherGeorge);

        ft::vector<char> son2 = George;
        REQUIRE(son2 == anotherGeorge);

        
        
        // Write Tests with another containers pointers to test compatibility 
        
        
        /*
    
        std::vector<int> xv;
        xv.push_back(100);
        std::vector<int> yv;
        yv = xv;
        std::vector<int> zv;
        zv.push_back(200);
        
       
       // REQUIRE(xv[0] == 100);
        //REQUIRE(yv[0] == 100);
       // REQUIRE(zv[0] == 200);

       // REQUIRE(x[0] == 100);
       // REQUIRE(y[0] == 100);
       // REQUIRE(z[0] == 200);
       
    }   

    SECTION("TESTING INSERTIONS")
    {
        ft::vector<char> vector1 = make<ft::vector<char> >("Bjarne Strousstrup");
        ft::vector<char> vector2; 

        ft::vector<char>::iterator i;
        
        // push_back
        for (i = vector1.begin(); i != vector1.end(); ++i)
            vector2.push_back(*i);
        REQUIRE(vector1 == vector2);

        // insert 
        ft::vector<char> vector1 = make<ft::vector<char> >("Bjarne Strousstrup");
        ft::vector<char> vector2 = make<ft::vector<char> >(""); 

        ft::vector<char>::iterator i;
        
        // push_back
        for (i = vector1.begin(); i != vector1.end(); ++i)
            vector2.insert(vector2.begin(), *i);
        REQUIRE(vector2 == make< ft::vector<char> >("purtssuortS enrajB"));

    }


    SECTION("TESTING RESERVE AND CAPACITY FUNCTIONS")
    {
        int N = 10000;

        ft::vector<int> vector1, vector2;
        int k;
        for (k = 0; k != N; ++k)
        {
            ft::vector<int>::size_type cap = vector1.capacity();
            vector1.push_back(int(k));
        }

        vector2.reserve(N);
        for (k = 0; k != N; ++k)
        {
            ft::vector<int>::size_type cap = vector2.capacity();
            vector2.push_back(int(k));
        }
    }

    SECTION("TESTING BACK AND POP BACK :DELETION ")
    {
        ft::vector<char> vector1 = make<ft::vector<char> >("abcdefghijkl");

        while (vector1.size() > 0)
            vector1.pop_back();
        
    }

    SECTION("TESTING ERASE :DELETION ")
    {
        ft::vector<char> vector1 = make<ft::vector<char> >("remembering");
        ft::vector<char>::iterator j;

        j = find(vector1.begin(), vector1.end(), 'm');

        REQUIRE(*j == 'm' && *(j + 1) == 'e');
        vector1.erase(j--);
        REQUIRE(vector1 == make<ft::vector<char> >("reembering"));

        // j is now on 'e'
        REQUIRE(*j == 'e' && *(j + 1) == 'e');
        vector1.erase(j--);
        REQUIRE(vector1 == make<ft::vector<char> >("rembering"));
        REQUIRE(*j == 'r');

        // Erase first 3 
        vector1.erase(j, j + 3);
        REQUIRE(vector1 == make<ft::vector<char> >("bering"));
        vector1.erase(vector1.begin() + 1);
        REQUIRE(vector1 == make<ft::vector<char> >("bring"));

    }
    */
}

