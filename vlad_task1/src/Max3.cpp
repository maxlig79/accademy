#include <Max3.hpp>

int Max3::max(int a, int b, int c)
{
    int max = a;
    max = max * (max >= b) + b * (b > max);
    max = max * (max >= c) + c * (c > max);
    return max;
}