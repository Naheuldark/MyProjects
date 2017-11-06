#include "WaveModel.h"
#include "Dvector.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>


WaveModel::WaveModel(WaveModel const& WM) :
	wind_dir(WM.getWindDir()), wave_align(WM.getWaveAlign()), 
	intensity(WM.getIntensity()), lambda(WM.getLambda()), 
	height_adjust(WM.getHeightAdjust())
{
}

WaveModel::WaveModel(Dvector wind_dir, double wave_align, 
					 double intensity, double lambda, 
					 double height_adjust) :
	wind_dir(wind_dir), wave_align(wave_align), 
	intensity(intensity), lambda(lambda), 
	height_adjust(height_adjust)
{
	assert(wind_dir.size() > 0 && wave_align >= 0 && intensity >= 0 && lambda >= 0 && height_adjust >= 0);
}


WaveModel::~WaveModel() {
}

double& WaveModel::operator () (double x, double y, double t) const
{
}

double& WaveModel::operator () (double x, double y, double t)
{
}

Dvector WaveModel::getWindDir() const {
	return wind_dir;
}
double WaveModel::getWaveAlign() const {
	return wave_align;
}
double WaveModel::getIntensity() const {
	return intensity;
}
double WaveModel::getLambda() const {
	return lambda;
}
double WaveModel::getHeightAdjust() const {
	return height_adjust;
}