#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <sstream>

#include "../src/Dvector.h"


int main()
{
    std::stringstream str1;
    Dvector v1;
    assert(&v1 != NULL);
    std::cout << "# OK : v1 n'est pas NULL\n";
    (&v1)->display(str1);
    assert(str1.str() == "");
    std::cout << "# OK : v1 est vide et v1.display() n'a rien affiché\n\n";


    std::stringstream str2;
    Dvector v2(3);
    assert(&v2 != NULL);
    std::cout << "# OK : v2 n'est pas NULL\n";
    assert(v2.size() == 3);
    std::cout << "# OK : v2 est bien de taille 3\n";
    v2.display(str2);
    assert(str2.str() == "0\n0\n0\n");
    std::cout << "# OK : v2.display() a affiché ce qu'il fallait\n\n";
    

    std::stringstream str3;
    Dvector v3(3,1.543);
    assert(&v3 != NULL);
    std::cout << "# OK : v3 n'est pas NULL\n";
    assert(v3.size() == 3);
    std::cout << "# OK : v3 est bien de taille 3\n";
    v3.display(str3);
    assert(str3.str() == "1.5\n1.5\n1.5\n");
    std::cout << "# OK : v3.display() a affiché ce qu'il fallait\n\n";
    
    
    std::stringstream str4;
    Dvector v4(v3);
    assert(&v4 != NULL);
    std::cout << "# OK : v4 n'est pas NULL\n";
    assert(v4.size() == 3);
    std::cout << "# OK : v4 est bien de taille 3 (idem que v3)\n";
    v4.fillRandomly();
    v4.display(str4);
    assert(str4.str() != "1.5\n1.5\n1.5\n");
    std::cout << "# OK : v4.fillRandomly() a bien modifié les valeurs de v4\n";
    std::cout << "# OK : v4.display() a affiché ce qu'il fallait\n\n";


    std::string file;

    file = "../test/tp1_test1.txt";
    Dvector v5(file);
    assert(&v5 != NULL);
    std::cout << "# OK : v5 n'est pas NULL\n";
    assert(v5.size() == 10);
    std::cout << "# OK : v5 est bien de taille 10\n\n";


    file = "../test/tp1_test2.txt";
    Dvector v6(file);
    assert(&v6 != NULL);
    std::cout << "# OK : v6 n'est pas NULL\n";
    assert(v6.size() == 16737);
    std::cout << "# OK : v6 est bien de taille 16737\n\n";
}