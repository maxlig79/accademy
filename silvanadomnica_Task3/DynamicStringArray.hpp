#include <string>
#include <vector>

using std::vector;
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
    std::string *getEntry ( const int index );
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray& operator=(const DynamicStringArray &obj); 
    ~DynamicStringArray();
    DynamicStringArray(DynamicStringArray &&other);
    DynamicStringArray& operator=(DynamicStringArray &&other);
    DynamicStringArray(const vector<string> &obj);
};