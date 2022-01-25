#include "DynamicStringArray.hpp"

DynamicStringArray::DynamicStringArray()
{
    dynamicArray = nullptr;
    size = 0;
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
    delete[] dynamicArray;
    dynamicArray = Array;
    size++;
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
        size--;
}

string DynamicStringArray::getEntry(const int index) const
{
    if ((index < 0) || (index >= size))
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
    size = obj.get_Size();
    dynamicArray = new string[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.getEntry(i);
    }
}

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    DynamicStringArray temp(obj);
    if (this->size != 0)
    {
        delete[] this->dynamicArray;
        this->size = obj.get_Size();
        this->dynamicArray = new string[this->size];
        for (int i = 0; i < this->size; i++)
        {
            this->dynamicArray[i] = obj.getEntry(i);
        }
    }
    return *this;
}

DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}