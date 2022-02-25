#include "DynamicStringArray.h"
// default constructor that sets the dynamic array to nullptr and sets size to 0
DynamicStringArray::DynamicStringArray() : size{0}, dynamicArray{nullptr}
{
}

// a function that return size
int DynamicStringArray::getSize() const
{
    return size;
}

// function creates a new dynamic array one element larger than dynamicArray and copy all element into the new array
void DynamicStringArray::addEntry(const string &String)
{
    string *newdynamicArray = new string[size + 1];
    for (int i = 0; i < size; i++)
    {
        newdynamicArray[i] = dynamicArray[i];
    }
    newdynamicArray[size] = String;
    delete[] dynamicArray;
    dynamicArray = newdynamicArray;
    size++;
}
// the function boolean should search dynamicArray for the string
bool DynamicStringArray::deleteEntry(const string &String)
{
    bool found = false;
    string *temp = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (dynamicArray[i] == String)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        if (size > 1)
        {
            temp = new string[size - 1];
            int j = 0;
            for (int i = 0; i < size; i++)
            {
                if (dynamicArray[i] == String)
                {
                    continue;
                }
                temp[j] = dynamicArray[i];
                j++;
            }
        }
        delete[] dynamicArray;
        dynamicArray = temp;
        size--;
    }
    return found;
}
string *DynamicStringArray::getEntry(const int index)
{
    if (index >= size)
    {
        return nullptr;
    }
    else
    {
        return &dynamicArray[index];
    }
}

// A copy constructor

DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{
    size = obj.getSize();
    dynamicArray = new std::string[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.dynamicArray[i];
    }
}

// new constructor

DynamicStringArray::DynamicStringArray(const vector<string> &vec) : DynamicStringArray()
{
    for (auto i : vec)
    {
    DynamicStringArray:
        addEntry(i);
    }
}

// Overload

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
// move ctor
DynamicStringArray::DynamicStringArray(DynamicStringArray &&obj) : size{obj.size}, dynamicArray{obj.dynamicArray}
{
    obj.size = 0;
    obj.dynamicArray = nullptr;
}
// move operator
DynamicStringArray &DynamicStringArray::operator=(DynamicStringArray &&obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        dynamicArray = obj.dynamicArray;
        size = obj.size;
        obj.dynamicArray = nullptr;
        obj.size = 0;
    }
    return *this;
}

// destructor
DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}
