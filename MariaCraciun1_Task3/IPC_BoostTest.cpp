#define BOOST_TEST_MODULE IPC_CLIENT_SERVER_TEST
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iterator>
#include <iostream>

std::ifstream client1 {"log.client1"};
std::ifstream client2 {"log.client2"};

BOOST_AUTO_TEST_SUITE ( ClientServerIPC )

BOOST_AUTO_TEST_CASE ( test )
{
    system ( "IPC_Script.sh" );
    std::string output;
    int count = 0;

    while ( std::getline(client1,output) )
    {
        switch(count)
        {
            case 0:
                BOOST_CHECK (output == "Add ok");
                break;
            case 1:
                BOOST_CHECK (output == "Element not found");
                break;
            case 2:
                BOOST_CHECK(output == "Add ok");
                break;   
            case 3:
                BOOST_CHECK(output == "Delete ok");
                break;
            case 4:
                BOOST_CHECK(output == "test2C1");
                break;
            case 5:
                BOOST_CHECK(output == "Delete not ok");
                break;
            default:    
                break;
        }
        count ++;
    }
    BOOST_CHECK (count == 6);

    count = 0;
    while ( std::getline(client2, output) )
    {
        switch(count)
        {
            case 0:
                BOOST_CHECK ( output == "Add ok");
                break;
            case 1:
                BOOST_CHECK ( output == "Add ok");
                break;
            case 2:
                BOOST_CHECK ( output == "Delete ok");
                break;               
            case 3:
                BOOST_CHECK ( output == "test2C2");
                break;
            default:    
                break;
        }
        count ++;
    }
    BOOST_CHECK (count == 4);
}

BOOST_AUTO_TEST_SUITE_END ()