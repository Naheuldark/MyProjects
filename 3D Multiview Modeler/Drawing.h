#ifndef DRAWING_H
#define DRAWING_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include "Vec3.h"
#include "Vec2.h"
#include "Mesh3D.h"
#include <string>

#include <GL/glut.h>


// --------------------------------
//             DRAWING
// --------------------------------


extern std::list<char*> historic;
extern std::list<Mesh3D> renderables;

bool loadOBJ(const char* filename,
             std::list<Vec3f> &out_vertices,
             std::list<Vec2f> &out_uvs,
             std::list<Vec3f> &out_normals);

void addCube(Vec3f pos,
             Vec3f rot_dir, float rot_angle,
             Vec3f scale);

void addSphere(Vec3f pos,
               Vec3f rot_dir, float rot_angle,
               Vec3f scale);

void renderScaleSpace();

void drawPoint(Vec3f x);
void drawLine(Vec3f p1, Vec3f p2);
void drawLineBetweenPoints(Vec3f p1, Vec3f p2);
void drawCube(Vec3f center);
void drawSphere(Vec3f center, float radius);

#endif