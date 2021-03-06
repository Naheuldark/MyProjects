#ifndef CUBE_RENDERABLE_HPP
#define CUBE_RENDERABLE_HPP

#include "HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class CubeRenderable : public HierarchicalRenderable
{
    public:
        ~CubeRenderable();
        CubeRenderable();
        CubeRenderable(ShaderProgramPtr program);

    protected:
        void do_draw();
        void do_animate(float time);

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec4> m_colors;
        std::vector<glm::vec3> m_normals;

        unsigned int m_pBuffer;
        unsigned int m_cBuffer;
        unsigned int m_nBuffer;
};

typedef std::shared_ptr<CubeRenderable> CubeRenderablePtr;

#endif
