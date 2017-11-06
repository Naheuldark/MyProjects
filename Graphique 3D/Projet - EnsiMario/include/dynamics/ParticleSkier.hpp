#ifndef ParticleSkier_HPP
#define ParticleSkier_HPP

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include "Particle.hpp"

/**@brief Represent a ParticleSkier as a moving ball.
 *
 * This class is used to model ParticleSkiers in a dynamic system.
 * Such a ParticleSkier is seen as a ball with a mass, a velocity and
 * a position. This ball is affected by forces that will change
 * both its position and its velocity. This ball can be fixed,
 * making its position constant and its velocity null.
 */
class ParticleSkier : public Particle
{
public:
    /**@brief Instantiate a dynamic ParticleSkier.
     *
     * Construct a new ParticleSkier, represented as a moving ball.
     * The initial position and velocity are saved in order to be
     * restored when the simulation restarts.
     *
     * @param position The initial position.
     * @param velocity The initial speed.
     * @param mass The ParticleSkier mass.
     * @param radius The ParticleSkier radius.
     */
    ParticleSkier(const glm::vec3& position, const glm::vec3& velocity,
            const float& mass, const float& radius, const float& angleT, const float& angleP );
    virtual ~ParticleSkier();

    /**@brief Access to this particle's angleTheta.
     *
     * Get the angleTheta of this particle.
     * @return The particle's angleTheta.
     */
    float getAngleTheta() const;

    /**@brief Access to this particle's anglePhi.
     *
     * Get the anglePhi of this particle.
     * @return The particle's anglePhi.
     */
    float getAnglePhi() const;

    /**@brief Access to this particle's normal.
     *
     * Get the normal of this particle.
     * @return The particle's normal.
     */
    const glm::vec3 & getNormal() const;

    /**@brief Set the particle's angleTheta.
     *
     * Set the angleTheta of this particle.
     * @param angle The new angleTheta of this particle.
     */
    void setAngleTheta(const float &angle);

    /**@brief Set the particle's anglePhi.
     *
     * Set the anglePhi of this particle.
     * @param angle The new anglePhi of this particle.
     */
    void setAnglePhi(const float &angle);

    /**@brief Set the particle's normal.
     *
     * Set the normal of this particle.
     * @param normal The new normal of this particle.
     */
    void setNormal(const glm::vec3& normal);

    /**@brief Increment the particle's angleTheta.
     *
     * Increment the angleTheta this particle.
     * @param angle The angle to add to this particle's angleTheta,
     * i.e. m_angleTheta += angle.
     */
    void incrAngleTheta(const float& angle);

    /**@brief Increment the particle's anglePhi.
     *
     * Increment the anglePhi this particle.
     * @param angle The angle to add to this particle's anglePhi,
     * i.e. m_anglePhi += angle.
     */
    void incrAnglePhi(const float& angle);

    /**@brief Get the particle's isParticleSkier flag.
     *
     * Get the isParticleSkier flag of this particle.
     */
    bool isParticleSkier();

    /**@brief Restart the particle.
     *
     * Set the particle's position, velocity, angleTheta and anglePhi to their initial values.
     */
    void restart();
  

private:
    const float m_initialAngleT;

    const float m_initialAngleP;

    glm::vec3 m_normal;

    float m_angleTheta;

    float m_anglePhi;
};

typedef std::shared_ptr<ParticleSkier> ParticleSkierPtr;

/**
 * \brief output stream operator, as non-member
 */
std::ostream& operator<<(std::ostream& os, const ParticleSkierPtr& p);

#endif
