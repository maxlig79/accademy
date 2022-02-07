#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;
using std::vector;
class DynamicStringArray
{
private:
    int size;
    std::string *dynamicArray;

public:
    DynamicStringArray();
    int get_Size() const;
    void addEntry(const std::string &String);
    bool deleteEntry(const std::string &String);
    std::string *getEntry(const int index);
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray &operator=(const DynamicStringArray &obj);
    DynamicStringArray(const vector<std::string> &obj);
    DynamicStringArray(DynamicStringArray &&obj);
    DynamicStringArray &operator=(DynamicStringArray &&obj);
    ~DynamicStringArray();
};
