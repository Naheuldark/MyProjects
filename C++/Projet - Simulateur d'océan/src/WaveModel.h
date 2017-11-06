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

        virtual Dvector operator () (double t) const;
        virtual Dvector operator () (double t);
        virtual double operator () (double x, double y, double t) const=0;
        virtual double operator () (double x, double y, double t)=0;

    protected:
        Dvector getWindDir() const;
        double getWaveAlign() const;
        double getIntensity() const;
        double getLambda() const;
        double getHeightAdjust() const;

    protected:
        Dvector wind_dir;
		double wave_align, intensity, lambda, height_adjust;
};

#endif
