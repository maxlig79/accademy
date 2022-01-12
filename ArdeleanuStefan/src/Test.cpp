#define BOOST_TEST_MODULE TEST_MAXIM
#define BOOST_TEST_DYN_LINK 
#include <boost/test/unit_test.hpp>
#include <Maxim.hpp>

BOOST_AUTO_TEST_CASE( test_max )
{
    Maxim m;

    BOOST_CHECK( m.calculMaxim(4,4,3) == 4 );

    BOOST_CHECK( m.calculMaxim(4,4,3) == 5 );

    BOOST_CHECK_MESSAGE( m.calculMaxim(4,4,3) == 5, " rezultat astepat " << m.calculMaxim(4,4,3));
}