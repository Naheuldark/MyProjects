#include "./../include/Geometries.hpp"
// #include "./../include/log.hpp"

#include <array>

// #include <chrono>
// #include <random>
// #include <glm/gtx/color_space.hpp>
// #include <glm/gtc/type_ptr.hpp>

void getUnitCube(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords)
{
    //Face 1
    positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));

    normals.push_back(glm::vec3(0.0,0.0,-1.0));
    normals.push_back(glm::vec3(0.0,0.0,-1.0));
    normals.push_back(glm::vec3(0.0,0.0,-1.0));

    //Face 2
    positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, -0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,0.0));

    normals.push_back(glm::vec3(0.0,0.0,-1.0));
    normals.push_back(glm::vec3(0.0,0.0,-1.0));
    normals.push_back(glm::vec3(0.0,0.0,-1.0));

    //Face 3
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, -0.5, 0.5));

    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));
    texCoords.push_back(glm::vec2(0.0,1.0));

    normals.push_back(glm::vec3(1.0,0.0,0.0));
    normals.push_back(glm::vec3(1.0,0.0,0.0));
    normals.push_back(glm::vec3(1.0,0.0,0.0));

    //Face 4
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));

    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));

    normals.push_back(glm::vec3(1.0,0.0,0.0));
    normals.push_back(glm::vec3(1.0,0.0,0.0));
    normals.push_back(glm::vec3(1.0,0.0,0.0));

    //Face 5
    positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(0.5, -0.5, 0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,0.0));

    normals.push_back(glm::vec3(0.0,0.0,1.0));
    normals.push_back(glm::vec3(0.0,0.0,1.0));
    normals.push_back(glm::vec3(0.0,0.0,1.0));

    //Face 6
    positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));

    normals.push_back(glm::vec3(0.0,0.0,1.0));
    normals.push_back(glm::vec3(0.0,0.0,1.0));
    normals.push_back(glm::vec3(0.0,0.0,1.0));

    //Face 7
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(-0.5, -0.5, -0.5));

    texCoords.push_back(glm::vec2(1.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,0.0));

    normals.push_back(glm::vec3(-1.0,0.0,0.0));
    normals.push_back(glm::vec3(-1.0,0.0,0.0));
    normals.push_back(glm::vec3(-1.0,0.0,0.0));

    //Face 8
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));

    texCoords.push_back(glm::vec2(1.0,1.0));
    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));

    normals.push_back(glm::vec3(-1.0,0.0,0.0));
    normals.push_back(glm::vec3(-1.0,0.0,0.0));
    normals.push_back(glm::vec3(-1.0,0.0,0.0));

    //Face 9
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, 0.5, -0.5));

    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));

    normals.push_back(glm::vec3(0.0,1.0,0.0));
    normals.push_back(glm::vec3(0.0,1.0,0.0));
    normals.push_back(glm::vec3(0.0,1.0,0.0));

    //Face 10
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));

    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));
    texCoords.push_back(glm::vec2(0.0,1.0));

    normals.push_back(glm::vec3(0.0,1.0,0.0));
    normals.push_back(glm::vec3(0.0,1.0,0.0));
    normals.push_back(glm::vec3(0.0,1.0,0.0));

    //Face 11
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(0.0,0.0));
    texCoords.push_back(glm::vec2(1.0,0.0));

    normals.push_back(glm::vec3(0.0,-1.0,0.0));
    normals.push_back(glm::vec3(0.0,-1.0,0.0));
    normals.push_back(glm::vec3(0.0,-1.0,0.0));

    //Face 12
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, -0.5, 0.5));

    texCoords.push_back(glm::vec2(0.0,1.0));
    texCoords.push_back(glm::vec2(1.0,0.0));
    texCoords.push_back(glm::vec2(1.0,1.0));

    normals.push_back(glm::vec3(0.0,-1.0,0.0));
    normals.push_back(glm::vec3(0.0,-1.0,0.0));
    normals.push_back(glm::vec3(0.0,-1.0,0.0));
}

void getUnitIndexedCube(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::ivec3>& indices)
{
    positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, -0.5, -0.5));
    positions.push_back(glm::vec3(0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
    positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
    positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, 0.5, 0.5));
    positions.push_back(glm::vec3(0.5, -0.5, 0.5));

    for (const glm::vec3& x : positions) {
        normals.push_back( glm::normalize(x) );
    }

    indices.push_back(glm::ivec3(0, 2, 1));
    indices.push_back(glm::ivec3(0, 3, 2));
    indices.push_back(glm::ivec3(1, 6, 7));
    indices.push_back(glm::ivec3(1, 2, 6));
    indices.push_back(glm::ivec3(5, 4, 7));
    indices.push_back(glm::ivec3(5, 7, 6));
    indices.push_back(glm::ivec3(4, 3, 0));
    indices.push_back(glm::ivec3(4, 5, 3));
    indices.push_back(glm::ivec3(3, 6, 2));
    indices.push_back(glm::ivec3(3, 5, 6));
    indices.push_back(glm::ivec3(4, 0, 1));
    indices.push_back(glm::ivec3(4, 1, 7));
}

void getUnitPlane(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords)
{
    positions.resize(6, glm::vec3(0.0,0.0,0.0));
    texCoords.resize(6, glm::vec2(0.0,0.0));
    normals.resize(6, glm::vec3(0.0,0.0,1.0));

    //First triangle
    positions[0] =glm::vec3(-0.5,-0.5,0.0);
    positions[1] =glm::vec3(0.5,-0.5,0.0);
    positions[2] =glm::vec3(0.5,0.5,0.0);

    texCoords[0] =glm::vec2(0.0,0.0);
    texCoords[1] =glm::vec2(1.0,0.0);
    texCoords[2] =glm::vec2(1.0,1.0);

    //Second triangle
    positions[3] =glm::vec3(-0.5,-0.5,0.0);
    positions[4] =glm::vec3(0.5,0.5,0.0);
    positions[5] =glm::vec3(-0.5,0.5,0.0);

    texCoords[3] =glm::vec2(0.0,0.0);
    texCoords[4] =glm::vec2(1.0,1.0);
    texCoords[5] =glm::vec2(0.0,1.0);
}

void getUnitMap(int maxWidth, int maxLength, int maxHeight, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords)
{
    positions.resize(6*maxWidth*maxLength, glm::vec3(0.0,0.0,0.0));
    texCoords.resize(6*maxWidth*maxLength, glm::vec2(0.0,0.0));
    normals.resize(6*maxWidth*maxLength, glm::vec3(0.0,0.0,1.0));

    int ind = 0;

    for (int i = 0; i < maxLength; ++i) {
        for (int j = 0; j < maxWidth; ++j) {
            positions[ind] = glm::vec3(float(i), float(j), height(float(i), float(j), maxHeight, maxLength, maxWidth));
            positions[ind+1] = glm::vec3(float(i), float(j+1), height(float(i), float(j+1), maxHeight, maxLength, maxWidth));
            positions[ind+2] = glm::vec3(float(i+1), float(j), height(float(i+1), float(j), maxHeight, maxLength, maxWidth));

            texCoords[ind] = glm::vec2(0.0,0.0);
            texCoords[ind+1] = glm::vec2(0.0,1.0);
            texCoords[ind+2] = glm::vec2(1.0,0.0);

            positions[ind+3] = glm::vec3(float(i), float(j+1), height(float(i), float(j+1), maxHeight, maxLength, maxWidth));
            positions[ind+4] = glm::vec3(float(i+1), float(j+1), height(float(i+1), float(j+1), maxHeight, maxLength, maxWidth));
            positions[ind+5] = glm::vec3(float(i+1), float(j), height(float(i+1), float(j), maxHeight, maxLength, maxWidth));

            texCoords[ind+3] = glm::vec2(0.0,1.0);
            texCoords[ind+4] = glm::vec2(1.0,1.0);
            texCoords[ind+5] = glm::vec2(1.0,0.0);

            ind += 6;
        }
    }

    for (const glm::vec3& x : positions) {
        normals.push_back(glm::normalize(x));
    }
}

float height(float i, float j, float maxHeight, float maxLength, int maxWidth)
{
    if (i <= 10)
        return maxHeight;

    float h = maxHeight + 4 - i*maxHeight/maxLength;

    if (j > 17*cos(20*i/maxLength)*cos(20*i/maxLength) && j < maxWidth - 17*sin(20*i/maxLength)*sin(20*i/maxLength)) {
        if (i > 10 && i < 13)
            return h-i+10;
        if (i > maxLength - 15)
            return 0.0;
        return h-3;
    }

    return h;
}

void getMountainsSurrounding(int maxWidth, int maxLength, int maxHeight, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords)
{
    positions.resize((maxLength+60)*(maxWidth+60)*100, glm::vec3(0.0,0.0,0.0));
    texCoords.resize((maxLength+60)*(maxWidth+60)*100, glm::vec2(0.0,0.0));
    normals.resize((maxLength+60)*(maxWidth+60)*100, glm::vec3(0.0,0.0,1.0));

    int ind = 0;

    // // Derrière skieur
    // for (int i = -10; i < 0; ++i) {
    //     for (int j = -30; j < maxWidth+30; ++j) {
    //         positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
    //         positions[ind+1] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
    //         positions[ind+2] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

    //         texCoords[ind] = glm::vec2(0.0,0.0);
    //         texCoords[ind+1] = glm::vec2(0.0,1.0);
    //         texCoords[ind+2] = glm::vec2(1.0,0.0);

    //         positions[ind+3] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
    //         positions[ind+4] = glm::vec3(float(i+1), float(j+1), perlin_noise(i+1,j+1));
    //         positions[ind+5] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

    //         texCoords[ind+3] = glm::vec2(0.0,1.0);
    //         texCoords[ind+4] = glm::vec2(1.0,1.0);
    //         texCoords[ind+5] = glm::vec2(1.0,0.0);

    //         ind += 6;
    //     }
    // }

    // Devant skieur
    for (int i = maxLength; i < maxLength+30; ++i) {
        for (int j = -30; j < maxWidth+30; ++j) {
            positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
            positions[ind+1] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+2] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind] = glm::vec2(0.0,0.0);
            texCoords[ind+1] = glm::vec2(0.0,1.0);
            texCoords[ind+2] = glm::vec2(1.0,0.0);

            positions[ind+3] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+4] = glm::vec3(float(i+1), float(j+1), perlin_noise(i+1,j+1));
            positions[ind+5] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind+3] = glm::vec2(0.0,1.0);
            texCoords[ind+4] = glm::vec2(1.0,1.0);
            texCoords[ind+5] = glm::vec2(1.0,0.0);

            ind += 6;
        }
    }

    // Côté droit
    for (int i = 0; i < maxLength; ++i) {
        for (int j = -30; j < 0; ++j) {
            positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
            positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
            positions[ind+1] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+2] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind] = glm::vec2(0.0,0.0);
            texCoords[ind+1] = glm::vec2(0.0,1.0);
            texCoords[ind+2] = glm::vec2(1.0,0.0);

            positions[ind+3] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+4] = glm::vec3(float(i+1), float(j+1), perlin_noise(i+1,j+1));
            positions[ind+5] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind+3] = glm::vec2(0.0,1.0);
            texCoords[ind+4] = glm::vec2(1.0,1.0);
            texCoords[ind+5] = glm::vec2(1.0,0.0);

            ind += 6;
        }
    }

    // Côté gauche
    for (int i = 0; i < maxLength; ++i) {
        for (int j = maxWidth; j < maxWidth+30; ++j) {
            positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
            positions[ind] = glm::vec3(float(i), float(j), perlin_noise(i,j));
            positions[ind+1] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+2] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind] = glm::vec2(0.0,0.0);
            texCoords[ind+1] = glm::vec2(0.0,1.0);
            texCoords[ind+2] = glm::vec2(1.0,0.0);

            positions[ind+3] = glm::vec3(float(i), float(j+1), perlin_noise(i,j+1));
            positions[ind+4] = glm::vec3(float(i+1), float(j+1), perlin_noise(i+1,j+1));
            positions[ind+5] = glm::vec3(float(i+1), float(j), perlin_noise(i+1,j));

            texCoords[ind+3] = glm::vec2(0.0,1.0);
            texCoords[ind+4] = glm::vec2(1.0,1.0);
            texCoords[ind+5] = glm::vec2(1.0,0.0);

            ind += 6;
        }
    }



    for (const glm::vec3& x : positions) {
        normals.push_back(glm::normalize(x));
    }
}

double perlin_noise(double x, double y)
{
    if (x == 0)
        if (y >= 0 && y <= 30)
            return 80;
    if (x == 200)
        return 0;
    if (y == 0)
        if (x >= 0 && x <= 200)
            return -0.4*x + 84;
    if (y == 30)
        if (x >= 0 && x <= 200)
            return -0.4*x + 84;

    double res = 50;
    double tempX,tempY;
    int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
    double unit = 1.0f/sqrt(2);
    double tmp,s,t,u,v,Cx,Cy,Li1,Li2;
    double gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};

    unsigned int perm[] =
       {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
        142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
        203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
        74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
        105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
        187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
        64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
        47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
        153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
        112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
        235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
        127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
        156,180};

    // Travailler en valeur absolue
    x = abs(x);
    y = abs(y);

    //Adapter pour la résolution
    x /= res;
    y /= res;

    //On récupère les positions de la grille associée à (x,y)
    x0 = (int)(x);
    y0 = (int)(y);

    //Masquage
    ii = x0 & 255;
    jj = y0 & 255;

    //Pour récupérer les vecteurs
    gi0 = perm[ii + perm[jj]] % 8;
    gi1 = perm[ii + 1 + perm[jj]] % 8;
    gi2 = perm[ii + perm[jj + 1]] % 8;
    gi3 = perm[ii + 1 + perm[jj + 1]] % 8;

    //on récupère les vecteurs et on pondère
    tempX = x-x0;
    tempY = y-y0;
    s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;

    tempX = x-(x0+1);
    tempY = y-y0;
    t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;

    tempX = x-x0;
    tempY = y-(y0+1);
    u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;

    tempX = x-(x0+1);
    tempY = y-(y0+1);
    v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;


    //Lissage
    tmp = x-x0;
    Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    Li1 = s + Cx*(t-s);
    Li2 = u + Cx*(v-u);

    tmp = y - y0;
    Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

    return ((Li1 + Cy*(Li2-Li1))+1)*0.5*(100-x0*x0);
}



void getUnitCylinder(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, const unsigned int &slices)
{
    size_t number_of_triangles = slices * 4;
    size_t number_of_vertices = number_of_triangles * 3;
    float angle_step = 2.0 * M_PI / double( slices );

    positions.resize(number_of_vertices, glm::vec3(0.0,0.0,0.0));
    normals.resize(number_of_vertices, glm::vec3(0.0,0.0,0.0));

    float previous_angle = (slices - 1) * angle_step;
    float angle = 0;
    float previous_sin = std::sin( previous_angle );
    float previous_cos = std::cos( previous_angle );
    float sin = 0;
    float cos = 1;
    for( size_t i = 0; i < slices;
            ++ i,
            previous_sin = sin, previous_cos = cos,
            angle += angle_step, cos = std::cos( angle ), sin = std::sin( angle) )
    {
        size_t voffset = 12 * i;
        positions[ voffset +  0 ] = glm::vec3{0,0,1};
        positions[ voffset +  1 ] = glm::vec3{previous_cos, previous_sin, 1};
        positions[ voffset +  2 ] = glm::vec3{cos, sin,1};

        positions[ voffset +  3 ] = glm::vec3{cos, sin,1};
        positions[ voffset +  4 ] = glm::vec3{previous_cos, previous_sin, 1};
        positions[ voffset +  5 ] = glm::vec3{previous_cos, previous_sin, 0};

        positions[ voffset +  6 ] = glm::vec3{cos, sin,1};
        positions[ voffset +  7 ] = glm::vec3{previous_cos, previous_sin, 0};
        positions[ voffset +  8 ] = glm::vec3{cos, sin,0};

        positions[ voffset +  9 ] = glm::vec3{cos, sin,0};
        positions[ voffset + 10 ] = glm::vec3{previous_cos, previous_sin, 0};
        positions[ voffset + 11 ] = glm::vec3{0, 0, 0}; //useless

        normals[ voffset +  0 ] = glm::vec3{0,0,1};
        normals[ voffset +  1 ] = glm::vec3{0,0,1};
        normals[ voffset +  2 ] = glm::vec3{0,0,1};

        normals[ voffset +  3 ] = glm::vec3{cos,sin,0};
        normals[ voffset +  4 ] = glm::vec3{previous_cos,previous_sin,0};
        normals[ voffset +  5 ] = glm::vec3{previous_cos,previous_sin,0};

        normals[ voffset +  6 ] = glm::vec3{cos,sin,0};
        normals[ voffset +  7 ] = glm::vec3{previous_cos,previous_sin,0};
        normals[ voffset +  8 ] = glm::vec3{cos,sin,0};

        normals[ voffset +  9 ] = glm::vec3{0,0,-1};
        normals[ voffset + 10 ] = glm::vec3{0,0,-1};
        normals[ voffset + 11 ] = glm::vec3{0,0,-1};


    }
}

void getUnitCylinderTex(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &texCoords,const unsigned int &slices)
{
    size_t number_of_triangles = slices * 4;
    size_t number_of_vertices = number_of_triangles * 3;
    float angle_step = 2.0 * M_PI / double( slices );

    positions.resize(number_of_vertices, glm::vec3(0.0,0.0,0.0));
    normals.resize(number_of_vertices, glm::vec3(0.0,0.0,0.0));
    texCoords.resize(number_of_vertices, glm::vec2(0.0,0.0));

    float previous_angle = (slices - 1) * angle_step;
    float angle = 0;
    float previous_sin = std::sin( previous_angle );
    float previous_cos = std::cos( previous_angle );
    float sin = 0;
    float cos = 1;
    float un = 1.0;
    float zero = 0.0;
    for( size_t i = 0; i < slices;
            ++ i,
            previous_sin = sin, previous_cos = cos,
            angle += angle_step, cos = std::cos( angle ), sin = std::sin( angle) )
    {
        size_t voffset = 12 * i;
        positions[ voffset +  0 ] = glm::vec3{0,0,1};
        positions[ voffset +  1 ] = glm::vec3{previous_cos, previous_sin, 1};
        positions[ voffset +  2 ] = glm::vec3{cos, sin,1};

        positions[ voffset +  3 ] = glm::vec3{cos, sin,1};
        positions[ voffset +  4 ] = glm::vec3{previous_cos, previous_sin, 1};
        positions[ voffset +  5 ] = glm::vec3{previous_cos, previous_sin, 0};

        positions[ voffset +  6 ] = glm::vec3{cos, sin,1};
        positions[ voffset +  7 ] = glm::vec3{previous_cos, previous_sin, 0};
        positions[ voffset +  8 ] = glm::vec3{cos, sin,0};

        positions[ voffset +  9 ] = glm::vec3{cos, sin,0};
        positions[ voffset + 10 ] = glm::vec3{previous_cos, previous_sin, 0};
        positions[ voffset + 11 ] = glm::vec3{0, 0, 0}; //useless

        normals[ voffset +  0 ] = glm::vec3{0,0,1};
        normals[ voffset +  1 ] = glm::vec3{0,0,1};
        normals[ voffset +  2 ] = glm::vec3{0,0,1};

        normals[ voffset +  3 ] = glm::vec3{cos,sin,0};
        normals[ voffset +  4 ] = glm::vec3{previous_cos,previous_sin,0};
        normals[ voffset +  5 ] = glm::vec3{previous_cos,previous_sin,0};

        normals[ voffset +  6 ] = glm::vec3{cos,sin,0};
        normals[ voffset +  7 ] = glm::vec3{previous_cos,previous_sin,0};
        normals[ voffset +  8 ] = glm::vec3{cos,sin,0};

        normals[ voffset +  9 ] = glm::vec3{0,0,-1};
        normals[ voffset + 10 ] = glm::vec3{0,0,-1};
        normals[ voffset + 11 ] = glm::vec3{0,0,-1};

        texCoords[ voffset + 0] = glm::vec2{zero,zero};
        texCoords[ voffset + 1] = glm::vec2{un,un};
        texCoords[ voffset + 2] = glm::vec2{zero,zero};

        texCoords[ voffset + 3] = glm::vec2{zero,zero};
        texCoords[ voffset + 4] = glm::vec2{un,un};
        texCoords[ voffset + 5] = glm::vec2{zero,zero};

        texCoords[ voffset + 6] = glm::vec2{zero,zero};
        texCoords[ voffset + 7] = glm::vec2{un,un};
        texCoords[ voffset + 8] = glm::vec2{zero,zero};

        texCoords[ voffset + 9] = glm::vec2{zero,zero};
        texCoords[ voffset + 10] = glm::vec2{un,un};
        texCoords[ voffset + 11] = glm::vec2{zero,zero};

        float transition = un;
        un = zero; 
        zero = transition;


    }
}

void getUnitSphere(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const unsigned int& strips, const unsigned int& slices)
{
    double radius=1.0;
    glm::vec3 center(0.0,0.0,0.0);

    unsigned int vertexNumber = slices*strips*6;
    positions.resize(vertexNumber);
    normals.resize(vertexNumber);

    for(int i=0; i<slices; ++i)
    {
        for(int j=0; j<strips; ++j)
        {
            double curr_theta = i*(2.0*M_PI/(double)slices);
            double curr_phi = j*(M_PI/(double)strips);

            double next_theta = (i+1)*(2.0*M_PI/(double)slices);
            double next_phi = (j+1)*(M_PI/(double)strips);

            std::array<glm::vec3,3> vTriangles;
            vTriangles[0] = center + glm::vec3(radius*cos(curr_theta)*sin(curr_phi), radius*sin(curr_theta)*sin(curr_phi), radius*cos(curr_phi));
            vTriangles[1] = center + glm::vec3(radius*cos(next_theta)*sin(curr_phi), radius*sin(next_theta)*sin(curr_phi), radius*cos(curr_phi));
            vTriangles[2] = center + glm::vec3(radius*cos(next_theta)*sin(next_phi), radius*sin(next_theta)*sin(next_phi), radius*cos(next_phi));

            positions[i*strips*6 + 6*j +0] = vTriangles[0];
            positions[i*strips*6 + 6*j +1] = vTriangles[1];
            positions[i*strips*6 + 6*j +2] = vTriangles[2];

            normals[i*strips*6 + 6*j +0] = glm::vec3(cos(curr_theta)*sin(curr_phi), sin(curr_theta)*sin(curr_phi), cos(curr_phi));
            normals[i*strips*6 + 6*j +1] = glm::vec3(cos(next_theta)*sin(curr_phi), sin(next_theta)*sin(curr_phi), cos(curr_phi));
            normals[i*strips*6 + 6*j +2] = glm::vec3(cos(next_theta)*sin(next_phi), sin(next_theta)*sin(next_phi), cos(next_phi));

            vTriangles[0] = center + glm::vec3(radius*cos(curr_theta)*sin(curr_phi), radius*sin(curr_theta)*sin(curr_phi), radius*cos(curr_phi));
            vTriangles[1] = center + glm::vec3(radius*cos(next_theta)*sin(next_phi), radius*sin(next_theta)*sin(next_phi), radius*cos(next_phi));
            vTriangles[2] = center + glm::vec3(radius*cos(curr_theta)*sin(next_phi), radius*sin(curr_theta)*sin(next_phi), radius*cos(next_phi));

            positions[i*strips*6 + 6*j +3] = vTriangles[0];
            positions[i*strips*6 + 6*j +4] = vTriangles[1];
            positions[i*strips*6 + 6*j +5] = vTriangles[2];

            normals[i*strips*6 + 6*j +3] = glm::vec3(cos(curr_theta)*sin(curr_phi), sin(curr_theta)*sin(curr_phi), cos(curr_phi));
            normals[i*strips*6 + 6*j +4] = glm::vec3(cos(next_theta)*sin(next_phi), sin(next_theta)*sin(next_phi), cos(next_phi));
            normals[i*strips*6 + 6*j +5] = glm::vec3(cos(curr_theta)*sin(next_phi), sin(curr_theta)*sin(next_phi), cos(next_phi));
        }
    }
}

void getTorus(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const float& a, const float& c, const unsigned int& strips, const unsigned int& slices)
{
    unsigned int vertexNumber = slices*strips*6;
    positions.resize(vertexNumber);
    normals.resize(vertexNumber);

    for(int i=0; i<strips; ++i)
    {
        for(int j=0; j<slices; ++j)
        {
            double curr_u = i*(2.0*M_PI/(double)strips);
            double curr_v = j*(2.0*M_PI/(double)slices);

            double next_u = (i+1)*(2.0*M_PI/(double)strips);
            double next_v = (j+1)*(2.0*M_PI/(double)slices);

            positions[i*strips*6 + 6*j +0] = glm::vec3((c+a*cos(curr_v))*cos(curr_u),
                    (c+a*cos(curr_v))*sin(curr_u),
                    a*sin(curr_v) );
            positions[i*strips*6 + 6*j +1] = glm::vec3((c+a*cos(curr_v))*cos(next_u),
                    (c+a*cos(curr_v))*sin(next_u),
                    a*sin(curr_v) );
            positions[i*strips*6 + 6*j +2] = glm::vec3((c+a*cos(next_v))*cos(next_u),
                    (c+a*cos(next_v))*sin(next_u),
                    a*sin(next_v) );

            normals[i*strips*6 + 6*j +0] = glm::vec3((cos(curr_v))*cos(curr_u),
                    (cos(curr_v))*sin(curr_u),
                    sin(curr_v) );
            normals[i*strips*6 + 6*j +1] = glm::vec3((cos(curr_v))*cos(next_u),
                    (cos(curr_v))*sin(next_u),
                    sin(curr_v) );
            normals[i*strips*6 + 6*j +2] = glm::vec3((cos(next_v))*cos(next_u),
                    (cos(next_v))*sin(next_u),
                    sin(next_v) );

            positions[i*strips*6 + 6*j +3] = glm::vec3((c+a*cos(curr_v))*cos(curr_u),
                    (c+a*cos(curr_v))*sin(curr_u),
                    a*sin(curr_v) );
            positions[i*strips*6 + 6*j +4] = glm::vec3((c+a*cos(next_v))*cos(next_u),
                    (c+a*cos(next_v))*sin(next_u),
                    a*sin(next_v) );
            positions[i*strips*6 + 6*j +5] = glm::vec3((c+a*cos(next_v))*cos(curr_u),
                    (c+a*cos(next_v))*sin(curr_u),
                    a*sin(next_v) );

            normals[i*strips*6 + 6*j +3] = glm::vec3((cos(curr_v))*cos(curr_u),
                    (cos(curr_v))*sin(curr_u),
                    sin(curr_v) );
            normals[i*strips*6 + 6*j +4] = glm::vec3((cos(next_v))*cos(next_u),
                    (cos(next_v))*sin(next_u),
                    sin(next_v) );
            normals[i*strips*6 + 6*j +5] = glm::vec3((cos(next_v))*cos(curr_u),
                    (cos(next_v))*sin(curr_u),
                    sin(next_v) );
        }
    }
}

void getUnitCone(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const unsigned int& strips, const unsigned int& slices)
{
    double height = 1.0;
    double radius=1.0;
    glm::vec3 center(0.0,0.0,0.0);
    int numberOfVertices = slices*strips*6 + slices*3;
    positions.resize(numberOfVertices);
    normals.resize(numberOfVertices);

    //Lateral surface
    for(int i=0; i<slices; ++i)
    {
        for(int j=0; j<strips; ++j)
        {
            double curr_theta = i*(2.0*M_PI/(double)slices);
            double curr_u = j*(height/(double)strips);
            double next_theta = (i+1)*(2.0*M_PI/(double)slices);
            double next_u = (j+1)*(height/(double)strips);
            double factor1 = (height-curr_u)/height;
            double factor2 = (height-next_u)/height;

            positions[i*strips*6 + 6*j +0] = center + glm::vec3(factor1*radius*cos(curr_theta),
                    factor1*radius*sin(curr_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +1] = center + glm::vec3(factor1*radius*cos(next_theta),
                    factor1*radius*sin(next_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +2] = center + glm::vec3(factor2*radius*cos(next_theta),
                    factor2*radius*sin(next_theta),
                    next_u);

            normals[i*strips*6 + 6*j +0] = glm::normalize(glm::vec3(cos(curr_theta),
                        sin(curr_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +1] = glm::normalize(glm::vec3(cos(next_theta),
                        sin(next_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +2] = glm::normalize(glm::vec3(cos(next_theta),
                        sin(next_theta),
                        next_u));

            positions[i*strips*6 + 6*j +3] = center + glm::vec3(factor1*radius*cos(curr_theta),
                    factor1*radius*sin(curr_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +4] = center + glm::vec3(factor2*radius*cos(next_theta),
                    factor2*radius*sin(next_theta),
                    next_u);
            positions[i*strips*6 + 6*j +5] = center + glm::vec3(factor2*radius*cos(curr_theta),
                    factor2*radius*sin(curr_theta),
                    next_u);

            normals[i*strips*6 + 6*j +3] = glm::normalize(glm::vec3(cos(curr_theta),
                        sin(curr_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +4] = glm::normalize(glm::vec3(cos(next_theta),
                        radius*sin(next_theta),
                        next_u));
            normals[i*strips*6 + 6*j +5] = glm::normalize(glm::vec3(cos(curr_theta),
                        radius*sin(curr_theta),
                        next_u));

        }
    }

    //Bottom faces
    unsigned int counter = slices*strips*6;
    for(int i=0; i<slices; ++i)
    {
        double curr_theta = i*(2.0*M_PI/(double)slices);
        double next_theta = (i+1)*(2.0*M_PI/(double)slices);
        double u_base = 0.0;

        positions[counter+3*i+0] = center + glm::vec3(0, 0, u_base );
        positions[counter+3*i+1] = center + glm::vec3(radius*cos(curr_theta), radius*sin(curr_theta), u_base);
        positions[counter+3*i+2] = center + glm::vec3(radius*cos(next_theta), radius*sin(next_theta), u_base);

        normals[counter+3*i+0] = glm::vec3(0, 0, -1);
        normals[counter+3*i+1] = glm::vec3(0, 0, -1);
        normals[counter+3*i+2] = glm::vec3(0, 0, -1);
    }

}

void getUnitConeTex(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, const unsigned int& strips, const unsigned int& slices)
{
    double height = 1.0;
    double radius=1.0;
    glm::vec3 center(0.0,0.0,0.0);
    int numberOfVertices = slices*strips*6 + slices*3;
    positions.resize(numberOfVertices);
    normals.resize(numberOfVertices);
    texCoords.resize(numberOfVertices);

    float zero = 0.0;
    float un = 1.0;

    //Lateral surface
    for(int i=0; i<slices; ++i)
    {
        for(int j=0; j<strips; ++j)
        {
            double curr_theta = i*(2.0*M_PI/(double)slices);
            double curr_u = j*(height/(double)strips);
            double next_theta = (i+1)*(2.0*M_PI/(double)slices);
            double next_u = (j+1)*(height/(double)strips);
            double factor1 = (height-curr_u)/height;
            double factor2 = (height-next_u)/height;

            positions[i*strips*6 + 6*j +0] = center + glm::vec3(factor1*radius*cos(curr_theta),
                    factor1*radius*sin(curr_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +1] = center + glm::vec3(factor1*radius*cos(next_theta),
                    factor1*radius*sin(next_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +2] = center + glm::vec3(factor2*radius*cos(next_theta),
                    factor2*radius*sin(next_theta),
                    next_u);

            normals[i*strips*6 + 6*j +0] = glm::normalize(glm::vec3(cos(curr_theta),
                        sin(curr_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +1] = glm::normalize(glm::vec3(cos(next_theta),
                        sin(next_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +2] = glm::normalize(glm::vec3(cos(next_theta),
                        sin(next_theta),
                        next_u));

            texCoords[i*strips*6 + 6*j +0] = glm::vec2{zero,zero};
            texCoords[i*strips*6 + 6*j +1] = glm::vec2{un,un};
            texCoords[i*strips*6 + 6*j +2] = glm::vec2{zero,zero};


            positions[i*strips*6 + 6*j +3] = center + glm::vec3(factor1*radius*cos(curr_theta),
                    factor1*radius*sin(curr_theta),
                    curr_u);
            positions[i*strips*6 + 6*j +4] = center + glm::vec3(factor2*radius*cos(next_theta),
                    factor2*radius*sin(next_theta),
                    next_u);
            positions[i*strips*6 + 6*j +5] = center + glm::vec3(factor2*radius*cos(curr_theta),
                    factor2*radius*sin(curr_theta),
                    next_u);

            normals[i*strips*6 + 6*j +3] = glm::normalize(glm::vec3(cos(curr_theta),
                        sin(curr_theta),
                        curr_u));
            normals[i*strips*6 + 6*j +4] = glm::normalize(glm::vec3(cos(next_theta),
                        radius*sin(next_theta),
                        next_u));
            normals[i*strips*6 + 6*j +5] = glm::normalize(glm::vec3(cos(curr_theta),
                        radius*sin(curr_theta),
                        next_u));

            texCoords[i*strips*6 + 6*j +3] = glm::vec2{zero,zero};
            texCoords[i*strips*6 + 6*j +4] = glm::vec2{un,un};
            texCoords[i*strips*6 + 6*j +5] = glm::vec2{zero,zero};

        }
    }

    //Bottom faces
    unsigned int counter = slices*strips*6;
    for(int i=0; i<slices; ++i)
    {
        double curr_theta = i*(2.0*M_PI/(double)slices);
        double next_theta = (i+1)*(2.0*M_PI/(double)slices);
        double u_base = 0.0;

        positions[counter+3*i+0] = center + glm::vec3(0, 0, u_base );
        positions[counter+3*i+1] = center + glm::vec3(radius*cos(curr_theta), radius*sin(curr_theta), u_base);
        positions[counter+3*i+2] = center + glm::vec3(radius*cos(next_theta), radius*sin(next_theta), u_base);

        normals[counter+3*i+0] = glm::vec3(0, 0, -1);
        normals[counter+3*i+1] = glm::vec3(0, 0, -1);
        normals[counter+3*i+2] = glm::vec3(0, 0, -1);

        texCoords[counter + 3*i +0] = glm::vec2{zero,zero};
        texCoords[counter + 3*i +1] = glm::vec2{un,un};
        texCoords[counter + 3*i +2] = glm::vec2{zero,zero};
    }

}
