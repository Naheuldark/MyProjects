#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "Dvector.h"


int main()
{
    Dvector v1;
    Dvector v2(3);
    Dvector v3(3,0);
    int i = v2.size();
    v3.display(std::cout);
    v2.fillRandomly();
    v2.display(std::cout);

    v2(0) = 0.0;
    const Dvector v4(1,6);
    double val = v4(0);

    v2 + 2.0;
    v2 - 2.0;
    v2 * 2.0;
    v2 / 2.0;
    v2 + v3;
    v2 - v3;
    -v2;

    std::cout << v2;
    Dvector v9(0);
    std::cin >> v9;

    v2 += 2.0;
    v2 -= 2.0;
    v2 *= 2.0;
    v2 /= 2.0;
    v2 += v3;
    v2 -= v3;

    v2 = v3;

    bool same = (v2 == v3);
}