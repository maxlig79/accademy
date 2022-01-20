#include <DynamicArray.hpp>
#include <algorithm>
#include <cmath>

DynamicArray::DynamicArray()
{
    m_dynamicArray = nullptr;
    m_size = 0;
}

DynamicArray::DynamicArray(size_t _size)
{
    m_dynamicArray = new std::string[_size];
    m_size = 0;
}

DynamicArray::DynamicArray(const DynamicArray &other)
{
    m_size = other.m_size;
    m_dynamicArray = new std::string[m_size];
    std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
}

DynamicArray::~DynamicArray()
{
    delete[] m_dynamicArray;
}

DynamicArray::DynamicArray(DynamicArray &&source)
{
    m_dynamicArray = std::move(source.m_dynamicArray);
    m_size = std::move(source.m_size);
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other)
{
    if (&other == this)
    {
        return *this;
    }
    delete[] m_dynamicArray;
    m_size = other.m_size;
    m_dynamicArray = new std::string[m_size];
    std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
    return *this;
}

DynamicArray &DynamicArray::operator=(DynamicArray &&source)
{
    delete[] m_dynamicArray;
    m_dynamicArray = std::move(source.m_dynamicArray);
    m_size = std::move(source.m_size);
    return *this;
}

std::string &DynamicArray::operator[](const size_t index)
{
    return m_dynamicArray[index];
}

const std::string &DynamicArray::operator[](const size_t index) const
{
    return m_dynamicArray[index];
}

void DynamicArray::deleteEntry(const std::string &entry)
{
    std::string *out = new std::string[m_size];
    size_t newSize = 0;
    std::copy_if(m_dynamicArray, m_dynamicArray + m_size, out, [&](const std::string el) {return el != entry; newSize += el != entry;});
    m_size = newSize;
    delete[] m_dynamicArray;
    m_dynamicArray = out;
}

std::string DynamicArray::getEntry(const size_t index) const
{
    return m_dynamicArray[index];
}

void DynamicArray::addEntry(const std::string &entry)
{
    reallocate(m_size + 1);
    m_dynamicArray[m_size - 1] = entry;
}

size_t DynamicArray::size() const
{
    return m_size;
}

void DynamicArray::reallocate(size_t newSize)
{
    std::string *newArray = new std::string[newSize];
    std::copy_n(m_dynamicArray, m_size, newArray);
    delete[] m_dynamicArray;
    m_dynamicArray = newArray;
    m_size = newSize;
}