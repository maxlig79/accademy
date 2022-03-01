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
    DynamicArray() : m_size{0}, dynamicArray{nullptr}
    {
    }

    DynamicArray(const std::vector<T> &inputs) : DynamicArray()
    {
        for (auto input : inputs)
            addEntry(input);
    }

    DynamicArray(DynamicArray<T> &&obj) : m_size{obj.m_size}, dynamicArray{obj.dynamicArray}
    {
        obj.m_size = 0;
        obj.dynamicArray = nullptr;
    }

    DynamicArray<T> &operator=(DynamicArray<T> &&obj)
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

    size_t get_size() const
    {
        return m_size;
    }

    void addEntry(const T &input)
    {
        T *temp = new T[m_size + 1];
        for (size_t i = 0; i < m_size; ++i)
            temp[i] = dynamicArray[i];
        temp[m_size] = input;
        ++m_size;
        delete[] dynamicArray;
        dynamicArray = temp;
    }

    bool deleteEntry(const T &input)
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

    T *getEntry(const int &index) const
    {

        try
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
        catch (const std::out_of_range &e)
        {
            std::cout << e.what() << std::endl;
            return nullptr;
        }
    }

    DynamicArray(const DynamicArray<T> &obj)
    {

        dynamicArray = new T[obj.get_size()];

        m_size = obj.m_size;
        for (size_t i = 0; i < m_size; ++i)
            dynamicArray[i] = obj.dynamicArray[i];
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &obj)
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

    ~DynamicArray()
    {
        delete[] dynamicArray;
    }
};

template <>
void DynamicArray<std::string>::addEntry(const std::string &input)
{
    try
    {
        if (input == "")
            throw std::invalid_argument("INPUT CANNOT BE EMPTY STRING");
        std::string *temp = new std::string[m_size + 1];
        for (size_t i = 0; i < m_size; ++i)
            temp[i] = dynamicArray[i];
        temp[m_size] = input;
        ++m_size;
        delete[] dynamicArray;
        dynamicArray = temp;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }
}