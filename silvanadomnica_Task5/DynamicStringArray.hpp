#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

using std::string;
using std::vector;

template <typename T>
class DynamicArray
{
private:
    T *dynamicArray;
    int size;

public:
    DynamicArray();
    int getSize() const;
    void addEntry(const T &newInput);
    bool deleteEntry(const T &newInput);
    T *getEntry(const int &index) const;
    DynamicArray(const DynamicArray &obj);
    DynamicArray &operator=(const DynamicArray &obj);
    ~DynamicArray();
    DynamicArray(DynamicArray &&other);
    DynamicArray &operator=(DynamicArray &&other);
    DynamicArray(const vector<string> &obj);
};
template <typename T>
DynamicArray<T>::DynamicArray() : size(0), dynamicArray(nullptr)
{
}
template <typename T>
int DynamicArray<T>::getSize() const
{
    return size;
}
template <>
void DynamicArray<std::string>::addEntry(const std::string &newInput)
{
    if (newInput == "")
    {
        throw std::invalid_argument("Cannot add an empty string");
    }

    string *newArray = new string[size + 1];
    for (int i = 0; i < size; i++)
    {
        newArray[i] = dynamicArray[i];
    }
    newArray[size] = newInput;
    delete[] dynamicArray;
    dynamicArray = newArray;
    size++;
}
template <typename T>
void DynamicArray<T>::addEntry(const T &newInput)
{
    T *newArray = new T[size + 1];
    for (int i = 0; i < size; i++)
    {
        newArray[i] = dynamicArray[i];
    }
    newArray[size] = newInput;
    delete[] dynamicArray;
    dynamicArray = newArray;
    size++;
}
template <class T>
bool DynamicArray<T>::deleteEntry(const T &newInput)
{
    bool found = false;
    for (int i = 0; i < size; i++)
    {
        if (newInput == dynamicArray[i])
        {
            found = true;
            break;
        }
    }
    T *temp = nullptr;
    if (found == true)
    {
        temp = new T[size - 1];
        int j = 0;
        for (int i = 0; i < size; i++)
        {
            if (dynamicArray[i] == newInput)
            {
                continue;
            }
            temp[j] = dynamicArray[i];
            j++;
        }
        delete[] dynamicArray;
        dynamicArray = temp;
        size--;
    }

    return found;
}
template <typename T>
T *DynamicArray<T>::getEntry(const int &index) const
{
    if (index >= size || index < 0)
    {
        throw std::out_of_range("The index is out of bound");
    }
    else
    {
        return &dynamicArray[index];
    }
}
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &obj)
{
    size = obj.getSize();
    dynamicArray = new T[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.dynamicArray[i];
    }
}
template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] dynamicArray;
}
template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &obj)
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
template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray &&other) : size(other.size), dynamicArray(other.dynamicArray)
{
    other.dynamicArray = nullptr;
    other.size = 0;
}
template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray &&other)
{
    if (this != &other)
    {
        delete[] dynamicArray;
        dynamicArray = other.dynamicArray;
        size = other.size;
        other.dynamicArray = nullptr;
        other.size = 0;
    }
    return *this;
}
template <typename T>
DynamicArray<T>::DynamicArray(const vector<string> &obj) : DynamicArray()
{
    for (auto i : obj)
    {
        DynamicArray::addEntry(i);
    }
}