#include "Window.h"

#include <iostream>

void setProjection(int new_width, int new_height)
{
    float ratio = 1.0f * new_width / new_height;
    
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, new_width, new_height);

    // Set the clipping volume
    if (isPersp) {
        gluPerspective(45, ratio, 0.1, 1000);
    } else {
        glOrtho(-new_width/200, new_width/200, -new_height/200, new_height/200, 0.1, 1000);
    }

    glMatrixMode(GL_MODELVIEW);
}


void changeSize(int new_width,int new_height) 
{
    // avoid windows with 0 height
    if (new_height == 0)
        new_height = 1;

    width = new_width;
    height = new_height;

    // set subwindow 1 as the active window
    glutSetWindow(subWindow1);
    // resize and reposition the sub window
    glutPositionWindow((width + border)/3, border);
    glutReshapeWindow(width*2/3 - border, height - 2*border);
    setProjection(width*2/3 - border, height - 2*border);

    // set subwindow 2 as the active window
    glutSetWindow(subWindow2);
    // resize and reposition the sub window
    glutPositionWindow(border, border);
    glutReshapeWindow(width/3 - border*3/2, height/2 - border*3/2);
    if (isPersp) setProjection(width/3 - border*3/2, height/2 - border*3/2);

    // set subwindow 3 as the active window
    glutSetWindow(utilityWindow);
    // resize and reposition the sub window
    glutPositionWindow(border, (height + border)/2);
    glutReshapeWindow(width/3 - border*3/2, height/2 - border*3/2);
    if (isPersp) setProjection(width/3 - border*3/2, height/2 - border*3/2);
}


void restorePerspectiveProjection() 
{
    glMatrixMode(GL_PROJECTION);
    
    // Restore previous projection matrix
    glPopMatrix();

    // Get back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}


void setOrthographicProjection() 
{
    // Switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // Save previous matrix which contains the settings for the perspective projection
    glPushMatrix();

    // Reset matrix
    glLoadIdentity();

    // Set a 2D orthographic projection
    gluOrtho2D(0, width, height, 0);

    // Switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}


void renderBitmapString(float x, float y, float z,
                        void *font,
                        char *string) 
{
    char *c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void generateOBJ()
{
    std::ofstream obj_file;
    obj_file.open("scene2.obj");

    int num_vertices = 0;

    for (std::list<Mesh3D>::iterator mesh = renderables.begin();
         mesh != renderables.end();
         mesh++) {
        
        std::list<Vec3f> vertices = (*mesh).getComputedVertices();

        for (std::list<Vec3f>::iterator vert = vertices.begin();
             vert != vertices.end();
             vert++) {
            obj_file << "v " << (*vert).x << " " << (*vert).y << " " << (*vert).z << std::endl;
            num_vertices++;
        }
    }

    for (int i = 1; i <= num_vertices; i+=3) {
        obj_file << "f " << i << " " << i+1 << " " << i+2 << std::endl;
    }

    obj_file.close();
}