#define BOOST_TEST_MODULE TEST
#include <boost/test/included/unit_test.hpp>
#include "DynamicStringArray.hpp"

BOOST_AUTO_TEST_SUITE(DynamicStringArrayTEST)
BOOST_AUTO_TEST_CASE(test1)
{
    DynamicStringArray array1;
    array1.addEntry("yes");
    array1.addEntry("no");
    array1.addEntry("probable");
    BOOST_CHECK(array1.get_Size() == 3);
}
BOOST_AUTO_TEST_CASE(test2)
{
    DynamicStringArray array2;
    array2.addEntry("yes");
    array2.addEntry("no");
    array2.addEntry("probable");
    BOOST_CHECK_EQUAL(array2.getEntry(0), "yes");
    BOOST_CHECK_EQUAL(array2.getEntry(1), "no");
}

BOOST_AUTO_TEST_CASE(test3)
{
    DynamicStringArray array3;
    array3.addEntry("yes");
    array3.addEntry("no");
    array3.addEntry("probable");
    array3.deleteEntry("yes");
    BOOST_CHECK(array3.get_Size() == 2);
}

BOOST_AUTO_TEST_CASE(test4)
{
    DynamicStringArray array4;
    array4.addEntry("yes");
    array4.addEntry("no");
    array4.addEntry("probable");
    DynamicStringArray array5 = array4;
    BOOST_CHECK(array4.get_Size() == array5.get_Size());
}
BOOST_AUTO_TEST_CASE(test5)
{
    DynamicStringArray array6, array7;
    array6.addEntry("yes");
    array6.addEntry("no");
    array6 = array7;
    if (array6.get_Size() != array7.get_Size())
        BOOST_ERROR("Error");
}

BOOST_AUTO_TEST_CASE(test6)
{
    DynamicStringArray SArray(DynamicStringArray(std::vector<string>{"Move", " is ", "better!"}));
    BOOST_CHECK(SArray.get_Size() == 3);
    BOOST_CHECK(SArray.getEntry(0) == "Move");
}

BOOST_AUTO_TEST_CASE(test7)
{
    DynamicStringArray SArray(DynamicStringArray(vector<string>{"Move", " is ", "better!"}));
    DynamicStringArray obj;
    obj = std::move(SArray);
    BOOST_CHECK(obj.get_Size() == 3);
    BOOST_CHECK(obj.getEntry(0) == "Move");
}

BOOST_AUTO_TEST_SUITE_END()