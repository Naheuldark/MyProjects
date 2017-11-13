#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>

#include <GL/glut.h>

#include "Vec3.h"
#include "Mesh3D.h"

#include "Window.h"
#include "PopUpMenu.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Drawing.h"
#include "Rendering.h"
#include "Camera.h"


// -------------------- //
//      VARIABLES       //
// -------------------- //


int fillMenu, mainMenu, drawMenu, exportMenu;   // Pop up menu identifiers
int menuFlag = 0;                               // Menu status


float angle = 0.0f;                     // Angles of rotation
float psi = 0.0f;

float lx = 0.0f, lz = -2.0f, ly = 0.0f; // Camera's direction
float x = 0.5f, z = 8.0f, y = 1.0f;    // XZ position of the camera


float deltaForward = 0; // "Amount" of forward movement
float deltaRight = 0;   // "Amount" of right movement

float deltaAngle = 0;   // "Amount" of angular movement
float deltaPsi = 0;
int xOrigin = -1;       // Origin of the movement
int yOrigin = -1;


int isDrawing = NOTHING;

bool isPersp = true;


int width, height;      // Width and height of the window


int frame;
long time, timebase;
char fps[50];


std::list<Mesh3D> renderables;  // Store all the renderables in the scene

std::list<char*> historic;


int mainWindow, subWindow1, subWindow2, utilityWindow;
int border = 6;     // Border between subwindows





// -----------------------------------
//             MAIN and INIT
// -----------------------------------

void init() 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Register callbacks
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardUpFunc(releaseNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
}


int main(int argc, char **argv) 
{
    // Init GLUT and create main window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    mainWindow = glutCreateWindow("3D Multiview Modeler");

    // Callbacks for main window
    glutDisplayFunc(renderSceneAll);
    glutReshapeFunc(changeSize);
    init();

    // Sub windows
    subWindow2 = glutCreateSubWindow(mainWindow, 
                                     border, border,
                                     width/3 - border*3/2, height/2 - border*3/2);
    glutDisplayFunc(renderScenesw2);
    init();

    utilityWindow = glutCreateSubWindow(mainWindow, 
                                        border, (height + border)/2,
                                        width/3 - border*3/2, height/2 - border*3/2);
    glutDisplayFunc(renderUtilityWindow);
    init();

    subWindow1 = glutCreateSubWindow(mainWindow, 
                                     (width + border)/3, border,
                                     width*2/3 - border, height - border);
    glutDisplayFunc(renderScenesw1);
    init();

    historic.push_front("Creating the main window.");
    historic.push_front("Creating the top view window.");
    historic.push_front("Creating the historic window.");
    historic.push_front("Projection mode set to Perspective.");

    // Init menus in the main window
    createPopupMenus();
    glColor3f(1, 1, 1);

    //turn on lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Add a few cubes in the renderables list to create a frame
    addCube(Vec3f(0.0,0.0,0.0),
            Vec3f(0.0,1.0,0.0), 0.0f,
            Vec3f(10.0,0.1,10.0));

    addCube(Vec3f(5.0,2.5,0.0),
            Vec3f(0.0,1.0,0.0), 0.0f,
            Vec3f(0.1,5.0,10.0));

    addCube(Vec3f(-5.0,2.5,0.0),
            Vec3f(0.0,1.0,0.0), 0.0f,
            Vec3f(0.1,5.0,10.0));

    addCube(Vec3f(0.0,2.5,-5.0),
            Vec3f(0.0,1.0,0.0), 0.0f,
            Vec3f(10,5.0,0.1));



    addSphere(Vec3f(0.0,1.0,0.0),
              Vec3f(0.0,1.0,0.0), 180.0f,
              Vec3f(0.1,0.1,0.1));


    // Enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}   