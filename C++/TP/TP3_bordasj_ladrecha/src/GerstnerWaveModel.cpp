#include "GerstnerWaveModelModel.h"

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

GerstnerWaveModel::GerstnerWaveModel() {
	int factor = 0;
	int N = 10;
	for (int i = 0; i < N; ++i) {
		factor = random()/RAND_MAX;
		ki(i) = 
	}
}



double GerstnerWaveModel::operator () (Dvector x0, double t) const {
	return amplitude * cos(dot(direction, x0) - frequency*t + phase);
}

double GerstnerWaveModel::operator () (Dvector x0, double t) {
	return amplitude * cos(dot(direction, x0) - frequency*t + phase);
}