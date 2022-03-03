#include "DynamicArray.hpp"

int main()
{
    DynamicArray < int >  obj;
    obj.addEntry ( 1 );
    obj.addEntry ( 2 );
    obj.addEntry ( 3 );
    obj.deleteEntry ( 2 );
    
    if ( obj.getLength() == 2 )
    {
        std::cout << "Deletion succeded";
    }
    else 
    {
        std::cout << "Deletion failed" ;
    }
}