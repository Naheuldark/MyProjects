#include "./../../include/dynamics_rendering/ParticleRenderableSkier.hpp"
#include "./../../include/gl_helper.hpp"
#include "./../../include/log.hpp"
#include "./../../include/Utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "./../../include/dynamics/ParticleSkier.hpp"

ParticleRenderableSkier::~ParticleRenderableSkier()
{
}

ParticleRenderableSkier::ParticleRenderableSkier(ShaderProgramPtr shaderProgram, ParticlePtr particle,Viewer* viewer, HierarchicalRenderablePtr start) :
ParticleRenderable(shaderProgram, particle), m_viewer(viewer), m_start(start)
{
    ecartX = getParticle()->getPosition().x - (*m_viewer).getCamera().getPosition().x;
    ecartY = getParticle()->getPosition().y - (*m_viewer).getCamera().getPosition().y;
    ecartZ = getParticle()->getPosition().z - (*m_viewer).getCamera().getPosition().z;
}

void ParticleRenderableSkier::do_animate(float time)
{
    const glm::vec3& pPosition = getParticle()->getPosition();
    const glm::vec3& cPosition = (*m_viewer).getCamera().getPosition();
    glm::vec3 positionCameraTranslate = cPosition;
    if ((pPosition.x != cPosition.x + ecartX) || (pPosition.y != cPosition.y + ecartY) || (pPosition.z != cPosition.z + ecartZ) ){
        float newX = pPosition.x - ecartX;
        float newY = pPosition.y- ecartY;
        float newZ = pPosition.z- 2*ecartZ;
        positionCameraTranslate = glm::vec3(newX,newY,newZ);
        
        }
    (*m_viewer).getCamera().setPosition(positionCameraTranslate);

    if (pPosition.x > 185)
        m_viewer->stopChrono();


    if (pPosition.x > 5.1 && pPosition.x < 5.3) {
        m_viewer->rmRenderable(m_start);
        m_viewer->resetChrono();
    }
}
