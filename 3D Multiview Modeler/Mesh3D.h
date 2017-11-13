#ifndef MESH3D_H
#define MESH3D_H

#include <cstdlib>
#include <stdio.h>
#include <list>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "Vec3.h"
#include "Vec2.h"

class Mesh3D
{
public:
    Mesh3D(Vec3f pos,
           Vec3f rot_dir, float rot_angle,
           Vec3f scale) :
        m_pos(pos),
        m_rot_dir(rot_dir), m_rot_angle(rot_angle),
        m_scale(scale)
    {
        m_tex = LoadPPM("Textures/marble.ppm", &m_tex_width, &m_tex_height, &m_tex_max);
        
        glEnable(GL_TEXTURE_2D);
        
        glGenTextures(1, m_textures);
        
        glBindTexture(GL_TEXTURE_2D, m_textures[0]);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_tex_width, m_tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_tex);
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    ~Mesh3D() {}



    void render()
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);

            glTranslatef(m_pos.x, m_pos.y, m_pos.z);
            glRotatef(m_rot_angle, m_rot_dir.x, m_rot_dir.y, m_rot_dir.z);
            glScalef(m_scale.x, m_scale.y, m_scale.z);

            glBindTexture(GL_TEXTURE_2D, m_textures[0]);

            std::list<Vec3f>::iterator normal = m_normals.begin();
            std::list<Vec2f>::iterator uv = m_uvs.begin();
            std::list<Vec3f>::iterator vertex = m_vertices.begin();

            while (vertex != m_vertices.end() &&
                   normal != m_normals.end() &&
                   uv != m_uvs.end()) {

                glBegin(GL_TRIANGLES);
                    glColor3f(1,1,1);
                    glTexCoord2f((*uv).x, (*uv).y);
                    glNormal3f((*normal).x, (*normal).y, (*normal).z);
                    glVertex3f((*vertex).x, (*vertex).y, (*vertex).z);
                    vertex++; uv++; normal++;

                    glColor3f(1,1,1);
                    glTexCoord2f((*uv).x, (*uv).y);
                    glNormal3f((*normal).x, (*normal).y, (*normal).z);
                    glVertex3f((*vertex).x, (*vertex).y, (*vertex).z);
                    vertex++; uv++; normal++;

                    glColor3f(1,1,1);
                    glTexCoord2f((*uv).x, (*uv).y);
                    glNormal3f((*normal).x, (*normal).y, (*normal).z);
                    glVertex3f((*vertex).x, (*vertex).y, (*vertex).z);
                    vertex++; uv++; normal++;
                glEnd();
            }

            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }


    // Compute the coord of each vertex for the OBJ export
    std::list<Vec3f> getComputedVertices()
    {
        std::list<Vec3f> res;

        float x,y,z;
        for (std::list<Vec3f>::iterator vert = m_vertices.begin();
             vert != m_vertices.end();
             vert++) {

            x = (*vert).x;
            y = (*vert).y;
            z = (*vert).z;

            // Translate
            x += m_pos.x;
            y += m_pos.y;
            z += m_pos.z;

            // Scale
            x *= m_scale.x;
            y *= m_scale.y;
            z *= m_scale.z;

            // Rotate
            if (m_rot_dir.x == 1.0) {
                // Axis x
                y = y*cos(m_rot_angle) - z*sin(m_rot_angle);
                z = y*sin(m_rot_angle) + z*cos(m_rot_angle);
            } else if (m_rot_dir.y == 1.0) {
                // Axis y
                x = x*cos(m_rot_angle) + z*sin(m_rot_angle);
                z = z*cos(m_rot_angle) - x*sin(m_rot_angle);
            } else if (m_rot_dir.z == 1.0) {
                // Axis z
                x = x*cos(m_rot_angle) - y*sin(m_rot_angle);
                y = x*sin(m_rot_angle) + y*cos(m_rot_angle);
            }           

            res.push_back(Vec3f(x,z,y));
        }

        return res;
    }

    /* LoadPPM -- loads the specified ppm file, and returns the image data as a GLubyte 
     *  (unsigned byte) array. Also returns the width and height of the image, and the
     *  maximum colour value by way of arguments
     *  usage: GLubyte myImg = LoadPPM("myImg.ppm", &width, &height, &max);
     */
    GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
    {
        GLubyte* img;
        FILE *fd;
        int n, m;
        int  k, nm;
        char c;
        int i;
        char b[100];
        float s;
        int red, green, blue;
        
        fd = fopen(file, "r");

        fscanf(fd, "%[^\n] ", b);
        if (b[0] != 'P' || b[1] != '3')
            exit(0);

        fscanf(fd, "%c", &c);
        while (c == '#') {
            fscanf(fd, "%[^\n] ", b);
            printf("%s\n", b);
            fscanf(fd, "%c", &c);
        }
        ungetc(c, fd); 
        fscanf(fd, "%d %d %d", &n, &m, &k);

        nm = n * m;

        img = (GLubyte*)malloc(3*sizeof(GLuint)*nm);


        s = 255.0/k;


        for (i = 0; i < nm; i++) {
            fscanf(fd, "%d %d %d", &red, &green, &blue);
            img[3*nm-3*i-3] = red*s;
            img[3*nm-3*i-2] = green*s;
            img[3*nm-3*i-1] = blue*s;
        }

        *width = n;
        *height = m;
        *max = k;

        return img;
    }

    void setVertices(std::list<Vec3f> v) { m_vertices = v; }
    void setUVs(std::list<Vec2f> u) { m_uvs = u; }
    void setNormals(std::list<Vec3f> n) { m_normals = n; }


private:
    float m_verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
    float m_cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

    GLubyte* m_tex;
    GLuint m_textures[1];
    int m_tex_width, m_tex_height, m_tex_max;

    std::list<Vec3f> m_vertices;
    std::list<Vec2f> m_uvs;
    std::list<Vec3f> m_normals;

    Vec3f m_pos;
    Vec3f m_rot_dir;
    float m_rot_angle;
    Vec3f m_scale;
};

#endif // MESH3D_H
