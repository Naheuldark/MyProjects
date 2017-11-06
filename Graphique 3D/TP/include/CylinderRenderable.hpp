#ifndef CYLINDER_RENDERABLE_HPP
#define CYLINDER_RENDERABLE_HPP

#include "HierarchicalRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class CylinderRenderable : public HierarchicalRenderable
{
    public:
        ~CylinderRenderable();
        CylinderRenderable(ShaderProgramPtr program, bool normalPerVertex = true, unsigned int nbSlices = 20);

    protected:
        void do_draw();
        void do_animate(float time);

    private:
        bool m_normalPerVertex;
        void buildNormalPerVertex(unsigned int nbSlices);
        void buildNormalPerFace(unsigned int nbSlices);

        std::vector< glm::vec3 > m_positions;
        std::vector< glm::vec4 > m_colors;
        std::vector< glm::vec3 > m_normals;
        std::vector<glm::ivec3> m_indices;

        unsigned int m_pBuffer;
        unsigned int m_cBuffer;
        unsigned int m_nBuffer;
        unsigned int m_iBuffer;
};

typedef std::shared_ptr<CylinderRenderable> CylinderRenderablePtr;

#endif
