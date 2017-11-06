#include "Dvector.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

#include <math.h>


Dvector::Dvector()
{
	val = NULL;
	taille = 0;
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
		val[i] = vec(i);
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
    delete [] val;
}

//###############

double& Dvector::operator () (int i) const {
    assert(i >= 0);
    assert(i < taille);
    return val[i];
}

double& Dvector::operator () (int i) {
    assert(i >= 0);
    assert(i < taille);
    return val[i];
}

Dvector& Dvector::operator += (const Dvector &Q) {
	assert(taille == Q.size());
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) += Q(i);
	return P;
}

Dvector& Dvector::operator -= (const Dvector &Q) {
	assert(taille == Q.size());
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) -= Q(i);
	return P;
}

Dvector& Dvector::operator *= (const Dvector &Q) {
	assert(taille == Q.size());
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) *= Q(i);
	return P;
}

Dvector& Dvector::operator /= (const Dvector &Q) {
	assert(taille == Q.size());
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i) {
		assert(Q(i) != 0);
		P(i) /= Q(i);
	}
	return P;
}

Dvector& Dvector::operator += (const double &k) {
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) += k;
	return P;
}

Dvector& Dvector::operator -= (const double &k) {
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) -= k;
	return P;
}

Dvector& Dvector::operator *= (const double &k) {
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) *= k;
	return P;
}

Dvector& Dvector::operator /= (const double &k) {
	assert(k != 0);
	Dvector &P = *this;
	for (int i = 0; i < taille; ++i)
		P(i) /= k;
	return P;
}

bool Dvector::operator == (const Dvector &Q) {
	if (taille != Q.size()) {
		return false;
	} else {
		for (int i = 0; i < taille; ++i)
			if (val[i] != Q(i))
				return false;
	}
	return true;

}

bool Dvector::operator != (const Dvector &Q) {
	return !(*this == Q);
}

Dvector& Dvector::operator = (const Dvector &P) {
	if (taille != 0)
		delete [] val;
	taille = P.size();
	val = new double[taille];
	std::memcpy(val, P.getVal(), taille * sizeof(double));
	return *this;
}

void Dvector::resize(int newSize, double* newVal) {
	if (newSize <= taille)
		return;

	assert(sizeof(newVal)/sizeof(double) == newSize - taille);

	double* v = new double[newSize];
	std::memcpy(v, val, taille * sizeof(double));
	delete [] val;
	for (int i = taille; i < newSize; ++i)
		v[i] = newVal[i-taille];
	val = v;
	taille = newSize;
}



Dvector operator + (const Dvector &P, const double &k) {
	Dvector R(P);
	for (int i = 0; i < P.size(); ++i) 
		R(i) += k;
	return R;
}

Dvector operator - (const Dvector &P, const double &k) {
	Dvector R(P);
	for (int i = 0; i < P.size(); ++i) 
		R(i) -= k;
	return R;
}

Dvector operator * (const Dvector &P, const double &k) {
	Dvector R(P);
	for (int i = 0; i < P.size(); ++i) 
		R(i) *= k;
	return R;
}

Dvector operator / (const Dvector &P, const double &k) {
	assert(k != 0);
	Dvector R(P);
	for (int i = 0; i < P.size(); ++i) 
		R(i) /= k;
	return R;
}

Dvector operator + (const Dvector &P, const Dvector &Q) {
	Dvector R(P);
	R += Q;
	return R;
}

Dvector operator - (const Dvector &P, const Dvector &Q) {
	Dvector R(P);
	R -= Q;
	return R;
}

Dvector operator - (const Dvector &P) {
	Dvector R(P);
	for (int i = 0; i < P.size(); ++i) 
		R(i) *= (-1.0);
	return R;
}

std::ostream& operator << (std::ostream &out, const Dvector &P) {
	out << "Dvector : ";
	for (int i = 0; i < P.size(); ++i)
		out << P(i) << " ";
	out << std::endl;
	return out;
}

std::istream& operator >> (std::istream &in, const Dvector &P) {
	for (int i = 0; i < P.size(); ++i)
		in >> P(i);
	return in;
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

Dvector& fill(Dvector& vec, double v) {
	for (int i = 0; i < vec.size(); ++i) {
		vec.getVal()[i] = v;
	}
	return vec;
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


double norm(const Dvector &P) {
	double res = 0;
	for (int i = 0; i < P.size(); ++i) {
		res += pow(P(i),2);
	}
	return sqrt(res);
}

double dot(const Dvector &P, const Dvector &Q) {
	assert(P.size() == Q.size());
	double res = 0;
	for (int i = 0; i < P.size(); ++i) {
		res += P(i) * Q(i);
	}
	return res;
}

