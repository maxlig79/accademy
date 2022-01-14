#define BOOST_TEST_MODULE MaximNumbers
#include <boost/test/included/unit_test.hpp>
#include "max.hpp"

BOOST_AUTO_TEST_CASE(maxim_test)
{
    maxim max;

    BOOST_CHECK(max.MaximNumbers(1, 2, 3) == 3);

    BOOST_REQUIRE(max.MaximNumbers(1, 2, 3) == 3);

    if (max.MaximNumbers(1, 2, 3) != 3)
        BOOST_ERROR("Ouch...");

    if (max.MaximNumbers(1, 2, 3) != 3)
        BOOST_FAIL("Ouch...");

    if (max.MaximNumbers(1, 2, 3) != 3)
        throw "Ouch...";

    BOOST_CHECK_MESSAGE(max.MaximNumbers(1, 2, 3) == 3,
                        "add(..) result: " << max.MaximNumbers(1, 2, 3));

    BOOST_CHECK_EQUAL(max.MaximNumbers(1, 2, 3), 3);
}
