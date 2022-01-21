#define BOOST_TEST_MODULE DynamicArray_test

#include <boost/test/unit_test.hpp>
#include <DynamicArray.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(DynamicArray_getEntry)
{
    DynamicArray arr;
    arr.addEntry("s1");
    arr.addEntry("s2");
    arr.addEntry("s3");
    BOOST_CHECK(arr.getEntry(0) == "s1");
    BOOST_CHECK(arr.getEntry(1) == "s2");
    BOOST_CHECK(arr.getEntry(2) == "s3");
    BOOST_CHECK(arr.size() == 3);
}

BOOST_AUTO_TEST_CASE(DynamicArray_deleteEntry)
{
    DynamicArray arr;
    arr.addEntry("s1");
    arr.addEntry("s2");
    arr.addEntry("s2");
    arr.addEntry("s3");

    BOOST_CHECK(arr.deleteEntry("s2"));

    BOOST_CHECK(arr.size() == 2);
    BOOST_CHECK(arr.getEntry(0) == "s1");
    BOOST_CHECK(arr.getEntry(1) == "s3");

    BOOST_CHECK(!arr.deleteEntry("s2"));
    BOOST_CHECK(!arr.deleteEntry("s4"));
}

BOOST_AUTO_TEST_CASE(DynamicArray_move)
{
    DynamicArray arr1;
    arr1.addEntry("s1");
    arr1.addEntry("s2");

    DynamicArray arr2;
    arr2 = std::move(arr1);
    BOOST_CHECK(arr2.size() == 2);

    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");

    DynamicArray arr3(std::move(arr2));
    BOOST_CHECK(arr3.size() == 2);

    BOOST_CHECK(arr3.getEntry(0) == "s1");
    BOOST_CHECK(arr3.getEntry(1) == "s2");
}

BOOST_AUTO_TEST_CASE(DynamicArray_copy)
{
    DynamicArray arr1;
    arr1.addEntry("s1");
    arr1.addEntry("s2");

    DynamicArray arr2(arr1);
    BOOST_CHECK(arr1.size() == 2);
    BOOST_CHECK(arr1.getEntry(0) == "s1");
    BOOST_CHECK(arr1.getEntry(1) == "s2");
    BOOST_CHECK(arr2.size() == 2);
    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");

    DynamicArray arr3;
    arr3 = arr2;
    BOOST_CHECK(arr2.size() == 2);
    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");
    BOOST_CHECK(arr3.size() == 2);
    BOOST_CHECK(arr3.getEntry(0) == "s1");
    BOOST_CHECK(arr3.getEntry(1) == "s2");
}
