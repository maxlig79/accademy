#define BOOST_TEST_MODULE TEST_SERVER_CLIENT
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include "common.h"
#include <fstream>

std::ifstream client1{"output.client1"};

std::ifstream client2{"output.client2"};

BOOST_AUTO_TEST_SUITE(ServerClientTests)

BOOST_AUTO_TEST_CASE(test)
{
    system("./test.sh");
    std::string command;
    int nrLinesClient1 = 0;
    int nrLinesClient2 = 0;

    while (std::getline(client1, command))
    {
        switch (nrLinesClient1)
        {
        case 0:
        {
            BOOST_CHECK_EQUAL(command, "Add OK");
            break;
        }
        case 1:
        {
            BOOST_CHECK(command == "test1");
            break;
        }
        case 2:
        {
            BOOST_CHECK_EQUAL(command, "Add OK");
            break;
        }
        case 3:
        {
            BOOST_CHECK(command == "test2");
            break;
        }
        case 4:
        {
            BOOST_CHECK_EQUAL(command, "DELETE NOT OK");
            break;
        }
        default:
            break;
        }
        nrLinesClient1++;
    }
    BOOST_CHECK_MESSAGE(nrLinesClient1 == 5,
                        "result: " << nrLinesClient1);
    BOOST_CHECK(nrLinesClient1 == 5);

    while (std::getline(client2, command))
    {
        switch (nrLinesClient2)
        {
        case 0:
        {
            BOOST_CHECK_EQUAL(command, "Add OK");
            break;
        }
        case 1:
        {
            BOOST_CHECK(command == "silvana");
            break;
        }
        case 2:
        {
            BOOST_CHECK_EQUAL(command, "Add OK");
            break;
        }
        case 3:
        {
            BOOST_CHECK(command == "domnica");
            break;
        }
        case 4:
        {
            BOOST_CHECK_EQUAL(command, "Add OK");
            break;
        }
        case 5:
        {
            BOOST_CHECK_EQUAL(command, "paula");
            break;
        }
        case 6:
        {
            BOOST_CHECK_EQUAL(command, "DELETE OK");
            break;
        }
        case 7:
        {
            BOOST_CHECK_EQUAL(command, "Element not found");
            break;
        }
        default:
            break;
        }
        nrLinesClient2++;
    }
    BOOST_CHECK_MESSAGE(nrLinesClient2 == 8,
                        "result: " << nrLinesClient2);
    BOOST_CHECK(nrLinesClient2 == 8);
}

BOOST_AUTO_TEST_SUITE_END()