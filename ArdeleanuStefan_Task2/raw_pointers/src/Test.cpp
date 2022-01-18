#define BOOST_TEST_MODULE TEST_DYNAMIC_STRING_ARRAY
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <DynamicStringArray.hpp>


BOOST_AUTO_TEST_SUITE(DynamicStringArrayTEST)

BOOST_AUTO_TEST_CASE(test_1_max)
{
    DynamicStringArray obj1;
    obj1.addEntry("unu");
    obj1.addEntry("doi");
    BOOST_CHECK(obj1.get_size() == 2);
}

BOOST_AUTO_TEST_CASE(test_2_max)
{
    DynamicStringArray obj1;
    obj1.addEntry("unu");
    obj1.addEntry("doi");
    BOOST_CHECK(*obj1.getEntry(0) == "unu");
    BOOST_CHECK(*obj1.getEntry(1) == "doi");
    BOOST_CHECK(obj1.getEntry(-1) == nullptr);
}

BOOST_AUTO_TEST_CASE(test_3_max)
{
    DynamicStringArray obj1;
    obj1.addEntry("unu");
    obj1.addEntry("doi");
    obj1.addEntry("trei");
    obj1.deleteEntry("doi");
    BOOST_CHECK(obj1.get_size() == 2);
    obj1.deleteEntry("patru");
    BOOST_CHECK(obj1.get_size() == 2);
}

BOOST_AUTO_TEST_CASE(test_4_max)
{
    DynamicStringArray obj1;
    obj1.addEntry("unu");
    obj1.addEntry("doi");
    obj1.addEntry("trei");
    DynamicStringArray obj2 = obj1;
    BOOST_CHECK(obj1.get_size() == obj2.get_size());
    DynamicStringArray obj3;
    obj3 = obj2;
    obj3 = obj3;
    BOOST_CHECK(obj3.get_size() == obj2.get_size());
}

BOOST_AUTO_TEST_SUITE_END()