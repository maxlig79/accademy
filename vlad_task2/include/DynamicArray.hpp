#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <type_traits>

template <typename T>
class DynamicArray
{
public:
    DynamicArray();

    DynamicArray(const DynamicArray<T> &other);

    DynamicArray(const std::vector<T> &container);

    DynamicArray(DynamicArray<T> &&source);

    DynamicArray<T> &operator=(const DynamicArray<T> &other);

    DynamicArray<T> &operator=(DynamicArray<T> &&source);

    ~DynamicArray();

public:
    bool deleteEntry(const T &entry);

    void addEntry(const T &entry);

    T getEntry(size_t index) const;

    size_t size() const;

private:
    void reallocate();

private:
    T *m_dynamicArray;
    size_t m_size;
};

template <typename T>
DynamicArray<T>::DynamicArray() : m_dynamicArray(nullptr), m_size(0)
{
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
{
    m_size = other.m_size;
    m_dynamicArray = new T[m_size];
    std::copy_n(other.m_dynamicArray, m_size, m_dynamicArray);
}

template <typename T>
DynamicArray<T>::DynamicArray(const std::vector<T> &container)
{
    m_size = container.size();
    m_dynamicArray = new T[m_size];
    std::copy_n(container.begin(), m_size, m_dynamicArray);
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&source)
{
    m_dynamicArray = source.m_dynamicArray;
    source.m_dynamicArray = nullptr;
    m_size = std::move(source.m_size);
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other)
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

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray<T> &&source)
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

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] m_dynamicArray;
}

template <typename T>
bool DynamicArray<T>::deleteEntry(const T &entry)
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

template <typename T>
void DynamicArray<T>::addEntry(const T &entry)
{
    if constexpr (std::is_same<T, std::string>::value || std::is_same<T, char>::value) 
    {
        if (entry == T())
        {
            throw std::invalid_argument("Invalid value");
        }
    }

    reallocate();
    m_dynamicArray[m_size - 1] = entry;
}

template <typename T>
T DynamicArray<T>::getEntry(size_t index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("DynamicArray: index out of range");
    }
    return m_dynamicArray[index];
}

template <typename T>
void DynamicArray<T>::reallocate()
{
    size_t newSize = m_size + 1;
    T *newArray = new T[newSize];
    std::copy_n(m_dynamicArray, m_size, newArray);
    delete[] m_dynamicArray;
    m_dynamicArray = newArray;
    m_size = newSize;
}

template <typename T>
size_t DynamicArray<T>::size() const
{
    return m_size;
}

#endif