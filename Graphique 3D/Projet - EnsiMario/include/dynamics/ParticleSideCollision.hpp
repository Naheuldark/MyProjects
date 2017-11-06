#ifndef PARTICLE_SIDE_COLLISION_HPP
#define PARTICLE_SIDE_COLLISION_HPP

#include "Collision.hpp"
#include "Particle.hpp"

/**@brief Implement the resolution of a collision event between two particles.
 *
 * Implementation of the resolution of a collision between two particles.
 */
class ParticleSideCollision : public Collision
{
public:
    /**@brief Build a new collision event between a particle and one side of the slope.
     *
     * Build a collision event between a particle and one side of the slope.
     * @param particle The colliding particle.
     * @param side The colliding side.
     * @param restitution The restitution factor of the collision.
     */
    ParticleSideCollision(ParticlePtr particle, bool side, float restitution);

    virtual ~ParticleSideCollision();

private:
    void do_solveCollision();

    ParticlePtr m_p;
    bool m_side;
};

typedef std::shared_ptr<ParticleSideCollision> ParticleSideCollisionPtr;

bool testParticleSide(const ParticlePtr& p, bool side);

#endif //PARTICLE_SIDE_COLLISION_HPP
