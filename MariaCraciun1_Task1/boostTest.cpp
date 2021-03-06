#define BOOST_TEST_MODULE computeMaxTest
#include <boost/test/included/unit_test.hpp>
#include "Max.hpp"

BOOST_AUTO_TEST_SUITE (computeMaxTest)

BOOST_AUTO_TEST_CASE( max_test )
{
    // seven ways to detect and report the same error:
    BOOST_CHECK( Max::ComputeMax(9,7,3) == 9 );        // #1 continues on error

    BOOST_REQUIRE( Max::ComputeMax(1,7,22) == 22 );      // #2 throws on error

    if( Max::ComputeMax(6,13,4) != 13 )
        BOOST_ERROR( "Computation not done correctly..." );            // #3 continues on error

    if( Max::ComputeMax(11,7,8) != 11 )
        BOOST_FAIL( "Computation not done correctly..." );             // #4 throws on error

    if( Max::ComputeMax(1,1,5) != 5 ) throw "Computation not done correctly..."; // #5 throws on error

    BOOST_CHECK_MESSAGE( Max::ComputeMax(5,6,2) == 6,  // #6 continues on error
        "add(..) result: " << Max::ComputeMax(5,6,2) );

    BOOST_CHECK_EQUAL( Max::ComputeMax(7,12,19), 19 );	  // #7 continues on error
}

BOOST_AUTO_TEST_SUITE_END( )