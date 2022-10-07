#include "ft_vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> x(100);
   // ft::vector<int> y(x);
    ft::vector<int> z(200);
    x.push_back(200);
    z.push_back(100);

    x.pop_back();
    z.pop_back();

   // std::cout << x.buffer[0];
    //std::cout << z.buffer[0];
    //z = x;
    
}