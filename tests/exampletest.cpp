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
    SECTION("TEST MULTIPLE NODES ON THE LINK LIST")
    {
        LNode *begin = new LNode(1, nullptr);
        begin->setNext(new LNode(2, nullptr));
        begin->getNext()->setNext(new LNode(3, nullptr));

        REQUIRE(begin->getData() == 1);
        REQUIRE(begin->getNext() != nullptr);

        REQUIRE(begin->getNext()->getData() == 2);
        REQUIRE(begin->getNext()->getNext() != nullptr);

        REQUIRE(begin->getNext()->getNext()->getData() == 3);
        REQUIRE(begin->getNext()->getNext()->getNext() == nullptr);
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

