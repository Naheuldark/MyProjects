#ifndef GERSTNERWAVE_HPP
#define GERSTNERWAVE_HPP

#include <iostream>
#include <assert.h>
#include "Height.h"
#include "Dvector.h"

class GerstnerWave
{
    public:
        ~GerstnerWave();
        GerstnerWave();
        GerstnerWave(double amplitude, double frequency, 
                     Dvector direction, double phase);
        GerstnerWave(GerstnerWave const& GW);

        GerstnerWave& operator = (const GerstnerWave &GW);

        double operator () (double x, double y, double t) const;
        double operator () (double x, double y, double t);

    protected:
        double getAmplitude() const;
        double getFrequency() const;
        Dvector getDirection() const;
        double getPhase() const;

    private:
		double amplitude, frequency, phase;
        Dvector direction;
};

#endif
