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


    // VERTEX SELECTION
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {

            /*GLint viewport[4];
            GLdouble modelview[16];
            GLdouble projection[16];

            GLdouble winX, winY, winZ;

            glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
            glGetDoublev(GL_PROJECTION_MATRIX, projection);
            glGetIntegerv(GL_VIEWPORT, viewport);

            // When the left mouse button is clicked:
            // --> translate every 3D points into screen coordinates
            // --> the closest to the mouse wins!!

            Vec3f screen_point;
            Vec3f vert_min;

            for (std::list<Vec3f>::iterator vert = point_list.begin();
                 vert != point_list.end();
                 vert++) {
                gluProject((*vert).x, (*vert).y, (*vert).z,
                           modelview, projection, viewport,
                           &winX, &winY, &winZ);
                screen_point.x = (float)winX;
                screen_point.y = (float)viewport[3] - (float)winY;
                screen_point.z = 0;

                if (sqrt(pow(x-screen_point.x,2)+pow(y-screen_point.y,2)) <= 5) {
                    vert_min = *vert;
                    break;
                }
            }

            for (std::list<Vec3f>::iterator vert = point_list.begin(), col = color_list.begin();
                 vert != point_list.end() && col != color_list.end();
                 vert++, col++) {
                if (vert_min.x == (*vert).x &&
                    vert_min.y == (*vert).y &&
                    vert_min.z == (*vert).z) {
                    // Paint in red the selected vertex
                    (*col).y = 0;
                    (*col).z = 0;
                } else { // Unselect the previously selected vertices
                    (*col).y = 1;
                    (*col).z = 1;
                }
            }*/
        }
    }


    // DRAWING
    if (button == GLUT_LEFT_BUTTON) {
        if (isDrawing) { // if isDrawing != NOTHING
            switch (isDrawing) {
                case POINT:
                    std::cout << "hellmo";
                    drawPoint(Vec3f(0,0,0));
                    break;
                case LINE:
                    break;
                case CUBE:
                    break;
                case SPHERE:
                    break;
            }
        }
    }
}