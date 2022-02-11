#define BOOST_TEST_MODULE TestArray
#include"DynamicStringArray.h"
#include<boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (TestArray);
BOOST_AUTO_TEST_CASE(test1){

    DynamicStringArray array;
    array.addEntry("Romania");
    array.addEntry("England");
    array.addEntry("France");
    array.addEntry("Germany");
    BOOST_CHECK(array.getSize() == 4);//Test for addEntry
}

BOOST_AUTO_TEST_CASE(test2){

    DynamicStringArray array2;
    array2.addEntry("Romania");
    array2.addEntry("England");
    array2.addEntry("France");
    array2.addEntry("Germany");
    BOOST_REQUIRE(array2.getSize() == 4);//Test for addEntry with BOOST_REQUIRE
}
BOOST_AUTO_TEST_CASE(test3){

    DynamicStringArray array3;
    array3.addEntry("Romania");
    array3.addEntry("England");
    array3.addEntry("France");
    array3.addEntry("Germany");
    array3.deleteEntry("France");
    BOOST_CHECK(array3.getSize() == 3);//Test for deleteEntry
}

BOOST_AUTO_TEST_CASE(test4){

    DynamicStringArray array4;
    array4.addEntry("Romania");
    array4.addEntry("England");
    array4.addEntry("France");
    array4.addEntry("Germany");
    DynamicStringArray array5=array4;
    BOOST_CHECK(array5.getSize() == array4.getSize());//Test for copy constructor
}


BOOST_AUTO_TEST_CASE(test5){

    DynamicStringArray array6,array7;
    array6.addEntry("Romania");
    array6.addEntry("England");
    array6.addEntry("France");
    array6.addEntry("Germany");
    array6=array7;
    if(array6.getSize() != array7.getSize())//Test for copy constructor
        BOOST_ERROR("This is an error");
}

BOOST_AUTO_TEST_CASE(test6){
    DynamicStringArray array1,array2;
    array1.addEntry("Romania");
    array2.addEntry("England");
    array1=array2;
    BOOST_CHECK(array1.getSize()==array2.getSize()); //Test for overload
}
BOOST_AUTO_TEST_SUITE_END();