
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using std::string;
using std::vector;
template <typename T>
class DynamicStringArray
{
private:
    T *dynamicArray;
    int size;

public:
    DynamicStringArray();
    int getSize() const;
    void addEntry(const T &input);
    bool deleteEntry(const T &String);
    T *getEntry(const int index);
    DynamicStringArray(const vector<T> &vec);
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray(DynamicStringArray &&obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj);
    DynamicStringArray &operator=(DynamicStringArray &&obj);
    ~DynamicStringArray();
};

// default constructor that sets the dynamic array to nullptr and sets size to 0
template <typename T>
DynamicStringArray<T>::DynamicStringArray() : size{0}, dynamicArray{nullptr}
{
}

// a function that return size
template <typename T>
int DynamicStringArray<T>::getSize() const
{
    return size;
}

// function creates a new dynamic array one element larger than dynamicArray and copy all element into the new array

template <typename T>
void DynamicStringArray<T>::addEntry(const T &input)
{

    T *newdynamicArray = new T[size + 1];
    for (int i = 0; i < size; i++)
    {
        newdynamicArray[i] = dynamicArray[i];
    }
    newdynamicArray[size] = input;
    delete[] dynamicArray;
    dynamicArray = newdynamicArray;
    size++;
}

template <>
void DynamicStringArray<string>::addEntry(const string &input)
{
    try
    {
        if (input == "")
        {
            throw std::invalid_argument("This is an empty string");
        }

        string *newdynamicArray = new string[size + 1];
        for (int i = 0; i < size; i++)
        {
            newdynamicArray[i] = dynamicArray[i];
        }
        newdynamicArray[size] = input;
        delete[] dynamicArray;
        dynamicArray = newdynamicArray;
        size++;
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << "\n";
    }
}

// the function boolean should search dynamicArray for the string
template <typename T>
bool DynamicStringArray<T>::deleteEntry(const T &String)
{
    bool found = false;
    T *temp = nullptr;
    for (int i = 0; i < size; i++)
    {
        if (dynamicArray[i] == String)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        if (size > 1)
        {
            temp = new T[size - 1];
            int j = 0;
            for (int i = 0; i < size; i++)
            {
                if (dynamicArray[i] == String)
                {
                    continue;
                }
                temp[j] = dynamicArray[i];
                j++;
            }
        }
        delete[] dynamicArray;
        dynamicArray = temp;
        size--;
    }
    return found;
}
template <typename T>
T *DynamicStringArray<T>::getEntry(const int index)
{
    try
    {
        if (index < 0 || index >= size)
        {

            throw std::out_of_range("The index is out of bound");
        }
        else
        {
            return &dynamicArray[index];
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
}

// A copy constructor
template <typename T>
DynamicStringArray<T>::DynamicStringArray(const DynamicStringArray &obj)
{
    size = obj.getSize();
    dynamicArray = new T[size];
    for (int i = 0; i < size; i++)
    {
        dynamicArray[i] = obj.dynamicArray[i];
    }
}

// new constructor
template <typename T>
DynamicStringArray<T>::DynamicStringArray(const vector<T> &vec) : DynamicStringArray()
{
    for (auto i : vec)
    {
    DynamicStringArray:addEntry(i);
    }
}

// Overload
template <typename T>
DynamicStringArray<T> &DynamicStringArray<T>::operator=(const DynamicStringArray &obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        size = obj.size;
        dynamicArray = new T[size];

        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = obj.dynamicArray[i];
        }
    }
    return *this;
}

// move ctor
template <typename T>
DynamicStringArray<T>::DynamicStringArray(DynamicStringArray &&obj) : size{obj.size}, dynamicArray{obj.dynamicArray}
{
    obj.size = 0;
    obj.dynamicArray = nullptr;
}

// move operator
template <typename T>
DynamicStringArray<T> &DynamicStringArray<T>::operator=(DynamicStringArray &&obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        dynamicArray = obj.dynamicArray;
        size = obj.size;
        obj.dynamicArray = nullptr;
        obj.size = 0;
    }
    return *this;
}

// destructor
template <typename T>
DynamicStringArray<T>::~DynamicStringArray()
{
    if (dynamicArray != nullptr)
    {
        delete[] dynamicArray;
        dynamicArray = nullptr;
    }
}
