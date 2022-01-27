#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>

using namespace boost::algorithm;

class Max{
public:
  int ComputeMax(int x, int y, int z){
    if( x>=y && x>=z ) { return x; } 
      else if( y>=x && y>=z) { return y; }
        else { return z; }
  }
};

int main()
{
Max nr;
std::cout<<nr.ComputeMax(5,1,3)<<std::endl;
}
