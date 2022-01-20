#include <iostream>
#include "DynamicStringArray.hpp"

int main()
{
DynamicStringArray obj;
      obj.addEntry("Ana");
      obj.addEntry("are");
      obj.addEntry("mere");
      if(obj.deleteEntry("mere")!=true && obj.getLength()!=2 )
      std::cout<<"deletion failed";
      else{
        std::cout<<"deletion succeded"<<std::endl<< obj.getLength();
      }
}
