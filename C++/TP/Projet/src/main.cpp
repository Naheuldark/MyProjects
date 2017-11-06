#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <complex>

#include "Ocean.h"
#include "Dvector.h"
#include "WaveModel.h"
#include "GerstnerWaveModel.h"


int main()
{
    // Initialisation des paramètres
    fprintf(stderr, "## Initialisation des paramètres\n");
    double Lx = 10.0;
    double Ly = 10.0;
    int nx = 128;
    int ny = 128;

    double t = 0.0f;
    double T = 10.0f;
    double dt = 0.1f;

    Dvector wind_dir(2);
    fill(wind_dir, 1.0);
    double intensity = 2.0f;

    // Initialisation du modèle de houle
    fprintf(stderr, "## Initialisation du modèle de houle\n");
    GerstnerWaveModel gerstner(wind_dir, intensity);

    // Initialisation de l'Océan
    fprintf(stderr, "## Initialisation de l'océan\n");
    Ocean ocean(Lx, Ly, nx, ny, t, gerstner);

    // Initialisation du champ de hauteur
    fprintf(stderr, "## Initialisation du champ de hauteur\n");
    ocean.generateHeight(3.0);

    // Boucle
    ocean.compute();
    std::cout << ocean.getH() << std::endl;

    ocean.setT(5);
    // ocean.compute();
    // std::cout << H << std::endl;
}
