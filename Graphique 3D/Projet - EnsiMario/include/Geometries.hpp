#ifndef GEOMETRIES_HPP
#define GEOMETRIES_HPP

/**@file
 * @brief Some useful functions to ease the development.
 */

// #include "GeometricTransformation.hpp"
// #include "Sphere.hpp"
// #include "Plane.hpp"

#include <vector>
#include <utility>
#include <glm/glm.hpp>


void getUnitCube(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords);
void getUnitIndexedCube(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::ivec3>& indices);

void getUnitCylinder(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const unsigned int& slices);
void getUnitCylinderTex(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords, const unsigned int& slices);

void getUnitPlane(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords);

void getUnitMap(int maxWidth, int maxLength, int maxHeight, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords);
float height(float i, float j, float maxHeight, float maxLength, int maxWidth);

void getMountainsSurrounding(int maxWidth, int maxLength, int maxHeight, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords);
double perlin_noise(double x, double y);

void getUnitSphere(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const unsigned int& strips, const unsigned int& slices);
void getTorus(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const float& a, const float& c, const unsigned int& strips, const unsigned int& slices);
void getUnitCone(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, const unsigned int &strips, const unsigned int& slices);
void getUnitConeTex(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2> &texCoords, const unsigned int &strips, const unsigned int& slices);

#endif // GEOMETRIES
