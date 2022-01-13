#define BOOST_TEST_MODULE TEST_MAXIM
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <Maxim.hpp>

BOOST_AUTO_TEST_SUITE(MaximTests)

BOOST_AUTO_TEST_CASE(test_1_max)
{
    BOOST_CHECK(Maxim::calculMaxim(3, 2, 4) == 4);
}

BOOST_AUTO_TEST_CASE(test_2_max)
{
    BOOST_REQUIRE(Maxim::calculMaxim(3, 2, 4) == 4);
}

BOOST_AUTO_TEST_CASE(test_3_max)
{
    if (Maxim::calculMaxim(3, 2, 4) != 5)
        BOOST_ERROR("Ouch...");
}

BOOST_AUTO_TEST_CASE(test_4_max)
{
    if (Maxim::calculMaxim(3, 2, 4) != 5)
        throw "EROARE";
}

BOOST_AUTO_TEST_SUITE_END()