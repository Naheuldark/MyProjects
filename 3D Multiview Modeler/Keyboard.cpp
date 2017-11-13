#include "Keyboard.h"


void processNormalKeys(unsigned char key, int x, int y) 
{
    glutSetMenu(mainMenu);
    switch (key) {
        // Exit when ESC key is pressed
        case 27:
            glutDestroyMenu(mainMenu);
            glutDestroyMenu(fillMenu);
            glutDestroyMenu(drawMenu);
            exit(0);
            break;

        // Switch between ortho/persp projection
        case 9:
            isPersp = !isPersp;
            if (isPersp) { historic.push_front("Projection mode set to Perspective."); }
            else { historic.push_front("Projection mode set to Ortho."); }
            break;

        // Move the camera
        case 'z':
            deltaForward = 0.5f;
            break;
        case 'q':
            deltaRight = -0.5f;
            break;
        case 'd':
            deltaRight = 0.5f;
            break;
        case 's':
            deltaForward = -0.5f;
            break;

    }

    glutSetWindow(mainWindow);
    glutPostRedisplay();


    if (key == 27) {
        glutDestroyWindow(mainWindow);
        exit(0);
    }
}

void releaseNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
        case 'z':
        case 's':
            deltaForward = 0.0f;
            break;

        case 'q':
        case 'd':
            deltaRight = 0.0f;
            break;
    }
}



void pressKey(int key, int x, int y) 
{
    switch (key) {
        case GLUT_KEY_UP: 
            deltaForward = 0.5f; 
            break;
        case GLUT_KEY_DOWN: 
            deltaForward = -0.5f; 
            break;
        case GLUT_KEY_LEFT: 
            deltaRight = -0.5f; 
            break;
        case GLUT_KEY_RIGHT: 
            deltaRight = 0.5f; 
            break;
    }

    glutSetWindow(mainWindow);
    glutPostRedisplay();
}

void releaseKey(int key, int x, int y) 
{
    switch (key) {
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: 
            deltaForward = 0.0f;
            break;
        case GLUT_KEY_LEFT: 
        case GLUT_KEY_RIGHT:
            deltaRight = 0.0f;
            break;
    }
}