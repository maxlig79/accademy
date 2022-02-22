#pragma once

#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::string;
class DynamicStringArray{
    private:
    std::string *dynamicArray;
    int size;

    public:
    DynamicStringArray();
    int getSize() const;
    void addEntry(const string &String);
    bool deleteEntry(const string &String);
    string *getEntry(const int index);  
    DynamicStringArray(const vector<string> &vec);
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray(DynamicStringArray &&obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj); 
    DynamicStringArray &operator=(DynamicStringArray &&obj);
    ~DynamicStringArray();
};
