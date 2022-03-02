#define BOOST_TEST_MODULE DynamicArray_test

#include <boost/test/unit_test.hpp>
#include <DynamicArray.hpp>
#include <iostream>
#include <vector>

BOOST_AUTO_TEST_CASE(DynamicArray_getEntry)
{
    DynamicArray<std::string> arr;
    arr.addEntry("s1");
    arr.addEntry("s2");
    arr.addEntry("s3");
    BOOST_CHECK(arr.getEntry(0) == "s1");
    BOOST_CHECK(arr.getEntry(1) == "s2");
    BOOST_CHECK(arr.getEntry(2) == "s3");
    BOOST_CHECK(arr.size() == 3);
}

BOOST_AUTO_TEST_CASE(DynamicArray_addEntryException)
{
    DynamicArray<std::string> strArr;
    DynamicArray<char> chArr;
    BOOST_CHECK_THROW(strArr.addEntry(""), std::invalid_argument);
    BOOST_CHECK_THROW(chArr.addEntry('\0'), std::invalid_argument);
    BOOST_CHECK_NO_THROW(strArr.addEntry("str1"));
    BOOST_CHECK_NO_THROW(chArr.addEntry('a'));
}

BOOST_AUTO_TEST_CASE(DynamicArray_getEntryException)
{
    DynamicArray<std::string> arr;
    arr.addEntry("str1");
    BOOST_CHECK_THROW(arr.getEntry(1), std::out_of_range);
    BOOST_CHECK_NO_THROW(arr.getEntry(0));
}

BOOST_AUTO_TEST_CASE(DynamicArray_deleteEntry)
{
    DynamicArray<std::string> arr;
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
    DynamicArray<std::string> arr1;
    arr1.addEntry("s1");
    arr1.addEntry("s2");

    DynamicArray<std::string> arr2;
    arr2 = std::move(arr1);
    BOOST_CHECK(arr2.size() == 2);

    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");

    DynamicArray<std::string> arr3(std::move(arr2));
    BOOST_CHECK(arr3.size() == 2);

    BOOST_CHECK(arr3.getEntry(0) == "s1");
    BOOST_CHECK(arr3.getEntry(1) == "s2");

    DynamicArray<std::string> arr4;
    arr4 = DynamicArray<std::string>(std::vector<std::string>{"Move","is","better"});
}

BOOST_AUTO_TEST_CASE(DynamicArray_copy)
{
    DynamicArray<std::string> arr1;
    arr1.addEntry("s1");
    arr1.addEntry("s2");

    DynamicArray<std::string> arr2(arr1);
    BOOST_CHECK(arr1.size() == 2);
    BOOST_CHECK(arr1.getEntry(0) == "s1");
    BOOST_CHECK(arr1.getEntry(1) == "s2");
    BOOST_CHECK(arr2.size() == 2);
    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");

    DynamicArray<std::string> arr3;
    arr3 = arr2;
    BOOST_CHECK(arr2.size() == 2);
    BOOST_CHECK(arr2.getEntry(0) == "s1");
    BOOST_CHECK(arr2.getEntry(1) == "s2");
    BOOST_CHECK(arr3.size() == 2);
    BOOST_CHECK(arr3.getEntry(0) == "s1");
    BOOST_CHECK(arr3.getEntry(1) == "s2");
}

BOOST_AUTO_TEST_CASE(DynamicArray_container)
{
    DynamicArray<std::string> sarray(DynamicArray<std::string>(std::vector<std::string>{"Move", "is", "better"}));
    BOOST_CHECK(sarray.size() == 3);
    BOOST_CHECK(sarray.getEntry(0) == "Move");
    BOOST_CHECK(sarray.getEntry(1) == "is");
    BOOST_CHECK(sarray.getEntry(2) == "better");
}

//Non-specialized template instance
BOOST_AUTO_TEST_CASE(DynamicArray_int)
{
    DynamicArray<int> arr;
    arr.addEntry(0);
    arr.addEntry(1);
    BOOST_CHECK(arr.getEntry(0) == 0);
    BOOST_CHECK(arr.getEntry(1) == 1);
    BOOST_CHECK(arr.size() == 2);
}

//This should raise a compile time error if DynamicArray is not implemented properly
/* BOOST_AUTO_TEST_CASE(DynamicArray_struct)
{
    struct TestType
    {
        int a;
        int b;
        TestType(int a, int b);
    };
    TestType var(1, 2);
    DynamicArray<TestType> arr;
    arr.addEntry(var);
} */