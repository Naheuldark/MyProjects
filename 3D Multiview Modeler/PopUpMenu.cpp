#include "PopUpMenu.h"


void processMenuStatus(int status, int x, int y) 
{
    if (status == GLUT_MENU_IN_USE)
        menuFlag = 1;
    else
        menuFlag = 0;
}


void processMainMenu(int option) 
{}


void processExportMenu(int option)
{
    switch (option) {
        case RENDER:
            generateIMG();
            historic.push_front("Rendering the scene.");
            break;
        case OBJ:
            generateOBJ();
            historic.push_front("Generating OBJ file.");
            break;
    }
}


void processFillMenu(int option) 
{
    switch (option) {
        case FILL: 
            glPolygonMode(GL_FRONT, GL_FILL);
            historic.push_front("Fill mode activated.");
            break;
        case WIRE: 
            glPolygonMode(GL_FRONT, GL_LINE);
            historic.push_front("Line mode activated.");
            break;
    }
}


void processDrawMenu(int option)
{
    switch (option) {
        case POINT:
            historic.push_front("Drawing a point.");
            isDrawing = POINT;
            break;
        case LINE:
            historic.push_front("Drawing a line.");
            isDrawing = LINE;
            break;
        case CUBE:
            historic.push_front("Drawing a cube.");
            isDrawing = CUBE;
            break;
        case SPHERE:
            historic.push_front("Drawing a sphere.");
            isDrawing = SPHERE;
            break;
    }
}


void createPopupMenus() 
{
    exportMenu = glutCreateMenu(processExportMenu);
    glutAddMenuEntry("Render image", RENDER);
    glutAddMenuEntry("Export OBJ file", OBJ);

    fillMenu = glutCreateMenu(processFillMenu);
    glutAddMenuEntry("Fill", FILL);
    glutAddMenuEntry("Wire", WIRE);

    drawMenu = glutCreateMenu(processDrawMenu);
    glutAddMenuEntry("Point", POINT);
    glutAddMenuEntry("Line", LINE);
    glutAddMenuEntry("Cube", CUBE);
    glutAddMenuEntry("Sphere", SPHERE);

    mainMenu = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Export", exportMenu);
    glutAddSubMenu("Draw", drawMenu);
    glutAddSubMenu("Polygon Mode ", fillMenu);
    
    // Attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Is the menu active?
    glutMenuStatusFunc(processMenuStatus);
}