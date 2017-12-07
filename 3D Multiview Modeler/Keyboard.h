#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

#include <GL/glut.h>


// -----------------------------------
//             KEYBOARD
// -----------------------------------


extern int fillMenu, mainMenu, drawMenu;
extern int menuFlag;
extern int mainWindow;
extern bool isPersp;
extern float deltaForward, deltaRight;
extern std::list<char*> historic;
extern float light_pos[];


void processNormalKeys(unsigned char key, int x, int y);
void releaseNormalKeys(unsigned char key, int x, int y);

void pressKey(int key, int x, int y);
void releaseKey(int key, int x, int y);

#endif