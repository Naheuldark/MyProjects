#ifndef CONE_RENDERABLE_HPP
#define CONE_RENDERABLE_HPP

#include "HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class ConeRenderable : public HierarchicalRenderable
{
    public:
        ~ConeRenderable();
        ConeRenderable( ShaderProgramPtr program );

    protected:
        void do_draw();
        void do_animate(float time);

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec4> m_colors;
        std::vector< glm::ivec3 > m_indices;

        unsigned int m_pBuffer;
        unsigned int m_cBuffer;
        unsigned int m_iBuffer;
};

typedef std::shared_ptr<ConeRenderable> ConeRenderablePtr;

#endif
