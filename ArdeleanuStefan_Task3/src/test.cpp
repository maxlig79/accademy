#define BOOST_TEST_MODULE TEST_CLIENT_SERVER_IPC
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
std::ifstream client1{"tmp/log.0"};
std::ifstream client2{"tmp/log.1"};

BOOST_AUTO_TEST_SUITE(ClientServerIPCTest)

BOOST_AUTO_TEST_CASE(test_1)
{
    system("./src/script.sh ");
    std::string output;
    int count = 0;
    while (std::getline(client1, output))
    {
        switch (count)
        {
        case 0:
            BOOST_CHECK(output == "Add OK");
            break;

        case 1:
            BOOST_CHECK(output == "unu");
            break;

        case 2:
            BOOST_CHECK(output == "DELETE NOT OK");
            break;
        default:
            break;
        }

        count++;
    }
    BOOST_CHECK(count == 3);
    count = 0;
    while (std::getline(client2, output)){
        switch (count)
        {
        case 0:
            BOOST_CHECK(output == "Add OK");
            break;

        case 1:
            BOOST_CHECK(output == "NOT FOUND");
            break;

        case 2:
            BOOST_CHECK(output == "DELETE OK");
            break;
        default:
            break;
        }

        count++;
    }
    BOOST_CHECK(count == 3);
}

BOOST_AUTO_TEST_SUITE_END()