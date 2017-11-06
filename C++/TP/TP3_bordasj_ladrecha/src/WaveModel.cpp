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
					 double height_adjust,
					 int nx, int ny,
					 double Lx, double Ly) :
	wind_dir(wind_dir), wave_align(wave_align), 
	intensity(intensity), lambda(lambda), 
	height_adjust(height_adjust),
	nx(nx), ny(ny), Lx(Lx), Ly(Ly),
	heights(Height(Lx, Ly, nx, ny))
{
	assert(wind_dir.size() > 0 && wave_align >= 0 && intensity >= 0 && lambda >= 0 && height_adjust >= 0);
}


WaveModel::~WaveModel() {
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
Height WaveModel::getHeights() const {
	return heights;
}




double& WaveModel::operator () (Dvector x, double t) const {
}

double& WaveModel::operator () (Dvector x, double t) {
}




WaveModel& WaveModel::operator = (const WaveModel &WM) {
	wind_dir = WM.getWindDir();
	wave_align = WM.getWaveAlign();
	intensity = WM.getIntensity();
	lambda = WM.getLambda();
	height_adjust = WM.getHeightAdjust();
	return *this;
}