#include "GerstnerWave.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

#include <math.h>


GerstnerWave::~GerstnerWave() {
}

GerstnerWave::GerstnerWave(double amplitude, double frequency, 
						   double direction, double phase) :
	amplitude(amplitude), frequency(frequency), phase(phase), direction(direction)
{
}

GerstnerWave::GerstnerWave(GerstnerWave const& GW) :
	amplitude(GW.getAmplitude()), frequency(GW.getFrequency()), 
	phase(GW.getPhase()), direction(GW.getDirection())
{
}


double GerstnerWave::getAmplitude() const {
	return amplitude;
}
double GerstnerWave::getFrequency() const {
	return frequency;
}
Dvector GerstnerWave::getDirection() const {
	return direction;
}
double GerstnerWave::getPhase() const {
	return phase;
}


double GerstnerWave::operator () (Dvector x0, double t) const {
	return amplitude * cos(dot(direction, x0) - frequency*t + phase);
}

double GerstnerWave::operator () (Dvector x0, double t) {
	return amplitude * cos(dot(direction, x0) - frequency*t + phase);
}


GerstnerWave& GerstnerWave::operator = (const GerstnerWave &GW) {
}