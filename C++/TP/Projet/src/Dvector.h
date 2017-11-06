#ifndef DVECTOR_HPP
#define DVECTOR_HPP

#include <iostream>
#include <assert.h>

class Dvector
{
    public:
        ~Dvector();
        Dvector();
        Dvector(int n);
        Dvector(int n, double init);
        Dvector(Dvector const& vec);
        Dvector(std::string& filename);

        double* getVal() const;
        int size() const;

        void display(std::ostream& str);
        void fillRandomly();

        double& operator () (int i) const;
        double& operator () (int i);
        Dvector& operator += (const Dvector &Q);
        Dvector& operator -= (const Dvector &Q);
        Dvector& operator *= (const Dvector &Q);
        Dvector& operator /= (const Dvector &Q);
        Dvector& operator += (const double &k);
        Dvector& operator -= (const double &k);
        Dvector& operator *= (const double &k);
        Dvector& operator /= (const double &k);
        bool operator == (const Dvector &Q);
        bool operator != (const Dvector &Q);
        Dvector& operator = (const Dvector &P);

        void resize(int newSize, double* newVal);



    private:
		double* val;
		int taille;	
};

Dvector operator + (const Dvector &P, const double &k);
Dvector operator - (const Dvector &P, const double &k);
Dvector operator * (const Dvector &P, const double &k);
Dvector operator / (const Dvector &P, const double &k);
Dvector operator + (const Dvector &P, const Dvector &Q);
Dvector operator - (const Dvector &P, const Dvector &Q);
Dvector operator - (const Dvector &P);

double norm(const Dvector &P);
double dot(const Dvector &P, const Dvector &Q);
Dvector& fill(Dvector& vec, double v);

std::ostream& operator << (std::ostream &s, const Dvector &P);
std::istream& operator >> (std::istream &s, const Dvector &P);

#endif
