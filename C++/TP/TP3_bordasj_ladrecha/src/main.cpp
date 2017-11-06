#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "Dvector.h"
#include "Height.h"


int main()
{
    Height H2(1,2,3,4);
    for (int i = 0; i < H2.getVec().size(); ++i)
        H2(i) = i;
    // H2.getVec().display(std::cout);
    // fprintf(stderr, "\n");

    Height H3(H2);

    std::cout << H2;
    //std::cout << H3 << std::endl;
}