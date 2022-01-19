#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#include <string>

class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(size_t _size);
    DynamicArray(const DynamicArray &other);
    DynamicArray(DynamicArray &&source);
    DynamicArray &operator=(const DynamicArray &other);
    DynamicArray &operator=(DynamicArray &&source);
    std::string &operator[](const size_t index);
    const std::string&operator[](const size_t index) const;
    ~DynamicArray();
    
public:
    void deleteEntry(const std::string &entry);
    void addEntry(const std::string &entry);
    std::string getEntry(size_t index) const;
    size_t size() const;

private:
    std::string *m_dynamicArray;
    size_t m_size;
    void reallocate(size_t newSize);
};

#endif