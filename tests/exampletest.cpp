#include <iostream>
#include "catch.hpp"
#include "../LList.hpp"
#include <string>

TEST_CASE("L Node", "[NODE]")
{   
    SECTION("Initialize")
    {
        LNode *node = new LNode(1, nullptr);
        REQUIRE(node->getData() == 1);
        REQUIRE(node->getNext() == nullptr);
    }
}
/*
TEST_CASE("My LinkedList", "[LINKED LIST]")
{
    SECTION("EMPTY LIST")
    {
        std::string a = "foo";
        std::string b = "bar";
        REQUIRE(a == b);
    }
}
*/
