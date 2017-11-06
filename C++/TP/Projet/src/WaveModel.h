#ifndef WAVEMODEL_HPP
#define WAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include "Dvector.h"

class WaveModel
{
    public:
        ~WaveModel();
        WaveModel(Dvector wind_dir, double wave_align, 
                  double intensity, double lambda, 
                  double height_adjust);
        WaveModel(WaveModel const& WM);

        virtual double& operator () (double x, double y, double t) const;
        virtual double& operator () (double x, double y, double t);

    protected:
        Dvector getWindDir() const;
        double getWaveAlign() const;
        double getIntensity() const;
        double getLambda() const;
        double getHeightAdjust() const;

    private:
        Dvector wind_dir;
		double wave_align, intensity, lambda, height_adjust;
};

#endif
