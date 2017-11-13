#include "Rendering.h"
#include "Drawing.h"
#include "Window.h"
#include "Camera.h"


// Display func for main window
void renderScene() 
{
    glutSetWindow(mainWindow);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}


// Display func for sub window 1
void renderScenesw1() 
{
    glutSetWindow(subWindow1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.1, 0.1, 0.0);

    setProjection(width*2/3 - border, height - 2*border);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //some light properties
    float light_pos[] = {2,2,2,1};

    float amb[4] = {1,1,1, 1};
    float diff[4] = {1,1,1, 1};
    float spec[4] = {1,1,1, 1};

    // http://devernay.free.fr/cours/opengl/materials.html
    float m_amb[] = {0.25, 0.20725, 0.20725, 1};
    float m_dif[] = {1, 0.829, 0.829};
    float m_spec[] = {0.296648, 0.296648, 0.296648};
    float shiny = 0.088*128;

    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);


    glColor3f(1,1,1);

    //set materials
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

    //set light properties
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);


    // renderScaleSpace();
    // Render all the renderables for the scene
    for (std::list<Mesh3D>::iterator mesh = renderables.begin();
         mesh != renderables.end();
         mesh++) {
        mesh->render();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_BLEND);

    // Display fps in the top window
    frame++;

    time = glutGet(GLUT_ELAPSED_TIME);

    if (time - timebase > 1000) {
        sprintf(fps, "FPS Counter: %4.2f",
                frame*1000.0/(time-timebase));
        timebase = time;
        frame = 0;
    }

    // Set the orthographic projection to write things on the screen
    setOrthographicProjection();
        glPushMatrix();
            glColor3f(1,1,1);
            glLoadIdentity();
            renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_12, fps);
        glPopMatrix();
    restorePerspectiveProjection();

    glutSwapBuffers();
}


// Display func for sub window 2
void renderScenesw2() 
{
    glutSetWindow(subWindow2);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.1, 0.1, 0.0);

    glLoadIdentity();
    gluLookAt(x, y + 15, z,
              x, y - 1, z,
              lx, 0, lz);

    // Draw red cone at the location of the main camera
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(x, y, z);
        glRotatef(180 - (angle + deltaAngle)*180.0/3.14, 0.0, 1.0, 0.0);
        glutSolidCone(0.2, 0.8f, 4,4);
    glPopMatrix();

    renderScaleSpace();
    // Render all the renderables for the scene
    for (std::list<Mesh3D>::iterator mesh = renderables.begin();
         mesh != renderables.end();
         mesh++) {
        mesh->render();
    }

    glutSwapBuffers();
}


// Display func for utility window
void renderUtilityWindow() 
{
    int x = 10, y = 40;

    glutSetWindow(utilityWindow);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glLoadIdentity();

    char title[50];
    sprintf(title, "Historic");

    // Set the orthographic projection to write things on the screen
    setOrthographicProjection();
        glPushMatrix();
            glLoadIdentity();
            glColor3f(0.0,0.0,0.0);

            renderBitmapString(x, y, 0, 
                               GLUT_BITMAP_HELVETICA_18, 
                               title);

            int i = 0;
            for (std::list<char*>::iterator list_iter = historic.begin();
                 list_iter != historic.end() && i < 25;
                 list_iter++) {
                y += 30; i++;
                //std::cout << *list_iter << std::endl;
                renderBitmapString(x, y, 0, 
                                   GLUT_BITMAP_HELVETICA_12, 
                                   *list_iter);
            }
        glPopMatrix();
    restorePerspectiveProjection();

    glutSwapBuffers();
}


// Global render func
void renderSceneAll() 
{
    /*point_list.clear();*/

    // Check for keyboard movement
    if (deltaForward || deltaRight) {
        computePos(deltaForward, deltaRight);
        glutSetWindow(mainWindow);
        glutPostRedisplay();
    }

    renderScene();
    renderScenesw1();
    renderScenesw2();
    renderUtilityWindow();
}