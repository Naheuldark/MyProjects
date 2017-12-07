#include "Mouse.h"
#include "Drawing.h"


void mouseMove(int x, int y) 
{
    if (xOrigin >= 0 && yOrigin >= 0) {
        // Update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;
        deltaPsi = (y - yOrigin) * 0.001f;

        // Update camera's direction
        lx = sin(angle + deltaAngle) - sin(psi + deltaPsi);
        lz = -cos(angle + deltaAngle) + sin(psi + deltaPsi);

        glutSetWindow(mainWindow);
        glutPostRedisplay();
    }
}


void mouseButton(int button, int state, int x, int y) 
{
    Vec3f mouseWorldCoord = getWorldCoordinates(x, y);

    // CAMERA
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            angle += deltaAngle;
            psi += deltaPsi;
            deltaAngle = 0.0f;
            deltaPsi = 0.0f;
            xOrigin = -1;
            yOrigin = -1;
        } else  {
            xOrigin = x;
            yOrigin = y;
        }
    }


   // DRAWING
    if (button == GLUT_LEFT_BUTTON) {
        if (isDrawing) { // if isDrawing != NOTHING
            switch (isDrawing) {
                case POINT:
                    drawPoint(mouseWorldCoord);
                    isDrawing = !isDrawing;
                    break;
                case LINE:
                    break;
                case CUBE:
                    drawCube(mouseWorldCoord);
                    isDrawing = !isDrawing;
                    break;
                case SPHERE:
                    drawSphere(mouseWorldCoord, 1.0);
                    isDrawing = !isDrawing;
                    break;
            }
        }
    }
}