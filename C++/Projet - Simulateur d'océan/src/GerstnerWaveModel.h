#ifndef GERSTNERWAVEMODEL_HPP
#define GERSTNERWAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include <vector>
#include "Dvector.h"
#include "WaveModel.h"
#include "GerstnerWave.h"

class GerstnerWaveModel :
    public WaveModel
{
    public:
        ~GerstnerWaveModel();
        GerstnerWaveModel(Dvector wind_dir, double intensity);

        double operator () (double x, double y, double t) const;
		double operator () (double x, double y, double t);

        int getN() {return N;}
        std::vector<Dvector> getKi() {return ki;}
        Dvector getAi() {return Ai;}
        Dvector getWi() {return wi;}
        Dvector getPhii() {return phii;}

    private:
        int N;
        std::vector<Dvector> ki;
    	Dvector Ai, wi, phii;
};

#endif
