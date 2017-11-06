#ifndef PHILIPSWAVEMODEL_HPP
#define PHILIPSWAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include <complex>
#include "Dvector.h"
#include "WaveModel.h"
#include "GenericVector.h"
#include "fft.h"

class PhilipsWaveModel :
    public WaveModel
{
    public:
        ~PhilipsWaveModel();
        PhilipsWaveModel(Dvector wind_dir, double intensity); 

        Dvector operator () (double t) const;
		Dvector operator () (double t);
        double operator () (double x, double y, double t) const;
        double operator () (double x, double y, double t);
        double compute_ph(double kx, double ky);
        double compute_ph(double kx, double ky) const;

    private:
        double A;
        int N, M;
        std::complex<double> ksi;
        std::complex<double> i_comp;
};

#endif
