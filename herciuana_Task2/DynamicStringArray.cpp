#include "DynamicStringArray.hpp"

DynamicStringArray::DynamicStringArray() : dynamicArray(nullptr), size(0)
{
}

int DynamicStringArray::get_Size() const
{
    return size;
}

void DynamicStringArray::addEntry(const string &String)
{
    string *Array = new string[size + 1];
    for (int i = 0; i < size; i++)
    {
        Array[i] = dynamicArray[i];
    }
    Array[size] = String;
    // delete[] dynamicArray;
    dynamicArray = Array;
    size++;
}

bool DynamicStringArray::deleteEntry(const string &String)
{
    bool r = false;
    for (int i = 0; i < size; i++)
    {
        if (dynamicArray[i] == String)
        {
            for (int j = i; j < size - 1; j++)
            {
                dynamicArray[j] = dynamicArray[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

string DynamicStringArray::getEntry(const int index) const
{
    if (index >= size)
    {
        return " ";
    }
    else
    {
        return dynamicArray[index];
    }
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{
    size = obj.get_Size();
    dynamicArray = new string[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.getEntry(i);
    }
}

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        size = obj.size;
        dynamicArray = new string[size];
    }
    return *this;
}
DynamicStringArray::DynamicStringArray(DynamicStringArray &&obj) : size(obj.size), dynamicArray(obj.dynamicArray)
{

    obj.dynamicArray = nullptr;
    obj.size = 0;
}

DynamicStringArray &DynamicStringArray::operator=(DynamicStringArray &&obj)
{
    if (this != &obj)
    {
        delete[] dynamicArray;
        dynamicArray = obj.dynamicArray;
        size = obj.size;
        obj.dynamicArray = nullptr;
        obj.size = 0;
    }
    return *this;
}
DynamicStringArray::DynamicStringArray(const vector<string> &obj) : DynamicStringArray()
{
    for (auto i : obj)
    {
        DynamicStringArray::addEntry(i);
    }
}
DynamicStringArray::~DynamicStringArray()
{
    {
        delete[] dynamicArray;
    }
}
