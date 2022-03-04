#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class DynamicArray
{
private:
    T *dynamicArray;
    size_t m_size;

public:
    DynamicArray();
    DynamicArray(const std::vector<T> &inputs);
    DynamicArray(DynamicArray<T> &&obj);
    DynamicArray<T> &operator=(DynamicArray<T> &&obj);
    size_t get_size() const;
    void addEntry(const T &input);
    bool deleteEntry(const T &input);
    T *getEntry(const int &index) const noexcept(false);
    DynamicArray(const DynamicArray<T> &obj);
    DynamicArray<T> &operator=(const DynamicArray &);
    ~DynamicArray();
};

template <typename T>
DynamicArray<T>::DynamicArray() : m_size{0}, dynamicArray{nullptr}
{
}

template <typename T>
DynamicArray<T>::DynamicArray(const std::vector<T> &inputs) : DynamicArray()
{
    for (auto input : inputs)
        addEntry(input);
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&obj) : m_size{obj.m_size}, dynamicArray{obj.dynamicArray}
{
    obj.m_size = 0;
    obj.dynamicArray = nullptr;
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray<T> &&obj)
{
    if (this != &obj)
    {
        delete[] dynamicArray;

        dynamicArray = obj.dynamicArray;
        m_size = obj.m_size;

        obj.dynamicArray = nullptr;
        obj.m_size = 0;
    }
    return *this;
}

template <typename T>
size_t DynamicArray<T>::get_size() const
{
    return m_size;
}

template <typename T>
void DynamicArray<T>::addEntry(const T &input)
{
    if constexpr (std::is_same<T, std::string>::value)
    {
        if (input == T())
            throw std::invalid_argument("INPUT CANNOT BE EMPTY STRING");
    }
    T *temp = new T[m_size + 1];
    for (size_t i = 0; i < m_size; ++i)
        temp[i] = dynamicArray[i];
    temp[m_size] = input;
    ++m_size;
    delete[] dynamicArray;
    dynamicArray = temp;
}

template <typename T>
bool DynamicArray<T>::deleteEntry(const T &input)
{
    bool existString = false;
    T *temp = nullptr;
    for (size_t i = 0; i < m_size; i++)
    {
        if (dynamicArray[i] == input)
        {
            existString = true;
            break;
        }
    }

    if (existString)
    {
        if (m_size > 1)
        {
            temp = new T[m_size - 1];
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
    return existString;
}

template <typename T>
T *DynamicArray<T>::getEntry(const int &index) const
{

    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("INDEX IS OUT OF RANGE");
    }
    else
    {
        return &dynamicArray[index];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &obj)
{

    dynamicArray = new T[obj.get_size()];

    m_size = obj.m_size;
    for (size_t i = 0; i < m_size; ++i)
        dynamicArray[i] = obj.dynamicArray[i];
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &obj)
{

    if (this != &obj)
    {
        delete[] dynamicArray;
        dynamicArray = new T[obj.get_size()];

        m_size = obj.m_size;
        for (size_t i = 0; i < m_size; ++i)
            dynamicArray[i] = obj.dynamicArray[i];
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] dynamicArray;
}
