#ifndef RENDERING_H
#define RENDERING_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include "Vec3.h"

#include <GL/glut.h>


// --------------------------------
//           RENDERING
// --------------------------------


extern int mainWindow, subWindow1, subWindow2, utilityWindow;
extern float x, y, z, lx, ly, lz;
extern int frame;
extern long time, timebase;
extern char fps[50];
extern std::list<char*> historic;
extern float angle, deltaAngle, deltaForward, deltaRight;
extern int sceneToRender;
extern int width, height, border;


void renderScene();
void renderScenesw1();
void renderScenesw2();

void renderUtilityWindow();

void renderSceneAll();

#endif