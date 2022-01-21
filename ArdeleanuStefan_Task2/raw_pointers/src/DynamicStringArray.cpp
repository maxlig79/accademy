#include <DynamicStringArray.hpp>

DynamicStringArray::DynamicStringArray() : m_size{0}, dynamicArray{nullptr}
{
}

DynamicStringArray::DynamicStringArray(const std::vector<std::string> &inputs) : DynamicStringArray()
{
    for (auto input : inputs)
        DynamicStringArray::addEntry(input);
}

DynamicStringArray::DynamicStringArray(DynamicStringArray &&obj) : m_size{obj.m_size}, dynamicArray{obj.dynamicArray}
{
    obj.m_size = 0;
    obj.dynamicArray = nullptr;
}

size_t DynamicStringArray::get_size() const
{
    return m_size;
}

void DynamicStringArray::addEntry(const std::string &input)
{
    std::string *temp = new std::string[m_size + 1];
    for (size_t i = 0; i < m_size; ++i)
        temp[i] = dynamicArray[i];
    temp[m_size] = input;
    ++m_size;
    delete[] dynamicArray;
    dynamicArray = temp;
}

bool DynamicStringArray::deleteEntry(const std::string &input)
{
    bool ok = false;
    std::string *temp = nullptr;
    for (size_t i = 0; i < m_size; i++)
    {
        if (dynamicArray[i] == input)
        {
            ok = true;
            break;
        }
    }

    if (ok)
    {
        if (m_size > 1)
        {
            temp = new std::string[m_size - 1];
            int index = 0;
            for (size_t i = 0; i < m_size; i++)
            {
                if (dynamicArray[i] == input)
                {
                    continue;
                }
                temp[index] = dynamicArray[i];
                index++;
            }
        }
        delete[] dynamicArray;
        dynamicArray = temp;
        --m_size;
    }
    return ok;
}

std::string *DynamicStringArray::getEntry(const int &index) const
{
    if (index < 0 || index >= m_size)
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

    m_size = obj.m_size;
    for (size_t i = 0; i < m_size; ++i)
        dynamicArray[i] = obj.dynamicArray[i];
}

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{

    if (this != &obj)
    {
        delete[] dynamicArray;
        dynamicArray = new std::string[obj.get_size()];

        m_size = obj.m_size;
        for (size_t i = 0; i < m_size; ++i)
            dynamicArray[i] = obj.dynamicArray[i];
    }
    return *this;
}

DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}