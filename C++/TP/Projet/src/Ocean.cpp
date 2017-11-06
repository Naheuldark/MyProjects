#include "Ocean.h"
#include "GenericVector.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>


Ocean::Ocean(double Lx, double Ly,
             int nx, int ny,
             double t,
             WaveModel model) :
	Lx(Lx), Ly(Ly), nx(nx), ny(ny),
	t(t), H(Height(Lx,Ly,nx,ny)),
	model(model), 
	vertices(GenericVector<double>(nx*ny))
{
}


Ocean::~Ocean() {
}

void Ocean::setT(double nt) {
	t = nt;
}


void Ocean::generateHeight(double h_init) {
	for (int i = 0; i < nx; ++i) {
		for (int j = 0; j < ny; ++j) {
			H(i*ny+j) = h_init;
		}
	}
}


void Ocean::compute() {
	for (int x = 0; x < nx; ++x) {
		for (int y = 0; y < ny; ++y) {
			H(x*ny+y) = model(x,y,t);
			//fprintf(stderr, "%d\n", model(x,y,t));
		}
	}
}


void Ocean::gl_vertices() {

}