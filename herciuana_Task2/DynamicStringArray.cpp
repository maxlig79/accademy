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
    size++;
    delete[] dynamicArray;
    dynamicArray = Array;
}

bool DynamicStringArray::deleteEntry(const string &String)
{
    bool r = false;
    int i;
    for (int i = 0; i < size; i++)
    {
        if (dynamicArray[i] == String)
        {
            r = true;
        }
    }
    if (r == true)
    {
        return r;
    }
    else
        return false;
}

string DynamicStringArray::getEntry(const int index) const
{
    if ((index < 0) || (index >= size))
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
        dynamicArray[i] = obj.dynamicArray[i];
    }
}

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if (this != &obj)
    {
        delete[] dynamicArray;
        dynamicArray = new string[size];
        size = obj.get_Size();
        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = obj.dynamicArray[i];
        }
    }
    return *this;
}
DynamicStringArray::DynamicStringArray(DynamicStringArray &&obj)
{
    dynamicArray = obj.dynamicArray;
    size = obj.get_Size();
    obj.dynamicArray = nullptr;
    obj.size = 0;
}

DynamicStringArray &DynamicStringArray::operator=(DynamicStringArray &&obj)
{
    if (this != &obj)
    {
        delete[] dynamicArray;
        dynamicArray = obj.dynamicArray;
        size = obj.get_Size();
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
    delete[] dynamicArray;
}