#include <string>
#include <vector>

class DynamicStringArray
{
private:
    std::string *dynamicArray;
    int size;

public:
    DynamicStringArray();
    int getSize() const;
    void addEntry(const std::string &newString);
    bool deleteEntry(const std::string &newString);
    std::string *getEntry ( const int index );
    DynamicStringArray(const DynamicStringArray &obj);
    DynamicStringArray& operator=(const DynamicStringArray &obj); 
    ~DynamicStringArray();
    DynamicStringArray(DynamicStringArray &&other);
    DynamicStringArray& operator=(DynamicStringArray &&other);
    DynamicStringArray(const std::vector<std::string> &obj);
};