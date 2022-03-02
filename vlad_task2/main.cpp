#include <iostream>
#include <DynamicArray.hpp>
#include <string>

int main()
{
    DynamicArray<std::string> arr;
    arr.addEntry("str1");
    std::cout << "Added str1" << std::endl;

    arr.addEntry("str2");
    std::cout << "Added str2" << std::endl;

    arr.addEntry("str2");
    std::cout << "Added str22" << std::endl;

    arr.addEntry("str4");
    std::cout << "Added str4" << std::endl;

    std::cout << arr.getEntry(0) << arr.getEntry(0) << arr.getEntry(2) << arr.getEntry(3) << std::endl;
    arr.deleteEntry("str2");
    std::cout << arr.getEntry(0) << arr.getEntry(1) << arr.getEntry(2) << std::endl;
}