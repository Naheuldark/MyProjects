#ifndef DVECTOR_HPP
#define DVECTOR_HPP

#include <iostream>

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
        void display(std::ostream& str);
        int size() const;
        void fillRandomly();

    private:
		double* val;
		int taille;	
};

#endif
