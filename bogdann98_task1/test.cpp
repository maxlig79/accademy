#define BOOST_TEST_MODULE MyTest
#include"Maxim.h"
#include<boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (MyTest)
BOOST_AUTO_TEST_CASE(test)
{
    BOOST_CHECK(Maxim::max(3,2,1)==3); //test 1

    BOOST_REQUIRE(Maxim::max(1,3,5)==5);//test 2

    if(Maxim::max(15,16,13)!=16)    
         BOOST_FAIL( "Ouch...."); //test 3
    
    BOOST_CHECK_MESSAGE(Maxim::max(7,8,5)==8,
        "add(..) result: "<<Maxim::max(7,8,5)); //test 4

    BOOST_CHECK_EQUAL(Maxim::max(3,4,5),5); //test 5
    
}

BOOST_AUTO_TEST_SUITE_END()