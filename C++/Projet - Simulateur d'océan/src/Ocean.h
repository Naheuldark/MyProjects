#ifndef OCEAN_HPP
#define OCEAN_HPP

#include <iostream>
#include <assert.h>
#include "Height.h"
#include "GenericVector.h"
#include "PhilipsWaveModel.h"
#include "WaveModel.h"


class Ocean
{
    public:
        ~Ocean();
        Ocean(double Lx, double Ly,
              int nx, int ny,
              double t,
              WaveModel* model);

        void setT(double nt);

        Height getH() const {
            return H;
        }

        void setHVec(Dvector vec) {
            H.setVec(vec);
        }

        void generateHeight(double h_init);
        void compute();
        void computeP();

    private:
        double Lx, Ly;
        int nx, ny;
        double t;
        Height H;
        WaveModel* model;
        GenericVector<double> vertices;
        
};

#endif
