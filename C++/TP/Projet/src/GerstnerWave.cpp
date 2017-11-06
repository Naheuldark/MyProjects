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

GerstnerWave::GerstnerWave() :
	amplitude(0.0f), frequency(0.0f), phase(0.0f), direction(Dvector())
{
}

GerstnerWave::GerstnerWave(double amplitude, double frequency, 
						   Dvector direction, double phase) :
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


double GerstnerWave::operator () (double x, double y, double t) const {
	Dvector x0(2);
	x0(0) = x;
	x0(1) = y;
	double res = amplitude * cos(dot(direction, x0) - frequency*t + phase);
	return res;
}

double GerstnerWave::operator () (double x, double y, double t) {
	Dvector x0(2);
	x0(0) = x;
	x0(1) = y;
	double res = amplitude * cos(dot(direction, x0) - frequency*t + phase);
	return res;
}

GerstnerWave& GerstnerWave::operator = (const GerstnerWave &GW) {
	amplitude = GW.getAmplitude();
	frequency = GW.getFrequency();
	phase = GW.getPhase();
	direction = GW.getDirection();
	return *this;
}