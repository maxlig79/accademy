#define BOOST_TEST_MODULE Max3_test

#include <boost/test/unit_test.hpp>
#include <DynamicArray.hpp>

BOOST_AUTO_TEST_CASE(arr_test)
{
    DynamicArray arr;
    arr.addEntry("s1");
    arr.addEntry("s2");
    arr.addEntry("s3");
    BOOST_CHECK(arr[0] == "s1");
    BOOST_CHECK(arr[1] == "s2");
    BOOST_CHECK(arr[2] == "s3");
}
