#include"DynamicStringArray.h"
#include<iostream>
using namespace std;
int main()
{
    DynamicStringArray array;
    array.addEntry("Romania");
    array.addEntry("England");
    array.addEntry("France");
    array.addEntry("Germany");
    std::cout<<"The number of elements is "<<array.getSize();
   
    return 0;
}