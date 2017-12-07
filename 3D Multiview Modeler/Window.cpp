#include "Window.h"


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


Vec3f getWorldCoordinates(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
 
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
 
    return Vec3f(posX, posY, posZ);
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
    obj_file.open("Output/scene.obj");

    int num_vertices = 0;

    for (std::list<Mesh3D>::iterator mesh = renderables.begin();
         mesh != renderables.end();
         mesh++) {
        
        std::list<Vec3f> vertices = mesh->getComputedVertices();

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




void generateIMG()
{
    std::ofstream bmp_file;
    bmp_file.open("Output/scene.ppm");

    std::vector<unsigned char> pixels(1 * 1 * 3);

    bmp_file << "P3" << std::endl;
    bmp_file << width*2/3 << " " << height << std::endl;
    bmp_file << "255" << std::endl;

    /*
     ***  Custom Shadow Algorithm ***
     Get the point of the image in the 3D scene
     Compute a ray from this point to the light
     If there is at least an intersection
        Color = black
     Else
        Color = readPixel
     */

    for (int j = height; j >= 0; --j) {
        //std::cout << "\n\nLine " << j << std::endl; 
        for (int i = 0; i < width*2/3; ++i)  {
            Vec3f point3D = getWorldCoordinates(i+width/3,j);
            bool intersection = false;

            glReadPixels(i,j,
                         1,1,
                         GL_RGB, GL_UNSIGNED_BYTE,
                         &pixels[0]);

            if ((int)pixels[0] == 25 &&     // If it's a background pixel
                (int)pixels[1] == 25 &&     // there is no need to compute
                (int)pixels[2] == 25) {     // the shadows!! ==> SAVE TIME
                bmp_file << (int)pixels[0] << " ";
                bmp_file << (int)pixels[1] << " ";
                bmp_file << (int)pixels[2] << " ";
            } else {
                for (std::list<Mesh3D>::iterator mesh = renderables.begin();
                     mesh != renderables.end();
                     mesh++) {
                    
                    intersection = mesh->intersect(point3D, Vec3f(light_pos[0], light_pos[1], light_pos[2]));
                    if (intersection == true)
                        break;
                
                }

                if (intersection) {
                    bmp_file << 0 << " ";
                    bmp_file << 0 << " ";
                    bmp_file << 0 << " ";
                } else {
                    bmp_file << (int)pixels[0] << " ";
                    bmp_file << (int)pixels[1] << " ";
                    bmp_file << (int)pixels[2] << " ";
                }
            }
        }
        bmp_file << std::endl;
    }
    std::cout << "Done" << std::endl;
    bmp_file.close();
}