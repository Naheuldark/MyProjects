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
    printf("## v1\n");
    v1.display(std::cout);
    printf("## v2\n");
    v2.display(std::cout);
    printf("## v3\n");
    v3.display(std::cout);

    Dvector v4(v3);
    v4.fillRandomly();
    printf("## v4\n");
    v4.display(std::cout);
    printf("taille de v4 : %i\n", v4.size());

    std::string file = "../test/tp1_test1.txt";
    Dvector v5(file);
    printf("## v5\n");
    v5.display(std::cout);
    printf("taille de v5 : %i\n", v5.size());
    file = "../test/tp1_test2.txt";
    Dvector v6(file);
    printf("## v6\n");
    //v6.display(std::cout);
    printf("taille de v6 : %i\n", v6.size());
}