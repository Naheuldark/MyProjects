#include "./../../include/dynamics/ParticleSideCollision.hpp"
#include <glm/gtx/norm.hpp>

ParticleSideCollision::ParticleSideCollision(ParticlePtr particle1, bool side, float restitution) :
    Collision(restitution)
{
    m_p = particle1;
    m_side = side;
}

ParticleSideCollision::~ParticleSideCollision()
{
}

void ParticleSideCollision::do_solveCollision()
{
    int width = 30;
    int length = 200;
    int maxHeight = 80;
    int topwidth = 10;


    if (m_p->isFixed())
        return;

    float x = m_p -> getPosition()[0];
    float y = m_p -> getPosition()[1];
    float z = m_p -> getPosition()[2];
    float d2plane;

    if (testParticleSide(m_p, m_side)) {
        if (m_side) {
            d2plane = std::abs(y - (width - 17*sin(20*x/length)*sin(20*x/length)-1));
            m_p->setPosition(glm::vec3(x, y + d2plane - m_p->getRadius(), z));
        }
        if (!m_side) {
            d2plane = std::abs(y - (17*cos(20*x/length)*cos(20*x/length)+2));
            m_p->setPosition(glm::vec3(x, y - d2plane + m_p->getRadius(), z));
        }
            m_p->setVelocity(glm::vec3(-0.5*m_p->getVelocity()[0], 0.5* m_p->getVelocity()[1], m_p->getVelocity()[2]));
    }
    

}


bool testParticleSide(const ParticlePtr &p1, const bool side)
{

    float x = p1->getPosition()[0];
    float y;
    int width = 30;
    int length = 200;
    int maxHeight = 80;
    int topwidth = 10;

    if (x <= 10)
        return false;

    if (side) {
        y = p1 -> getPosition()[1] + p1 -> getRadius();
        return (y >= width - 17*sin(20*x/length)*sin(20*x/length)-1);

    }

    if (!side) {
        y = p1 -> getPosition()[1] - p1 -> getRadius();
        return (y <= 17*cos(20*x/length)*cos(20*x/length) +2);

    }

}
