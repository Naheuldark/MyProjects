#ifndef LIGHTED_CUBE_RENDERABLE_HPP
#define LIGHTED_CUBE_RENDERABLE_HPP

#include "./../lighting/Materiable.hpp"
#include "./../../include/CubeRenderable.hpp"

class LightedCubeRenderable : public CubeRenderable, public Materiable
{
public:
    ~LightedCubeRenderable();
    LightedCubeRenderable(ShaderProgramPtr program, const MaterialPtr& material);

protected:
    void do_draw();
    void do_animate(float time);
};

typedef std::shared_ptr<LightedCubeRenderable> LightedCubeRenderablePtr;

#endif
