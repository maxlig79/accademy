#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "Maxim.hpp"

BOOST_AUTO_TEST_CASE(my_test)
{
    Maxim max;
    BOOST_CHECK(max.maximOfThree(1, 2, 3) == 3);

    BOOST_REQUIRE(max.maximOfThree(1, 2, 3) == 3);

    if( max.maximOfThree(1, 2, 3) != 3 )
      BOOST_ERROR( "Ouch..." );           

    if( max.maximOfThree(1, 2, 3) != 3 )
      BOOST_FAIL( "Ouch..." );             

    if( max.maximOfThree(1, 2, 3) != 3 ) throw "Ouch..."; 

    BOOST_CHECK_MESSAGE( max.maximOfThree(1, 2, 3) == 3,  
                         "add(..) result: " << max.maximOfThree(1, 2, 3) );

    BOOST_CHECK_EQUAL(max.maximOfThree(1, 2, 3) , 3);
}