#define BOOST_TEST_MODULE TEST_DYNAMIC_ARRAY
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <DynamicArray.hpp>


BOOST_AUTO_TEST_SUITE(DynamicArrayTEST)

BOOST_AUTO_TEST_CASE(test_1_max)
{
    DynamicArray<std::string> obj1;
    obj1.addEntry("unu");
    obj1.addEntry("");
    obj1.addEntry("doi");
    BOOST_CHECK(obj1.get_size() == 2);
    BOOST_CHECK(*obj1.getEntry(0) == "unu");
    BOOST_CHECK(*obj1.getEntry(1) == "doi");
    BOOST_CHECK(obj1.getEntry(-1) == nullptr);
}

BOOST_AUTO_TEST_CASE(test_2_max)
{
    DynamicArray<int> obj1;
    obj1.addEntry(1);
    obj1.addEntry(2);
    BOOST_CHECK(obj1.get_size() == 2);
    BOOST_CHECK(*obj1.getEntry(0) == 1);
    BOOST_CHECK(*obj1.getEntry(1) == 2);
    BOOST_CHECK(obj1.getEntry(-1) == nullptr);
    BOOST_CHECK(obj1.deleteEntry(1) == true);
    BOOST_CHECK(obj1.deleteEntry(5) == false);
}

BOOST_AUTO_TEST_CASE(test_3_max)
{
    DynamicArray<char> obj1;
    obj1.addEntry('a');
    obj1.addEntry('b');
    BOOST_CHECK(obj1.get_size() == 2);
    BOOST_CHECK(*obj1.getEntry(0) == 'a');
    BOOST_CHECK(*obj1.getEntry(1) == 'b');
    BOOST_CHECK(obj1.getEntry(-1) == nullptr);
}


BOOST_AUTO_TEST_CASE(test_4_max)
{
    DynamicArray<std::string> obj1;
    obj1.addEntry("unu");
    obj1.addEntry("doi");
    obj1.addEntry("trei");
    DynamicArray<std::string> obj2 = obj1;
    BOOST_CHECK(obj1.get_size() == obj2.get_size());
    DynamicArray<std::string> obj3;
    obj3 = obj2;
    obj3 = obj3;
    BOOST_CHECK(obj3.get_size() == obj2.get_size());
}

BOOST_AUTO_TEST_CASE(test_5_max)
{
    DynamicArray<std::string> obj1(DynamicArray<std::string>(std::vector<std::string>{"unu", "doi", "trei"}));
    BOOST_CHECK(*obj1.getEntry(0) == "unu");
    BOOST_CHECK(*obj1.getEntry(1) == "doi");
    BOOST_CHECK(*obj1.getEntry(2) == "trei");
    BOOST_CHECK(obj1.getEntry(-1) == nullptr);
}

BOOST_AUTO_TEST_CASE(test_6_max)
{
    std::vector<std::string> inputs{"unu", "doi", "trei"};
    DynamicArray<std::string> obj1(inputs);
    DynamicArray<std::string> obj2(std::move(obj1));
    BOOST_CHECK(*obj2.getEntry(0) == "unu");
    BOOST_CHECK(*obj2.getEntry(1) == "doi");
    BOOST_CHECK(*obj2.getEntry(2) == "trei");
    BOOST_CHECK(obj2.getEntry(-1) == nullptr);
    BOOST_CHECK(obj2.get_size() == 3);
}

BOOST_AUTO_TEST_CASE(test_7_max)
{
    std::vector<std::string> inputs{"unu", "doi", "trei"};
    DynamicArray<std::string> obj1(inputs);
    DynamicArray<std::string> obj2;
    obj2 = std::move(obj1);
    obj2 = std::move(obj2);
    BOOST_CHECK(*obj2.getEntry(0) == "unu");
    BOOST_CHECK(*obj2.getEntry(1) == "doi");
    BOOST_CHECK(*obj2.getEntry(2) == "trei");
    BOOST_CHECK(obj2.getEntry(-1) == nullptr);
    BOOST_CHECK(obj2.get_size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()