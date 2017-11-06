#ifndef SKIER_CHARACTER_H
#define SKIER_CHARACTER_H

#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/MeshRenderable.hpp"
#include "../include/CylinderRenderable.hpp"
#include "../include/ConeRenderable.hpp"
#include "../include/CubeRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/keyframes/KeyframedCylinderRenderable.hpp"
#include "../include/texturing/TexturedCylinderRenderable.hpp"
#include "../include/texturing/TexturedConeRenderable.hpp"
#include "../include/texturing/TexturedCubeRenderable.hpp"
#include "../include/lighting/LightedCubeRenderable.hpp"

    /**@brief Instantiate a textured skier.
     *
     * Construct a new skier.
     * @param phongShader The phong shader.
     * @param texShader The texShader.
     */
std::shared_ptr<HierarchicalRenderable> buildASkier (ShaderProgramPtr phongShader, ShaderProgramPtr texShader);

#endif