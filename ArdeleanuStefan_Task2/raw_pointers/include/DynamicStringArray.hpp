#pragma once

#include <cstring>
#include <iostream>
#include <string>

class DynamicStringArray
{
private:
    std::string *dynamicArray;
    size_t size;

public:
    DynamicStringArray();
    size_t get_size() const;
    void addEntry(const std::string &);
    bool deleteEntry(const std::string &);
    std::string *getEntry(const int &) const;
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj);
    ~DynamicStringArray();
};

