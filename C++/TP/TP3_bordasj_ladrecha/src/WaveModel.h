#ifndef WAVEMODEL_HPP
#define WAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include "Height.h"
#include "Dvector.h"

class WaveModel
{
    public:
        ~WaveModel();
        WaveModel(Dvector wind_dir, double wave_align, 
                  double intensity, double lambda, 
                  double height_adjust,
                  int nx, int ny,
                  double Lx, double Ly);
        WaveModel(WaveModel const& WM);

    protected:
        Dvector getWindDir() const;
        double getWaveAlign() const;
        double getIntensity() const;
        double getLambda() const;
        double getHeightAdjust() const;
        Height getHeights() const;

        double& operator () (Dvector x, double t) const;
        double& operator () (Dvector x, double t);

        WaveModel& operator = (const WaveModel &WM);

    private:
        Height heights;
        Dvector wind_dir;
		double wave_align, intensity, lambda, height_adjust;
        int nx, ny;
        double Lx, Ly;
};

#endif
