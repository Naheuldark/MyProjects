#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"
#include "../include/Elements.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/lighting/LightedMeshRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"


#include "../include/keyframes/KeyframedCylinderRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"

#include <iostream>
#include <iomanip>


void initialize_tree_scene(Viewer& viewer)
{
    // Shaders
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(
        "../shaders/flatVertex.glsl", "../shaders/flatFragment.glsl");
    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
        "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");
    
    ShaderProgramPtr texShader
        = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                          "../shaders/textureFragment.glsl");

    viewer.addShaderProgram(flatShader);
    viewer.addShaderProgram(phongShader);    
    viewer.addShaderProgram(texShader);

    // Frame
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    // Define a directional light for the whole scene
    glm::vec3 lightDirection = glm::normalize(glm::vec3(0.0, -1.0, -1.0));
    glm::vec3 ghostWhite(248.0/255, 248.0/255, 1.0);
    DirectionalLightPtr directionalLight =
        std::make_shared<DirectionalLight>(lightDirection, ghostWhite, ghostWhite, ghostWhite);
    viewer.setDirectionalLight(directionalLight);
    // Add a renderable to display the light and control it via mouse/key event
    glm::vec3 lightPosition(0.0, 5.0, 8.0);
    DirectionalLightRenderablePtr directionalLightRenderable
        = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
    glm::mat4 localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.5));
    directionalLightRenderable->setLocalTransform(localTransformation);
    viewer.addRenderable(directionalLightRenderable);
    
    std::shared_ptr<HierarchicalRenderable> smalltree = buildASmallTree(phongShader, texShader);
    std::shared_ptr<HierarchicalRenderable> talltree = buildATallTree(phongShader, texShader);

    viewer.addRenderable(smalltree);
    talltree->setParentTransform(glm::translate(glm::mat4(), glm::vec3(5,0,0)));
    viewer.addRenderable(talltree);

    // "Let's go !" - Luigi
    viewer.setAnimationLoop(true, 2.0);
    viewer.startAnimation();
}
