#include <iostream>
#include "DynamicStringArray.hpp"

int main()
{
  DynamicArray<string> obj;
  obj.addEntry ( "Hello" );
  obj.addEntry ( "world" );
  if ( obj.deleteEntry ( "world" ) != true && obj.getSize() != 2 )
    std::cout << "Deletion failed" ;
    else {
    std::cout << "Deletion succeded" << std::endl << obj.getSize() ;
    }
}