#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <complex>

#include "Ocean.h"
#include "Dvector.h"
#include "GenericVector.h"
#include "WaveModel.h"
#include "PhilipsWaveModel.h"


int main(int argc, char** argv)
{
    // Initialisation des paramètres
    fprintf(stderr, "## Initialisation des paramètres\n");
    double Lx = 10.0;
    double Ly = 10.0;
    int nx = 256;
    int ny = 256;

    double t = 0.0f;
    double T = 5.0f;
    double dt = 0.1f;

    Dvector wind_dir(2);
    fill(wind_dir, 1);
    double intensity = 50.0f;

    // Initialisation du modèle de houle
    fprintf(stderr, "## Initialisation du modèle de houle\n");
    PhilipsWaveModel philips(wind_dir, intensity);

    // Initialisation de l'Océan
    fprintf(stderr, "## Initialisation de l'océan\n");
    Ocean ocean(Lx, Ly, nx, ny, t, &philips);

    // Initialisation du champ de hauteur
    fprintf(stderr, "## Initialisation du champ de hauteur\n");
    ocean.generateHeight(3.0);

    // Boucle
    fprintf(stderr, "## Boucle\n");
    int i = 0;
    
    for (t = 0.0f; t < T; t += dt) {
        ocean.setT(t);
        ocean.computeP();

        std::ostringstream strs;
        strs << "../philips/philips" << i << ".txt";
        std::string str = strs.str();

        std::ofstream fichier(str.c_str());

        if(fichier) {
            fichier << ocean.getH();
            fichier.close();
        } else
            std::cerr << "!! Erreur à l'ouverture" << std::endl;

        i++;
    }


    return 0;
}
