#include <string>
#include <vector>

using std::string;
using std::vector;

template<typename T> 
class DynamicArray
{
private:
    T *dynamicArray;
    int size;

public:
    DynamicArray();
    int getSize() const;
    void addEntry(const T &newInput);
    bool deleteEntry(const string &newInput);
    string getEntry(const int index) const;
    DynamicArray(const DynamicArray &obj);
    DynamicArray& operator=(const DynamicArray &obj); 
    ~DynamicArray();
    DynamicArray(DynamicArray &&other);
    DynamicArray& operator=(DynamicArray &&other);
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
bool DynamicArray<T>::deleteEntry(const string &newInput)
{
    bool found = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (newInput == dynamicArray[i])
        {
            found = true;
            break;
        }
    }
    if (found == true)
    {
        std::string *temp = dynamicArray;
        dynamicArray = new std::string[size - 1];
        for (int j; j < size; j++)
        {
            if (j < i)
            {
                dynamicArray[j] = temp[j];
            }
            else if (j > i)
            {
                dynamicArray[j - 1] = temp[j];
            }
        }
        size--;
    }

    return found;
}
template <class T>
string DynamicArray<T>::getEntry(const int index) const
{
    if (index >= size)
    {
        return "";
    }
    else
    {
        return dynamicArray[index];
    }
}
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray &obj)
{
    size = obj.getSize();
    dynamicArray = new string[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.getEntry(i);
    }
}
template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] dynamicArray;
}
template <class T>
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
template <class T>
DynamicArray<T>::DynamicArray(DynamicArray &&other) : size(other.size), dynamicArray(other.dynamicArray)
{
    other.dynamicArray = nullptr;
    other.size = 0;
}
template <class T>
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
template <class T>
DynamicArray<T>::DynamicArray(const vector<string> &obj) : DynamicArray()
{
    for (auto i : obj)
    {
        DynamicArray::addEntry(i);
    }
}