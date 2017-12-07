#ifndef MOUSE_H
#define MOUSE_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <sstream>
#include "Vec3.h"
#include "Mesh3D.h"
#include "PopUpMenu.h" // for the constants
#include "Drawing.h"
#include "Window.h"

#include <GL/glut.h>


// --------------------------------
//             MOUSE
// --------------------------------


extern int isDrawing;
extern int xOrigin, yOrigin;
extern float angle, psi, deltaAngle, deltaPsi;
extern float lx, ly, lz;
extern int mainWindow;
extern std::list<Mesh3D> renderables;
extern std::list<char*> historic;


void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);

#endif