#include "./../../include/dynamics/SpringForceField.hpp"

SpringForceField::SpringForceField(const ParticlePtr p1, const ParticlePtr p2,
                                   float stiffness, float equilibriumLength,
                                   float damping) :
    m_p1(p1),
    m_p2(p2),
    m_stiffness(stiffness),
    m_equilibriumLength(equilibriumLength),
    m_damping(damping)
{}

void SpringForceField::do_addForce()
{
    //TODO: Implement a damped spring
    //Functions to use:
    //glm::length( vec3 ): Return the length of a vector
    //glm::normalize( vec3 ): Return the normalization of a vector
    //Particle::getVelocity(), Particle::getForce(), Particle::setForce()
    //
    //Nb:   Compute force ONLY IF the displacement length is above std::numeric_limits<float>::epsilon()
    //      Otherwise the computation is useless

    float dx = glm::length(getParticle1()->getPosition() - getParticle2()->getPosition());

    glm::vec3 force = glm::vec3(0,0,0);
    float gdamping = 5;
    if (dx > std::numeric_limits<float>::epsilon()) {
        force -= m_stiffness * (glm::length(m_p1->getPosition() - m_p2->getPosition()) - m_equilibriumLength) * glm::normalize(m_p1->getPosition() - m_p2->getPosition());
        force -= m_damping * (dot(getParticle1()->getVelocity() - getParticle2()->getVelocity(),glm::normalize(m_p1->getPosition() - m_p2->getPosition()))) * glm::normalize(m_p1->getPosition() - m_p2->getPosition());
    }
     m_p1->incrForce(force - gdamping*m_p1->getVelocity());
     m_p2->incrForce(-force - gdamping*m_p2->getVelocity());
}

ParticlePtr SpringForceField::getParticle1() const
{
    return m_p1;
}

ParticlePtr SpringForceField::getParticle2() const
{
    return m_p2;
}
