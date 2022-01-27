#include <string>
#include <vector>

using std::string;
using std::vector;

class DynamicStringArray
{
private:
    string *dynamicArray;
    int size;

public:
    DynamicStringArray();
    int getSize() const;
    void addEntry(const string &newString);
    bool deleteEntry(const string &newString);
    string getEntry(const int index) const;
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray& operator=(const DynamicStringArray &obj); 
    ~DynamicStringArray();
    DynamicStringArray(DynamicStringArray &&other);
    DynamicStringArray& operator=(DynamicStringArray &&other);
    DynamicStringArray(const vector<string> &obj);
};