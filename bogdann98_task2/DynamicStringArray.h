#pragma once

#include<iostream>
#include<string>


using std::string;
class DynamicStringArray{
    private:
    string *dynamicArray;
    int size;

    public:
    DynamicStringArray();
    int getSize() const;
    void addEntry(const string &String);
    bool deleteEntry(const string &String);
    string getEntry(const int index) const;
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj); 
    ~DynamicStringArray();
};
