//#include <DynamicArray.hpp>
#include <algorithm>
#include <stdexcept>
#include <cmath>

template<>
void DynamicArray<std::string>::addEntry(const std::string &entry)
{
    if(entry == "")
    {
        throw std::invalid_argument("DynamicArray<std::string> cannot add empty string");
    }
    reallocate();
    m_dynamicArray[m_size - 1] = entry;
}

template<>
void DynamicArray<char>::addEntry(const char &entry)
{
    if(entry == '\0')
    {
        throw std::invalid_argument("DynamicArray<std::string> cannot add empty string");
    }
    reallocate();
    m_dynamicArray[m_size - 1] = entry;
}