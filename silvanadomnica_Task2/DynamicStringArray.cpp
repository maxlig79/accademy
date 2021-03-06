#include "DynamicStringArray.hpp"

DynamicStringArray::DynamicStringArray() : size(0), dynamicArray(nullptr)
{
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
    bool found = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (newString == dynamicArray[i])
        {
            found = true;
            break;
        }
    }
    if (found == true)
    {
        std::string *temp = dynamicArray;
        dynamicArray = new std::string[size - 1];
        for (int j; j < size; j++)
        {
            if (j < i)
            {
                dynamicArray[j] = temp[j];
            }
            else if (j > i)
            {
                dynamicArray[j - 1] = temp[j];
            }
        }
        size--;
    }

    return found;
}
string DynamicStringArray::getEntry(const int index) const
{
    if (index >= size)
    {
        return "";
    }
    else
    {
        return dynamicArray[index];
    }
}
DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{
    size = obj.getSize();
    dynamicArray = new string[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.getEntry(i);
    }
}
DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}
DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        size = obj.size;
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = obj.dynamicArray[i];
        }
    }
    return *this;
}
DynamicStringArray::DynamicStringArray(DynamicStringArray &&other) : size(other.size), dynamicArray(other.dynamicArray)
{
    other.dynamicArray = nullptr;
    other.size = 0;
}
DynamicStringArray &DynamicStringArray::operator=(DynamicStringArray &&other)
{
    if (this != &other)
    {
        delete[] dynamicArray;
        dynamicArray = other.dynamicArray;
        size = other.size;
        other.dynamicArray = nullptr;
        other.size = 0;
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