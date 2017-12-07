#include "Drawing.h"


bool loadOBJ(const char* filename,
             std::list<Vec3f> &out_vertices,
             std::list<Vec2f> &out_uvs,
             std::list<Vec3f> &out_normals)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Vec3f> temp_vertices;
    std::vector<Vec2f> temp_uvs;
    std::vector<Vec3f> temp_normals;

    FILE *file = fopen(filename, "r");
    if (file == NULL) 
        return false;

    while (true) {
        char lineHeader[128];
        // Read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v") == 0) {
            Vec3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vn") == 0) {
            Vec3f normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "vt") == 0) {
            Vec2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
                                                                       &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
                                                                       &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9)
                return false;
            
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
        unsigned int vertexIndex = vertexIndices[i];
        Vec3f vertex = temp_vertices[vertexIndex-1];
        out_vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < normalIndices.size(); ++i) {
        unsigned int normalIndex = normalIndices[i];
        Vec3f normal = temp_normals[normalIndex-1];
        out_normals.push_back(normal);
    }

    for (unsigned int i = 0; i < uvIndices.size(); ++i) {
        unsigned int uvIndex = uvIndices[i];
        Vec2f uv = temp_uvs[uvIndex-1];
        out_uvs.push_back(uv);
    }

    return true;
}


void addCube(Vec3f pos,
             Vec3f rot_dir, float rot_angle,
             Vec3f scale,
             char* tex_name)
{
    Mesh3D *cube = new Mesh3D(pos,
                              rot_dir, rot_angle,
                              scale,
                              tex_name);
    std::list<Vec3f> vertices;
    std::list<Vec2f> uvs;
    std::list<Vec3f> normals;

    if (!loadOBJ("Meshes/cube.obj", vertices, uvs, normals))
        exit(0);
    
    cube->setVertices(vertices);
    cube->setUVs(uvs);
    cube->setNormals(normals);
    renderables.push_back(*cube);
}

void addSphere(Vec3f pos,
               Vec3f rot_dir, float rot_angle,
               Vec3f scale,
               char* tex_name)
{
    Mesh3D *sphere = new Mesh3D(pos,
                                rot_dir, rot_angle,
                                scale,
                                tex_name);
    std::list<Vec3f> vertices;
    std::list<Vec2f> uvs;
    std::list<Vec3f> normals;

    if (!loadOBJ("Meshes/sphere.obj", vertices, uvs, normals))
        exit(0);
    
    sphere->setVertices(vertices);
    sphere->setUVs(uvs);
    sphere->setNormals(normals);
    renderables.push_back(*sphere);
}


void renderScaleSpace()
{
    glLineWidth(1.0); 

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();

    glColor3f(1.0,1.0,1.0);
}


void drawPoint(Vec3f x)
{
    addSphere(x,
              Vec3f(0.0,1.0,0.0), 0.0f,
              Vec3f(0.005,0.005,0.005),
              "Textures/PPM/red.ppm");
}

void drawLine(Vec3f p1, Vec3f p2)
{

}

void drawLineBetweenPoints(Vec3f p1, Vec3f p2)
{

}

void drawCube(Vec3f center)
{
    addCube(center,
            Vec3f(0.0,1.0,0.0), 0.0f,
            Vec3f(1,1,1),
            "Textures/PPM/red.ppm");
}

void drawSphere(Vec3f center, float radius)
{
    addSphere(center,
              Vec3f(0.0,1.0,0.0), 0.0f,
              Vec3f(radius/20.0,radius/20.0,radius/20.0),
              "Textures/PPM/red.ppm");
}