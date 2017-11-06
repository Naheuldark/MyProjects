#ifndef OCEAN_HPP
#define OCEAN_HPP

#include <iostream>
#include <assert.h>
#include "Height.h"
#include "GenericVector.h"
#include "WaveModel.h"

class Ocean
{
    public:
        ~Ocean();
        Ocean(double Lx, double Ly,
              int nx, int ny,
              double t,
              WaveModel model);

        void setT(double nt);
        Height getH() const {
            return H;
        }

        void generateHeight(double h_init);
        void compute();
        void gl_vertices();

    private:
        double Lx, Ly;
        int nx, ny;
        double t;
        Height H;
        WaveModel model;
        GenericVector<double> vertices;
        
};

#endif
