#ifndef GERSTNERWAVEMODEL_HPP
#define GERSTNERWAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include "Dvector.h"
#include "WaveModel.h"
#include "GerstnerWave.h"

class GerstnerWaveModel :
    public WaveModel
{
    public:
        ~GerstnerWaveModel();
        GerstnerWaveModel(Dvector wind_dir, double intensity); 

        double& operator () (double x, double y, double t) const;
		double& operator () (double x, double y, double t);
    
    private:
        int N;
        Dvector ki[];
    	Dvector Ai, wi, phii;
};

#endif
