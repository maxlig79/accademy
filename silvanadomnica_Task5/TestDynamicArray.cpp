#define BOOST_TEST_MODULE TEST_DYNAMIC_STRING_ARRAY
#include <boost/test/included/unit_test.hpp>
#include "DynamicStringArray.hpp"

BOOST_AUTO_TEST_SUITE(DynamicStringArrayTests)
BOOST_AUTO_TEST_CASE(test_string)
{
    DynamicArray<std::string> arrayString;
    arrayString.addEntry("hello");
    arrayString.addEntry("bonjour");
    arrayString.addEntry("buna");
    arrayString.addEntry("");
    BOOST_CHECK_EQUAL(*arrayString.getEntry(0), "hello");
    BOOST_CHECK_EQUAL(*arrayString.getEntry(1), "bonjour");
    arrayString.deleteEntry("buna");
    BOOST_CHECK(arrayString.getSize() == 2);
    BOOST_CHECK_THROW(arrayString.addEntry(""),std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(test_int)
{
    DynamicArray<int> arrayInt;
    arrayInt.addEntry(1);
    arrayInt.addEntry(467);
    arrayInt.addEntry(791);
    arrayInt.addEntry(872);
    BOOST_CHECK(arrayInt.getSize() == 4);
    BOOST_CHECK_EQUAL(*arrayInt.getEntry(0), 1);
    BOOST_CHECK_EQUAL(*arrayInt.getEntry(1), 467);
    arrayInt.deleteEntry(1);
    BOOST_CHECK(arrayInt.getSize() == 3);
    BOOST_CHECK_THROW(*arrayInt.getEntry(9) == 872,std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_double)
{
    DynamicArray<double> arrayDouble;
    arrayDouble.addEntry(1.6);
    arrayDouble.addEntry(2.8);
    BOOST_CHECK(arrayDouble.getSize() == 2);
    DynamicArray<double> array = arrayDouble;
    BOOST_CHECK(arrayDouble.getSize() == array.getSize());
}
BOOST_AUTO_TEST_CASE(test_copy)
{
    DynamicArray<string> array6, array7;
    array6.addEntry("hello");
    array7.addEntry("hola");
    array6 = array7;
    if (array6.getSize() != array7.getSize())
        BOOST_ERROR("Ouch...");
}
BOOST_AUTO_TEST_CASE(test_constructor)
{
    DynamicArray<string> sarray(DynamicArray<string>(vector<string>{"Move", "is", "better"}));
    BOOST_CHECK(sarray.getSize() == 3);
    BOOST_CHECK(*sarray.getEntry(0) == "Move");
    BOOST_CHECK(*sarray.getEntry(1) == "is");
    BOOST_CHECK(*sarray.getEntry(2) == "better");
}
BOOST_AUTO_TEST_CASE(test_move)
{
    DynamicArray<string> sarray(DynamicArray<string>(vector<string>{"Move", "is", "better"}));
    DynamicArray<string> obj;
    obj = std::move(sarray);
    BOOST_CHECK(obj.getSize() == 3);
    BOOST_CHECK(*obj.getEntry(0) == "Move");
    BOOST_CHECK(*obj.getEntry(1) == "is");
}
BOOST_AUTO_TEST_SUITE_END()