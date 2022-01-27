#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
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
    DynamicStringArray &operator=(const DynamicStringArray &obj);
    DynamicStringArray(const vector<string> &obj);
    DynamicStringArray(DynamicStringArray &&obj);
    DynamicStringArray &operator=(DynamicStringArray &&obj);
    ~DynamicStringArray();
};