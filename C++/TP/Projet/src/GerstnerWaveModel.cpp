#include "GerstnerWaveModel.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

#include <math.h>


GerstnerWaveModel::~GerstnerWaveModel() {
}

GerstnerWaveModel::GerstnerWaveModel(Dvector wind_dir, double intensity) :
	WaveModel(wind_dir, 0.0f, intensity, 0.0f, 0.0f), N(10)
{
	double factor = 0;
	Dvector* ki[N];
	Dvector Ai(N);
	Dvector wi(N);
	Dvector phii(N);
	for (int i = 0; i < N; ++i) {
		factor = random()/RAND_MAX;
		ki[i] = new Dvector(2);
		*ki[i] = wind_dir;
		*ki[i] += factor;
		Ai(i) = intensity;
		wi(i) = sqrt(norm(*ki[i] * 9.81));
		phii(i) = M_PI;
	}
}



double& GerstnerWaveModel::operator () (double x, double y, double t) const {
	GerstnerWave* waves[N];
	double somme = 0.0f;
	for (int i = 0; i < N; ++i)	{
		waves[i] = new GerstnerWave(Ai(i), wi(i), ki[i], phii(i));
		somme += (*waves[i])(x,y,t);
	}
	return somme;
}

double& GerstnerWaveModel::operator () (double x, double y, double t) {
	GerstnerWave* waves[N];
	double somme = 0.0f;
	for (int i = 0; i < N; ++i)	{
		waves[i] = new GerstnerWave(Ai(i), wi(i), ki[i], phii(i));
		somme += (*waves[i])(x,y,t);
	}
	return somme;
}