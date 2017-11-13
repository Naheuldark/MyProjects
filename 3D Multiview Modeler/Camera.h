#ifndef CAMERA_H
#define CAMERA_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

#include <GL/glut.h>


// --------------------------------
//            CAMERA
// --------------------------------


extern int width, height;
extern float lx, lz, x, z;


void computePos(float deltaForward, float deltaRight);

#endif