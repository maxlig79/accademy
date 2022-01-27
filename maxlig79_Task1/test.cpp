#define BOOST_TEST_MODULE computemaxtest
#include <boost/test/included/unit_test.hpp>
#include "ComputeMax.h"

BOOST_AUTO_TEST_SUITE (computemaxtest)

BOOST_AUTO_TEST_CASE( max_test )
{
    ComputeMax cMax;
    // seven ways to detect and report the same error:
    BOOST_CHECK( cMax.Compute(9,7,3) == 9 );        // #1 continues on error

    BOOST_REQUIRE( cMax.Compute(1,7,22) == 22 );      // #2 throws on error

    if( cMax.Compute(6,13,4) != 13 )
        BOOST_ERROR( "Ouch..." );            // #3 continues on error

    if( cMax.Compute(11,7,8) != 11 )
        BOOST_FAIL( "Ouch..." );             // #4 throws on error

    if( cMax.Compute(1,1,5) != 5 ) throw "Ouch..."; // #5 throws on error

    BOOST_CHECK_MESSAGE( cMax.Compute(5,6,2) == 6,  // #6 continues on error
        "add(..) result: " << cMax.Compute(5,6,2) );

    BOOST_CHECK_EQUAL( cMax.Compute(7,12,19), 19 );	  // #7 continues on error
}

BOOST_AUTO_TEST_SUITE_END( )
