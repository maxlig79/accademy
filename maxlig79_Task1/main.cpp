#include "ComputeMax.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
  ComputeMax cMax;
  cout << "Maximum is " << cMax.Compute(5,10,3) << endl;
}