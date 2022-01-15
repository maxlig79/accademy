#define BOOST_TEST_MODULE Max3_test

//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <Max3.hpp>

BOOST_AUTO_TEST_CASE(max_test)
{
    Max3 max;
    BOOST_CHECK(max.max(1, 3, 2) == 3);
    BOOST_CHECK(max.max(1, 2, 3) == 3);
    BOOST_CHECK(max.max(3, 2, 1) == 3);
}
