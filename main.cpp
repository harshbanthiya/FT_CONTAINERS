/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:19:59 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/10/06 11:53:03 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CATCH_CONFIG_RUNNER 
#include <iostream>
#include "tests/catch.hpp"
#include <fstream>
#include <string>
#include <exception>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "No arguments.. running tests!\n";
        try {
            int result = Catch::Session().run(argc, argv);
            std::cin.get();
            return (result < 0xFF ? result : 0xFF);
        }catch (const std::exception& ex)
        {
            const char *pMessage = ex.what();
            if (pMessage)
            {
                std::cout << "An unhandled exception was thrown: \n" << pMessage;
            }
            std::cin.get();
            return (-1);
        }
    }
    else {
        std::cout << "Main program logic goes here.. \n";
        std::cout << "program called with args" << std::endl;
    }
}