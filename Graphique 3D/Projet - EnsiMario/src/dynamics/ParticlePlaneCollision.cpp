#include "./../../include/dynamics/ParticlePlaneCollision.hpp"

ParticlePlaneCollision::ParticlePlaneCollision(ParticlePtr particle, PlanePtr plane, float restitution) :
    Collision(restitution)
{
    m_particle = particle;
    m_plane = plane;
}

ParticlePlaneCollision::~ParticlePlaneCollision()
{}

void ParticlePlaneCollision::do_solveCollision(){
    //Don't process fixed particles (ground plane is assumed fixed)
    if (m_particle->isFixed())
        return;

    //TODO: Solve ParticlePlane collisions,
    // update particle position and velocity after collision
    //
    //Functions to use:
    //glm::dot(v1, v2): Return the dot product of two vector.
    //Plane::distanceToOrigin(): Return the distance to origin from the plane
    //Plane::normal(): Return the normal of the plane
    //Particle::getRadius(), Particle::getPosition(), Particle::getVelocity(), Particle::setPosition(), Particle::setVelocity()

    float d2plane = std::abs(glm::dot(m_particle->getPosition(), m_plane->normal()) - m_plane->distanceToOrigin());
    if (testParticlePlane(m_particle, m_plane)) {
        m_particle->setPosition(m_particle->getPosition() - (d2plane - m_particle->getRadius()) * m_plane->normal());
        m_particle->setVelocity(m_particle->getVelocity() -( 1.0f + m_restitution) * glm::dot(m_particle->getVelocity(), m_plane->normal()) * m_plane->normal());
    }

    float absProdScalaire = glm::abs(glm::dot(m_particle->getNormal(), m_plane->normal()));
    float multLength = glm::length(m_particle->getNormal()) * glm::length(m_plane->normal());
    if(absProdScalaire!= multLength){

      // Othogonal case 
      if (absProdScalaire == 0){
         m_particle->setAnglePhi(M_PI/4);
         m_particle->setNormal(glm::vec3(sin(m_particle->getAnglePhi()),sin(m_particle->getAnglePhi()),cos(m_particle->getAnglePhi())));

         // other cases 
       } else {
        float angle = acos(absProdScalaire/multLength);
        m_particle->setAnglePhi(angle);
        m_particle->setNormal(glm::vec3(sin(m_particle->getAnglePhi()),sin(m_particle->getAnglePhi()),cos(m_particle->getAnglePhi())));
       }
     
    }
}



bool testParticlePlane(const ParticlePtr &particle, const PlanePtr &plane)
{
    /* Equation of a plane passing through A and normal to n:
   * dot( p - A, n ) = dot( p, n ) - dot( A, n ) = 0
   * dot( A, n ) is stored in the "distanceToOrigin" of the plane.
   *
   * Equation of a particle of radius r centered in c:
   * dot( p - c, p - c ) = r²
   *
   * distance( plane, particle )
   *   = min( distance( plane, c ) - r, 0 )              //definition
   *   = min( abs( dot( c - A, n ) ) - r, 0 )
   *   = min( abs( dot( c, n ) - dot( A, n ) ) - r, 0 )
   *
   * So, there is intersection if distance( plane, particle ) = 0
   * <=> abs( dot( c, n ) - dot( A, n ) ) - r <= 0
   * <=> abs( dot( c, n ) - dot( A, n ) ) <= r
   */

    //TODO: Test collision between particle and plane
    //Functions to use:
    //glm::dot(v1, v2): Return the dot product of two vector.
    //Plane::distanceToOrigin(): Return the distance to origin from the plane
    //Plane::normal(): Return the normal of the plane
    //Particle::getRadius(), Particle::getPosition()

    if (plane -> getLongueur() != 0 && (particle->getPosition()[0] < (plane->getMilieu() - plane->getLongueur()/2))) 
      return false;

    if (plane -> getLongueur() != 0 && (particle->getPosition()[0] > (plane->getMilieu() + plane->getLongueur()/2)))
      return false;

    float d2plane = std::abs(glm::dot(particle->getPosition(), plane->normal()) - plane->distanceToOrigin());
    return (d2plane <= particle->getRadius());
}
