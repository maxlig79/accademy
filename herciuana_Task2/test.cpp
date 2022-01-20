#define BOOST_TEST_MODULE TEST_DYNAMIC_STRING_ARRAY
#include <boost/test/included/unit_test.hpp>
#include "DynamicStringArray.hpp"

BOOST_AUTO_TEST_CASE(test1)
{
    DynamicStringArray array1;
    array1.addEntry("salut");
    array1.addEntry("hola");
    array1.addEntry("hello");
    BOOST_CHECK(array1.get_Size() == 3);
}