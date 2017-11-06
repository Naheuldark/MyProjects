#include "Dvector.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>


Dvector::Dvector()
{
	val = NULL;
}

Dvector::Dvector(int n)
{
    val = new double[n];
    taille = n;
}

Dvector::Dvector(int n, double init)
{
    val = new double[n];
    taille = n;
    for (int i = 0; i < n; ++i)
    {
    	val[i] = init;
    }
}

Dvector::Dvector(Dvector const& vec)
{
	taille = vec.size();
	if (taille == 0) return;
	val = new double[taille];
	for (int i = 0; i < taille; ++i)
	{
		val[i] = vec.getVal()[i];
	}
}

int getNbrLine(std::string filename);

Dvector::Dvector(std::string& filename)
{
	taille = getNbrLine(filename);

	std::ifstream fichier(filename.c_str());
	if (fichier)
	{
		val = new double[taille];
		int i = 0;
		std::string ligne;
		while(getline(fichier, ligne))
		{
			val[i] = std::atof(ligne.c_str());
			i++;
		}
	}
	else
	{
		Dvector(0);
		std::cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
	}
	fichier.close();
}

Dvector::~Dvector()
{
    delete(val);
}

//###############

void Dvector::display(std::ostream& str)
{
    for (int i = 0; i < taille; i++)
    {
        str << std::setprecision(2) << val[i] << '\n';
    }
}

double* Dvector::getVal() const
{
	return val;
}

int Dvector::size() const
{
	return taille;
}

void Dvector::fillRandomly()
{
	for (int i = 0; i < taille; ++i)
	{
		val[i] = rand()/(double)RAND_MAX;
	}
}

int getNbrLine(std::string filename)
{
	int n = 0;
	std::ifstream fichier(filename.c_str());
	if (fichier) {
		std::string ligne;
		while(getline(fichier, ligne))
			n++;
	} else {
		std::cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
	}
	fichier.close();
	return n;
}
