#include "DynamicStringArray.hpp"

DynamicStringArray::DynamicStringArray()
{
    dynamicArray = nullptr;
    size = 0;
}
int DynamicStringArray::getSize() const
{
    return size;
}
void DynamicStringArray::addEntry(const string &newString)
{
    string *newArray = new string[size + 1]; 
    for (int i = 0; i < size; i++)
    {
        newArray[i] = dynamicArray[i];
    }
    newArray[size] = newString;
    delete[] dynamicArray;
    dynamicArray = newArray;
    size++;
}
bool DynamicStringArray::deleteEntry(const string &newString)
{
    for (int i = 0; i < size; i++) {
        if (dynamicArray[i] == newString) {
            std::string *newArray = new std::string[size - 1];
            for (int j = 0; j < i; ++j) {
                newArray[j] = dynamicArray[j];
            }
            for (int j = i+1; j < size; ++j) {
                newArray[j-1] = dynamicArray[j];
            }
            delete[] dynamicArray;
            dynamicArray = newArray;
            --size;
            return true;
        }
    }
    return false;
}
string DynamicStringArray::getEntry(const int index) const
{
    if(index >=size)
    {
        return nullptr;
    }
    else
    {
        return dynamicArray[index];
    }
}
DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{
    size=obj.getSize();
    dynamicArray=new string[size];
    for(int i=0;i<size;i++)
    {
        dynamicArray[i]=obj.getEntry(i);
    }
}
DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}
DynamicStringArray& DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if(&obj != this)
    {
        size=obj.size;
        dynamicArray=new string[size];
        for(int i=0;i<size;i++)
        {
            dynamicArray[i]=obj.dynamicArray[i];
        }
    }
    return *this;
}