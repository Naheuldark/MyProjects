#include "PhilipsWaveModel.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

#include <math.h>


//Source loi normale: https://www.developpez.net/forums/
#define RAND ((double) rand())/((double) RAND_MAX)
#define TWOPI 2.0*3.141592653589793238462643383279502884197169399375
#define RANDN sqrt(-2.0*log(RAND))*cos(TWOPI*RAND)
 
 
double normalDistribution(double mu,double sigma)
{
  if(sigma<=0.0)
  {
    fprintf(stderr,"Error in file %s line %u function %s : sigma must be > 0\nExit program\n",__FILE__,__LINE__,__FUNCTION__);
    exit(EXIT_FAILURE);
  }
 
  return (mu+sigma*RANDN);
}

PhilipsWaveModel::~PhilipsWaveModel() {
}

PhilipsWaveModel::PhilipsWaveModel(Dvector wind_dir, double intensity) :
    WaveModel(wind_dir, 0.0f, intensity, 10.0f, 10.0f),
    N(256), M(256), A(15)
{
    double ksi_r = normalDistribution(0,1);
    double ksi_i = normalDistribution(0,1);

    ksi = std::complex <double> (ksi_r, ksi_i);   
    i_comp = std::complex <double>(0,1);
}

Dvector PhilipsWaveModel::operator() (double t) {
    int i = 0;
    GenericVector<std::complex <double> > htilde(N*M);

    for (int n = -N/2 ; n < N/2 ; n++) {
        for (int m = -M/2; m < M/2 ; m++) {
            double kx = 2*M_PI*n/N;
            double ky = 2*M_PI*m/M;

            htilde(i++) = (1/sqrt(2)) * ksi * exp(i_comp * sqrt(9.81*sqrt(kx*kx+ky*ky)) * t) * sqrt(compute_ph(kx, ky))
                        + (1/sqrt(2)) * conj(ksi) * exp(- i_comp * sqrt(9.81*sqrt(kx*kx+ky*ky)) * t) * sqrt(compute_ph(-kx, -ky));

        }
    }

    Dvector height (N*M);
    for (int i = 0; i<N*M; i++) 
        height(i) = real(htilde(i));

    //Dvector height = ifft_vector_double(htilde);
    return height;

}

Dvector PhilipsWaveModel::operator() (double t) const{
    int i = 0;
    GenericVector<std::complex <double> > htilde(N*M);

    for (int n = -N/2 ; n < N/2 ; n++) {
        for (int m = -M/2 ; m < M/2 ; m++) {
            double kx = 2*M_PI*n/N;
            double ky = 2*M_PI*m/M;

            htilde(i++) = (1/sqrt(2)) * ksi * exp(i_comp * sqrt(9.81*sqrt(kx*kx+ky*ky)) * t) * sqrt(compute_ph(kx, ky))
                        + (1/sqrt(2)) * conj(ksi) * exp(- i_comp * sqrt(9.81*sqrt(kx*kx+ky*ky)) * t) * sqrt(compute_ph(-kx, -ky));
            
            
        }
    }

    Dvector height = ifft_vector_double(htilde);
    return height;
}


double PhilipsWaveModel::operator() (double x, double y, double t) const {
    return 0;
}

double PhilipsWaveModel::operator() (double x, double y, double t) {
    return 0;
}

double PhilipsWaveModel::compute_ph(double kx, double ky) {
    double kcarre = kx*kx + ky*ky;
    double L = intensity * intensity / 9.81; 
    double scal = kx*wind_dir(0) + ky * wind_dir(1);
    return A * exp((-1/(kcarre*L*L))/kcarre) * scal * scal;
}

double PhilipsWaveModel::compute_ph(double kx, double ky) const {
    double kcarre = kx*kx + ky*ky;
    double L = intensity * intensity / 9.81; 
    double scal = kx*wind_dir(0) + ky * wind_dir(1);
    return A * exp((-1/(kcarre*L*L))/kcarre) * scal * scal;
}