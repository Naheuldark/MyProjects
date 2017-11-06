#include "../../include/dynamics/Plane.hpp"
#include <glm/gtc/matrix_access.hpp>


Plane::Plane(const glm::vec3& normal, const glm::vec3& point)
    : m_n{normal}, m_d{dot(normal, point)}
{
}

Plane::Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const float& longueur, const float& milieu)
{
    m_n = glm::normalize(glm::cross(b-a, c-a));
    m_d = glm::dot(m_n, a);
    m_longueur = longueur;
    m_milieu = milieu;
}

Plane::~Plane()
{
}

glm::vec3 Plane::projectOnPlane(const glm::vec3& p)
{
    glm::vec3 planePoint = m_d*m_n;
    glm::vec3 v = p-planePoint;
    float dist = glm::dot(v,m_n);
    glm::vec3 projection = p - dist*m_n;
    return projection;
}

void Plane::setDistanceToOrigin(const float& d)
{
    m_d = d;
}

const float& Plane::distanceToOrigin() const
{
    return m_d;
}

void Plane::setNormal(const glm::vec3& n)
{
    m_n = n;
}

const glm::vec3& Plane::normal() const
{
    return m_n;
}


const float& Plane::getLongueur() const {
    return m_longueur;
}

const float& Plane::getMilieu() const {
    return m_milieu;
}