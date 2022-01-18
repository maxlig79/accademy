#include <DynamicStringArray.hpp>

DynamicStringArray::DynamicStringArray()
{
    dynamicArray = nullptr;
    size = 0;
}

size_t DynamicStringArray::get_size() const
{
    return size;
}

void DynamicStringArray::addEntry(const std::string &input)
{

    if (size == 0)
    {
        dynamicArray = new std::string[size + 1];
        dynamicArray[size] = input;
        ++size;
    }
    else
    {
        std::string *temp = new std::string[size + 1];
        for (size_t i = 0; i < size; ++i)
            temp[i] = dynamicArray[i];
        temp[size] = input;
        ++size;
        delete[] dynamicArray;
        dynamicArray = nullptr;
        dynamicArray = temp;
    }
}

bool DynamicStringArray::deleteEntry(const std::string &input)
{
    bool ok = false;
    for (size_t i = 0; i < size; i++)
    {
        if (dynamicArray[i] == input)
        {
            ok = true;
        }
    }

    if (!ok)
        return ok;
    else
    {
        std::string *temp = new std::string[size - 1];
        int index = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (dynamicArray[i] == input)
            {
                continue;
            }
            temp[index] = dynamicArray[i];
            index++;
        }
        delete[] dynamicArray;
        dynamicArray = nullptr;
        dynamicArray = temp;
        --size;
        return true;
    }
}

std::string *DynamicStringArray::getEntry(const int &index) const
{
    if (index < 0 || index >= size)
    {
        return nullptr;
    }
    else
    {
        return &dynamicArray[index];
    }
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{

    dynamicArray = new std::string[obj.get_size()];

    size = obj.size;
    for (size_t i = 0; i < size; ++i)
        dynamicArray[i] = obj.dynamicArray[i];
}

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if (this == &obj)
    {
        return *this;
    }
    dynamicArray = new std::string[obj.get_size()];

    size = obj.size;
    for (size_t i = 0; i < size; ++i)
        dynamicArray[i] = obj.dynamicArray[i];
    return *this;
}

DynamicStringArray::~DynamicStringArray()
{
    if (dynamicArray != nullptr)
        delete[] dynamicArray;
    dynamicArray = nullptr;
}