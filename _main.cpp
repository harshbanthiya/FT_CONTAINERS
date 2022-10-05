#include "Ft_vector/ft_vector.hpp"
#include <iostream>

int main()
{
    ft::Vector<int> x(100);
   // ft::Vector<int> y(x);
    ft::Vector<int> z(200);
    x.push_back(200);
    z.push_back(100);

    x.pop_back();
    z.pop_back();

    std::cout << &x << " " << &z << std::endl;
   // std::cout << x.buffer[0];
    //std::cout << z.buffer[0];
    //z = x;
    
}