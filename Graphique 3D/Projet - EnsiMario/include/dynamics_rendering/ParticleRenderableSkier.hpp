#ifndef PARTICLE_RENDERABLE_SKIER_HPP
#define PARTICLE_RENDERABLE__SKIER_HPP

#include "ParticleRenderable.hpp"
#include "../dynamics/Particle.hpp"
#include "../Viewer.hpp"

#include <vector>
#include <glm/glm.hpp>

/**@brief Render a particle to the screen.
 *
 * Render a particle to the screen. Since a particle is modeled by
 * a ball, this renderable simply render the corresponding ball. If
 * you have more than one renderable, have a look to ParticleListRenderable.
 */
class ParticleRenderableSkier : public ParticleRenderable
{
    public:
        /**@brief Build a particle renderable.
         *
         * Build a renderable to render a particle.
         * @param program The shader program used to render the particle.
         * @param particle The particle to render.
         */
        ParticleRenderableSkier(ShaderProgramPtr program, ParticlePtr particle, Viewer* viewer, HierarchicalRenderablePtr start);

        virtual ~ParticleRenderableSkier();

    private:
        void do_animate(float time);

        Viewer* m_viewer;
        HierarchicalRenderablePtr m_start;

        float ecartX;
        float ecartY;
        float ecartZ;
};

typedef std::shared_ptr<ParticleRenderableSkier> ParticleRenderableSkierPtr;

#endif //PARTICLE_RENDERABLE__SKIER_HPP
