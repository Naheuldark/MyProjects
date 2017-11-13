#ifndef POPUPMENU_H
#define POPUPMENU_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

#include <GL/glut.h>

#include "Window.h"


// -------------------- //
//         MENUS        //
// -------------------- //

// Constant definitions for Menus
#define RENDER  1
#define OBJ     2

#define FILL 1
#define WIRE 2

#define NOTHING 0
#define POINT   1
#define LINE    2
#define CUBE    3
#define SPHERE  4

extern int isDrawing;
extern int menuFlag;
extern int fillMenu, mainMenu, drawMenu, exportMenu;
extern std::list<char*> historic;

void processMenuStatus(int status, int x, int y);

void processMainMenu(int option);

void processFillMenu(int option);
void processShrinkMenu(int option);

void createPopupMenus();

#endif