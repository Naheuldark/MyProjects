#include "Height.h"
#include "Dvector.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>


Height::Height(Height const& H) :
	Lx(H.getLx()), Ly(H.getLy()), nx(H.getNx()), ny(H.getNy()),
	vec(H.getVec())
{
	assert(H.getVec().getVal() != NULL);
}

Height::Height(double Lx, double Ly, int nx, int ny) :
	Lx(Lx), Ly(Ly), nx(nx), ny(ny), vec(Dvector(nx*ny))
{
	assert(Lx >= 0 && Ly >= 0 && nx >= 0 && ny >= 0);
}


Height::~Height() {
	//this->vec.~Dvector();
}


double Height::getLx() const {
	return Lx;
}

double Height::getLy() const {
	return Ly;
}

int Height::getNx() const {
	return nx;
}

int Height::getNy() const {
	return ny;
}

Dvector Height::getVec() const {
	return vec;
}


void Height::setLx(double Lx) {
	assert(Lx >= 0);
	this->Lx = Lx;
}

void Height::setLy(double Ly) {
	assert(Ly >= 0);
	this->Ly = Ly;
}

void Height::setNx(int nx) {
	assert(nx >= 0);
	this->nx = nx;
}

void Height::setNy(int ny) {
	assert(ny >= 0);
	this->ny = ny;
}


double& Height::operator () (int offset) const {
	assert(offset >= 0 && offset < vec.size());
	return vec(offset);
}

double& Height::operator () (int offset) {
	assert(offset >= 0 && offset < vec.size());
	return vec(offset);
}


Height& Height::operator = (const Height &H) {
	Lx = H.getLx();
	Ly = H.getLy();
	nx = H.getNx();
	ny = H.getNy();
	vec = H.getVec();
	return *this;
}


std::ostream& operator << (std::ostream &out, const Height &H) {
	for (int j = 0; j < H.getNy()-1; ++j) {
		for (int i = 0; i < H.getNx(); ++i) {
			out << i*H.getLx()/(H.getNx()-1) << " " << j*H.getLy()/(H.getNy()-1) << " " << H(i*H.getNy()+j) << std::endl;
		}
		out << std::endl;
	}
	for (int i = 0; i < H.getNx(); ++i) {
		out<< i*H.getLx()/(H.getNx()-1) << " " << (H.getNy()-1)*H.getLy()/(H.getNy()-1) << " " << H(i*H.getNy()+H.getNy()-1) << std::endl;
	}
	return out;
}