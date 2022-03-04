#define BOOST_TEST_MODULE TestArray
#include "DynamicStringArray.h"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestArray);

//-------Test for strings---------

BOOST_AUTO_TEST_CASE(test1)
{
    DynamicStringArray<string> array;
    array.addEntry("Romania");
    array.addEntry("England");
    array.addEntry("France");
    array.addEntry("Germany");
    BOOST_CHECK(array.getSize() == 4); // Test for addEntry
}

BOOST_AUTO_TEST_CASE(test2)
{

    DynamicStringArray<std::string> array2;
    array2.addEntry("Romania");
    array2.addEntry("England");
    array2.addEntry("France");
    array2.addEntry("Germany");
    BOOST_CHECK_EQUAL(*array2.getEntry(0), "Romania");
    BOOST_CHECK_EQUAL(*array2.getEntry(2), "France"); // test for getEntry
}

BOOST_AUTO_TEST_CASE(test3)
{

    DynamicStringArray<std::string> array4;
    array4.addEntry("Romania");
    array4.addEntry("England");
    array4.addEntry("France");
    array4.addEntry("Germany");
    DynamicStringArray<std::string> array5 = array4;
    BOOST_CHECK(array5.getSize() == array4.getSize()); // Test for copy constructor
}

BOOST_AUTO_TEST_CASE(test4)
{

    DynamicStringArray<std::string> array6, array7;
    array6.addEntry("Romania");
    array7.addEntry("England");
    array6 = array7;
    if (array6.getSize() != array7.getSize()) // test for assignment operator
        BOOST_ERROR("This is an error");
}

BOOST_AUTO_TEST_CASE(test5)
{

    DynamicStringArray<std::string> moveArray(DynamicStringArray<std::string>(vector<string>{"This", "is", "a", "move"}));
    BOOST_CHECK(moveArray.getSize() == 4);
    BOOST_CHECK(*moveArray.getEntry(3) == "move");
}

BOOST_AUTO_TEST_CASE(test6)
{

    DynamicStringArray<std::string> moveArray(DynamicStringArray<std::string>(vector<string>{"This", "is", "a", "move"}));
    DynamicStringArray<std::string> vec;
    vec = std::move(moveArray);
    BOOST_CHECK(vec.getSize() == 4);
    BOOST_CHECK(*vec.getEntry(0) == "This");
    BOOST_CHECK(*vec.getEntry(1) == "is");
    BOOST_CHECK(*vec.getEntry(2) == "a");
}
BOOST_AUTO_TEST_CASE(test7)
{

    DynamicStringArray<int> arr;
    arr.addEntry(1);
    arr.addEntry(2);
    arr.addEntry(3);
    arr.addEntry(4);
    arr.deleteEntry(3);
    BOOST_CHECK(arr.getSize() == 3); // Test for deleteEntry
}

//-------Tests for integers---------
BOOST_AUTO_TEST_CASE(test1_integer)
{
    DynamicStringArray<int> array9;
    array9.addEntry(1);
    array9.addEntry(2);
    array9.addEntry(3);
    array9.addEntry(4);
    BOOST_CHECK(array9.getSize() == 4); // Test for addEntry
}

BOOST_AUTO_TEST_CASE(test2_integer)
{

    DynamicStringArray<int> array10;
    array10.addEntry(1);
    array10.addEntry(2);
    array10.addEntry(3);
    array10.addEntry(4);
    BOOST_CHECK_EQUAL(*array10.getEntry(0), 1);
    BOOST_CHECK_EQUAL(*array10.getEntry(2), 3); // test for getEntry
}

BOOST_AUTO_TEST_CASE(test3_integer)
{

    DynamicStringArray<int> arr;
    arr.addEntry(1);
    arr.addEntry(2);
    arr.addEntry(3);
    arr.addEntry(4);
    DynamicStringArray<int> arr2 = arr;
    BOOST_CHECK(arr2.getSize() == arr.getSize()); // Test for copy constructor
}

BOOST_AUTO_TEST_CASE(test4_integer)
{

    DynamicStringArray<int> arr1, arr2;
    arr1.addEntry(1);
    arr2.addEntry(2);
    arr1 = arr2;
    if (arr1.getSize() != arr2.getSize()) // test for assignment operator
        BOOST_ERROR("This is an error");
}

BOOST_AUTO_TEST_CASE(test5_integer)
{

    DynamicStringArray<int> moveArray(DynamicStringArray<int>(vector<int>{1, 2, 3, 4}));
    BOOST_CHECK(moveArray.getSize() == 4);
    BOOST_CHECK(*moveArray.getEntry(3) == 4);
}

BOOST_AUTO_TEST_CASE(test6_integer)
{

    DynamicStringArray<int> moveArray(DynamicStringArray<int>(vector<int>{1, 2, 3, 4}));
    DynamicStringArray<int> vec;
    vec = std::move(moveArray);
    BOOST_CHECK(vec.getSize() == 4);
    BOOST_CHECK(*vec.getEntry(0) == 1);
    BOOST_CHECK(*vec.getEntry(1) == 2);
    BOOST_CHECK(*vec.getEntry(2) == 3);
}
BOOST_AUTO_TEST_CASE(test7_interger)
{

    DynamicStringArray<string> arr;
    arr.addEntry("RO");
    arr.addEntry("EN");
    arr.addEntry("FR");
    arr.addEntry("GR");
    arr.deleteEntry("FR");
    BOOST_CHECK(arr.getSize() == 3); // Test for deleteEntry
}

BOOST_AUTO_TEST_SUITE_END();