#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <string>
#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
    DynamicArray(): m_dynamicArray(nullptr), m_size(0)
    {
    }

    DynamicArray(const DynamicArray<T> &other)
    {
        m_size = other.m_size;
        m_dynamicArray = new T[m_size];
        std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
    }

    DynamicArray(const std::vector<T> &container)
    {
        m_size = container.size();
        m_dynamicArray = new T[m_size];
        std::copy_n(container.begin(), m_size, m_dynamicArray);
    }

    DynamicArray(DynamicArray<T> &&source)
    {
        m_dynamicArray = source.m_dynamicArray;
        source.m_dynamicArray = nullptr;
        m_size = std::move(source.m_size);
    }

    DynamicArray &operator=(const DynamicArray<T> &other)
    {
        if (this != &other)
        {
            delete[] m_dynamicArray;
            m_size = other.m_size;
            m_dynamicArray = new T[m_size];
            std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
        }
        return *this;
    }

    DynamicArray &operator=(DynamicArray<T> &&source)
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

    ~DynamicArray()
    {
        delete[] m_dynamicArray;
    }

public:
    bool deleteEntry(const T &entry)
    {
        size_t occurences = std::count(m_dynamicArray, m_dynamicArray + m_size, entry);
        if (occurences)
        {
            T *out = new T[m_size - occurences];
            size_t newSize = m_size - occurences;
            std::copy_if(m_dynamicArray, m_dynamicArray + m_size, out, std::bind(std::not_equal_to<T>(), entry, std::placeholders::_1));
            m_size = newSize;
            delete[] m_dynamicArray;
            m_dynamicArray = out;
        }
        return occurences;
    }

    void addEntry(const T &entry)
    {
        reallocate();
        m_dynamicArray[m_size - 1] = entry;
    }

    T getEntry(size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("DynamicArray: index out of range");
        }
        return m_dynamicArray[index];
    }

    size_t size() const
    {
        return m_size;
    }

private:
    void reallocate()
    {
        size_t newSize = m_size + 1;
        T *newArray = new T[newSize];
        std::copy_n(m_dynamicArray, m_size, newArray);
        delete[] m_dynamicArray;
        m_dynamicArray = newArray;
        m_size = newSize;
    }

private:
    T *m_dynamicArray;
    size_t m_size;
};

#include <DynamicArray.inc>

#endif