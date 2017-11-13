#ifndef WINDOW_H
#define WINDOW_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <iostream>
#include <fstream>

#include <GL/glut.h>

#include "Vec3.h"
#include "Mesh3D.h"


// --------------------------------
//             WINDOW
// --------------------------------


extern int width, height;
extern int mainWindow, subWindow1, subWindow2, utilityWindow;
extern int border;
extern bool isPersp;
extern std::list<Mesh3D> renderables;


void setProjection(int new_width, int new_height);
void changeSize(int new_width,int new_height);

void restorePerspectiveProjection();
void setOrthographicProjection();

void renderBitmapString(float x, float y, float z,
                        void *font,
                        char *string);

void generateOBJ();

#endif