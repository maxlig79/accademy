#define BOOST_TEST_MODULE BOOSTTEST
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "common.h"
#include <fstream>
#include <iostream>
#include <iterator>

std::ifstream client1{"client1.log"};
std::ifstream client2{"client2.log"};

BOOST_AUTO_TEST_SUITE(BoostTest)
BOOST_AUTO_TEST_CASE(test)
{
    system("./script.sh");
    std::string output;
    int k = 0;
    while (std::getline(client1, output))
    {
        switch (k)
        {
        case 0:
        {
            BOOST_CHECK(output == "Add OK");
            break;
        }
        case 1:
        {
            BOOST_CHECK(output == "Add OK");
            break;
        }
        case 2:
        {
            BOOST_CHECK(output == "Not found");
            break;
        }
        case 3:
        {
            BOOST_CHECK(output == "no1");
            break;
        }
        default:
            break;
                }
        k++;
    }
    BOOST_CHECK(k == 3);
    k = 0;
    while (std::getline(client2, output))
    {
        switch (k)
        {
        case 0:
        {
            BOOST_CHECK(output == "Add OK");
            break;
        }
        case 1:
        {
            BOOST_CHECK(output == "Add OK");
            break;
        }
        case 2:
        {
            BOOST_CHECK(output == "no2");
            break;
        }
        default:break;
        }
        k++;
    }
    BOOST_CHECK(k==3);
}
BOOST_AUTO_TEST_SUITE_END()