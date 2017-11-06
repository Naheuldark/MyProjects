#ifndef HEIGHT_HPP
#define HEIGHT_HPP

#include <iostream>
#include <assert.h>
#include "Dvector.h"

class Height
{
    public:
        ~Height();
        Height(double Lx, double Ly, int nx, int ny);
        Height(Height const& height);

        double getLx() const;
        double getLy() const;
        int getNx() const;
        int getNy() const;
        Dvector getVec() const;

        void setLx(double Lx);
        void setLy(double Ly);
        void setNx(int nx);
        void setNy(int ny);

        double& operator () (int offset) const;
        double& operator () (int offset);

        Height& operator = (const Height &H);

    private:
		int nx, ny;
        double Lx, Ly;
        Dvector vec;
};

std::ostream& operator << (std::ostream &out, const Height &H);

#endif
