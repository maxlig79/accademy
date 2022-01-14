#include <iostream>
#include <Maxim.hpp>

int Maxim::calculMaxim(int nr_1, int nr_2, int nr_3)
{
    int max_aux = (nr_1 < nr_2) ? nr_2 : nr_1;
    return ((max_aux < nr_3) ? nr_3 : max_aux);
}
