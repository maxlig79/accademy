#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class DynamicStringArray
{
private:
    std::string *dynamicArray;
    size_t m_size;

public:
    DynamicStringArray();
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray(const std::vector<std::string> &inputs);
    DynamicStringArray(DynamicStringArray &&obj);
    DynamicStringArray &operator=(DynamicStringArray &&obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj);
    size_t get_size() const;
    void addEntry(const std::string &);
    bool deleteEntry(const std::string &);
    std::string *getEntry(const int &) const;
    ~DynamicStringArray();
};
