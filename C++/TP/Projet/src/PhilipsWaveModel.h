#ifndef PHILIPSWAVEMODEL_HPP
#define PHILIPSWAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include "Dvector.h"
#include "fft.h"

class PhilipsWaveModel :
    public WaveModel
{
    public:
        ~PhilipsWaveModel();
        PhilipsWaveModel(Dvector wind_dir, double intensity); 

        double& operator () (double x, double y, double t) const;
		double& operator () (double x, double y, double t);
    
    private:
        GenericVector <Dvector> k;
        Height h;
        int A;
};

#endif
