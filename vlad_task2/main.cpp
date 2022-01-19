#include <iostream>
#include <DynamicArray.hpp>

int main()
{
    DynamicArray arr;
    arr.addEntry("str1");
    std::cout << "Added str1" << std::endl;

    arr.addEntry("str2");
    std::cout << "Added str2" << std::endl;

    arr.addEntry("str2");
    std::cout << "Added str22" << std::endl;

    arr.addEntry("str4");
    std::cout << "Added str4" << std::endl;

    std::cout << arr[0] << arr[1] << arr[2] << arr[3] << std::endl;
    arr.deleteEntry("str2");
    std::cout << arr[0] << arr[1] << arr[2] << std::endl;
}