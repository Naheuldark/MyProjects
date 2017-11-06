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
        GerstnerWave(double amplitude, double frequency, 
                     double direction, double phase);
        GerstnerWave(GerstnerWave const& GW);

    protected:
        double getAmplitude() const;
        double getFrequency() const;
        Dvector getDirection() const;
        double getPhase() const;

        double operator () (Dvector x0, double t) const;
        double operator () (Dvector x0, double t);

        GerstnerWave& operator = (const GerstnerWave &GW);

    private:
		double amplitude, frequency, phase;
        Dvector direction;
};

#endif
