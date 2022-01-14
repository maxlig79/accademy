#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "Maxim.hpp"

BOOST_AUTO_TEST_CASE(test1)
{
    BOOST_CHECK(Maxim::maximOfThree(1, 2, 3) == 3);           
}
BOOST_AUTO_TEST_CASE(test2)
{
  BOOST_REQUIRE(Maxim::maximOfThree(1, 2, 3) == 3);
}
BOOST_AUTO_TEST_CASE(test3)
{
   if( Maxim::maximOfThree(1, 2, 3) != 3 )
      BOOST_ERROR( "Ouch..." );
}
BOOST_AUTO_TEST_CASE(test4)
{
   BOOST_CHECK_MESSAGE( Maxim::maximOfThree(1, 2, 3) == 3,  
                         "add(..) result: " << Maxim::maximOfThree(1, 2, 3) );
}
BOOST_AUTO_TEST_CASE(test5)
{
  BOOST_CHECK_EQUAL(Maxim::maximOfThree(1, 2, 3) , 3);
}