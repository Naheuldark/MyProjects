#include "./../../include/dynamics/ParticleSkier.hpp"


ParticleSkier::ParticleSkier(const glm::vec3 &position, const glm::vec3 &velocity,
                   const float &mass, const float &radius, const float& angleT, const float& angleP)
    : Particle(position, velocity,mass,radius), m_initialAngleT(angleT), m_initialAngleP(angleP),m_angleTheta(angleT), m_anglePhi(angleP)
{
    if (m_anglePhi == 0){
        m_normal = glm::vec3(0,0,1);
    } else {
        m_normal = glm::vec3(sin(m_anglePhi),sin(m_anglePhi),cos(m_anglePhi));
    }

}

ParticleSkier::~ParticleSkier()
{}


float ParticleSkier::getAngleTheta() const
{
    return m_angleTheta;
}

float ParticleSkier::getAnglePhi() const
{
    return m_anglePhi;
}

const glm::vec3 & ParticleSkier::getNormal() const
{
    return m_normal;
}

void ParticleSkier::setAngleTheta(const float &angle)
{
    m_angleTheta = angle;
}

void ParticleSkier::setAnglePhi(const float &angle)
{
    m_anglePhi = angle;
}

void ParticleSkier::setNormal(const glm::vec3& normal)
{
    m_normal = normal;
}

void ParticleSkier::incrAngleTheta(const float& angle)
{
    m_angleTheta +=angle;
}

void ParticleSkier::incrAnglePhi(const float& angle)
{
    m_anglePhi +=angle;
}

bool ParticleSkier::isParticleSkier(){
    return true;
}

void ParticleSkier::restart()
{
    m_position = m_initialPosition;
    m_velocity = m_initialVelocity;
    m_angleTheta = m_initialAngleT;
    m_anglePhi = m_initialAngleP;

}

std::ostream& operator<<(std::ostream& os, const ParticleSkierPtr& p)
{
    const glm::vec3& x = p->getPosition();
    const glm::vec3& v = p->getVelocity();

    os << "pos (" << x[0] << ", " << x[1] << ", " << x[2] << ")";
    os << " ; ";
    os << "vel (" << v[0] << ", " << v[1] << ", " << v[2] << ")";

    return os;
}
