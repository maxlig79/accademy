#include <iostream>
#include <string>

using std::string;
class DynamicStringArray
{
private:
    int size;
    string *dynamicArray;

public:
    DynamicStringArray();
    int get_Size() const;
    void addEntry(const string &String);
    bool deleteEntry(const string &String);
    string getEntry(const int index) const;
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray& operator=(const DynamicStringArray &obj); 
    ~DynamicStringArray();
};