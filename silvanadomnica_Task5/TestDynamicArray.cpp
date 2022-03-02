#define BOOST_TEST_MODULE TEST_DYNAMIC_STRING_ARRAY
#include <boost/test/included/unit_test.hpp>
#include "DynamicStringArray.hpp"

BOOST_AUTO_TEST_SUITE(DynamicStringArrayTests)
BOOST_AUTO_TEST_CASE(test1)
{
    DynamicArray<std::string> array1;
    array1.addEntry("hello");
     array1.addEntry("hola");
    array1.addEntry("bonjour");
    BOOST_CHECK(array1.getSize() == 3);
}
BOOST_AUTO_TEST_CASE(test2)
{
    DynamicArray<string> array2;
    array2.addEntry("hello");
    array2.addEntry("hola");
    array2.addEntry("bonjour");
    BOOST_CHECK_EQUAL(array2.getEntry(0), "hello");
    BOOST_CHECK_EQUAL(array2.getEntry(2), "bonjour");
}
BOOST_AUTO_TEST_CASE(test3)
{
    DynamicArray<string> array3;
    array3.addEntry("hello");
    array3.addEntry("hola");
    array3.addEntry("bonjour");
    array3.deleteEntry("hello");
    BOOST_CHECK(array3.getSize() == 2);
}
BOOST_AUTO_TEST_CASE(test4)
{
    DynamicArray<string> array4;
    array4.addEntry("hello");
    array4.addEntry("hola");
    array4.addEntry("bonjour");
    DynamicArray<string> array5 = array4;
    BOOST_CHECK(array4.getSize() == array5.getSize());
}
BOOST_AUTO_TEST_CASE(test5)
{
    DynamicArray<string> array6, array7;
    array6.addEntry("hello");
    array7.addEntry("hola");
    array6 = array7;
    if (array6.getSize() != array7.getSize())
        BOOST_ERROR("Ouch...");
}
BOOST_AUTO_TEST_CASE(test6)
{
    DynamicArray<string> sarray(DynamicArray<string>(vector<string>{"Move", "is", "better"}));
    BOOST_CHECK(sarray.getSize() == 3);
    BOOST_CHECK(sarray.getEntry(0) == "Move");
    BOOST_CHECK(sarray.getEntry(1) == "is");
    BOOST_CHECK(sarray.getEntry(2) == "better");
}
BOOST_AUTO_TEST_CASE(test7)
{
    DynamicArray<string> sarray(DynamicArray<string>(vector<string>{"Move", "is", "better"}));
    DynamicArray<string> obj;
    obj = std::move(sarray);
    BOOST_CHECK(obj.getSize() == 3);
    BOOST_CHECK(obj.getEntry(0) == "Move");
    BOOST_CHECK(obj.getEntry(1) == "is");
}
BOOST_AUTO_TEST_SUITE_END()