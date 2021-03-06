#include <DynamicArray.hpp>
#include <algorithm>
#include <stdexcept>
#include <cmath>

DynamicArray::DynamicArray() : m_dynamicArray(nullptr), m_size(0)
{
}

DynamicArray::DynamicArray(const DynamicArray &other)
{
    m_size = other.m_size;
    m_dynamicArray = new std::string[m_size];
    std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
}

DynamicArray::DynamicArray(const std::vector<std::string> &other)
{
    m_size = other.size();
    m_dynamicArray = new std::string[m_size];
    std::copy_n(other.begin(), m_size, m_dynamicArray);
}

DynamicArray::~DynamicArray()
{
    delete[] m_dynamicArray;
}

DynamicArray::DynamicArray(DynamicArray &&source)
{
    m_dynamicArray = source.m_dynamicArray;
    source.m_dynamicArray = nullptr;
    m_size = std::move(source.m_size);
}

DynamicArray &DynamicArray::operator=(const DynamicArray &other)
{
    
    if (this != &other)
    {
        delete[] m_dynamicArray;
        m_size = other.m_size;
        m_dynamicArray = new std::string[m_size];
        std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
    }
    return *this;
}

DynamicArray &DynamicArray::operator=(DynamicArray &&source)
{
    if (this != &source)
    {
        delete[] m_dynamicArray;
        m_dynamicArray = std::move(source.m_dynamicArray);
        source.m_dynamicArray = nullptr;
        m_size = std::move(source.m_size);
    }
    return *this;
}

bool DynamicArray::deleteEntry(const std::string &entry)
{
    size_t occurences = std::count(m_dynamicArray, m_dynamicArray + m_size, entry);
    if (occurences)
    {
        std::string *out = new std::string[m_size - occurences];
        size_t newSize = m_size - occurences;
        std::copy_if(m_dynamicArray, m_dynamicArray + m_size, out, std::bind(std::not_equal_to(), entry, std::placeholders::_1));
        m_size = newSize;
        delete[] m_dynamicArray;
        m_dynamicArray = out;
    }
    return occurences;
}

std::string DynamicArray::getEntry(const size_t index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("DynamicArray: index out of range");
    }
    return m_dynamicArray[index];
}

void DynamicArray::addEntry(const std::string &entry)
{
    reallocate();
    m_dynamicArray[m_size - 1] = entry;
}

size_t DynamicArray::size() const
{
    return m_size;
}

void DynamicArray::reallocate()
{
    size_t newSize = m_size + 1;
    std::string *newArray = new std::string[newSize];
    std::copy_n(m_dynamicArray, m_size, newArray);
    delete[] m_dynamicArray;
    m_dynamicArray = newArray;
    m_size = newSize;
}