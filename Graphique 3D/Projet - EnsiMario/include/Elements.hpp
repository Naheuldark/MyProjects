#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/lighting/LightedMeshRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/texturing/TexturedCubeRenderable.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"


#include "../include/keyframes/KeyframedCylinderRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"

#include <iostream>
#include <iomanip>

std::shared_ptr<HierarchicalRenderable> buildASmallTree (ShaderProgramPtr phongShader, ShaderProgramPtr texShader);
std::shared_ptr<HierarchicalRenderable> buildATallTree (ShaderProgramPtr phongShader, ShaderProgramPtr texShader);
std::shared_ptr<HierarchicalRenderable> buildASnowman (ShaderProgramPtr phongShader);
std::shared_ptr<HierarchicalRenderable> buildAnAdPanel (ShaderProgramPtr phongShader, ShaderProgramPtr texShader, int who);



#endif