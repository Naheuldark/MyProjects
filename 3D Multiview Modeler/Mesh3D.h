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
           Vec3f scale,
           char* tex_name) :
        m_pos(pos),
        m_rot_dir(rot_dir), m_rot_angle(rot_angle),
        m_scale(scale)
    {
        m_tex = LoadPPM(tex_name, &m_tex_width, &m_tex_height, &m_tex_max);
        
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

            // Scale
            x *= m_scale.x;
            y *= m_scale.y;
            z *= m_scale.z;

            // Translate
            x += m_pos.x;
            y += m_pos.y;
            z -= m_pos.z;

            // Rotate
            /*if (m_rot_dir.x == 1.0) {
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
            */          

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

    /*
     * Intersect function
     * Compute the ray from the point to the light and returns true if there is
     * an intersection with the mesh
     */
    bool intersect(Vec3f orig, Vec3f dest)
    {
        Vec3f dir = dest - orig;
        float t;

        int res = 0;

        std::list<Vec3f>::iterator vert = m_vertices.begin();
        while (vert != m_vertices.end()) {
            Vec3f v0 = (*vert); vert++;
            Vec3f v1 = (*vert); vert++;
            Vec3f v2 = (*vert); vert++;

            //std::cout << v0 << "\t" << v1 << "\t" << v2 << std::endl;

            // compute plane's normal
            Vec3f v0v1 = v1 - v0; 
            Vec3f v0v2 = v2 - v0; 
            // no need to normalize
            Vec3f N = v0v1.cross(v0v2); // N 
            float area2 = N.length(); 
         
            // Step 1: finding P
         
            // check if ray and plane are parallel ?
            float NdotRayDirection = N.dot(dir); 
            if (fabs(NdotRayDirection) < 0.0001) // almost 0 
                continue; // they are parallel so they don't intersect !
         
            float d = N.dot(v0); 
         
            t = (N.dot(orig) + d) / NdotRayDirection; 
            // check if the triangle is in behind the ray
            if (t < 0) continue; // the triangle is behind 
         
            Vec3f P = orig + t * dir; 
         
            // Step 2: inside-outside test
            Vec3f C; // vector perpendicular to triangle's plane 
         
            // edge 0
            Vec3f edge0 = v1 - v0; 
            Vec3f vp0 = P - v0; 
            C = edge0.cross(vp0); 
            if (N.dot(C) < 0) continue; // P is on the right side 
         
            // edge 1
            Vec3f edge1 = v2 - v1; 
            Vec3f vp1 = P - v1; 
            C = edge1.cross(vp1); 
            if (N.dot(C) < 0) continue; // P is on the right side 
         
            // edge 2
            Vec3f edge2 = v0 - v2; 
            Vec3f vp2 = P - v2; 
            C = edge2.cross(vp2); 
            if (N.dot(C) < 0) continue; // P is on the right side 
            
            return true; // this ray hits the triangle    
        }

        return false;

    }

    void setVertices(std::list<Vec3f> v) { m_vertices = v; }
    std::list<Vec3f> getVertices() { return m_vertices; }
    void setUVs(std::list<Vec2f> u) { m_uvs = u; }
    void setNormals(std::list<Vec3f> n) { m_normals = n; }


private:
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
