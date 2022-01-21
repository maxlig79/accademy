#include <string>

using std::string;

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
};