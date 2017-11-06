#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"

#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"

//#include "../include/SnowRenderable.hpp"

#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderable.hpp"
#include "../include/dynamics_rendering/ParticleListRenderable.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringListRenderable.hpp"
#include "../include/dynamics_rendering/ControlledForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/QuadRenderable.hpp"


void initialize_snow_scene(Viewer& viewer)
{
    ShaderProgramPtr flatShader =
        std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                        "../shaders/flatFragment.glsl");

    ShaderProgramPtr snowShader =
        std::make_shared<ShaderProgram>("../shaders/SnowVertex.glsl",
                                        "../shaders/SnowFragment.glsl");

    viewer.addShaderProgram(flatShader);
    viewer.addShaderProgram(snowShader);

    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    // Add snow in front of the camera
    // SnowRenderablePtr snow = std::make_shared<SnowRenderable>(snowShader);
    // snow->setParentTransform(glm::translate(glm::mat4(1), glm::vec3(1.0,1.0,0.0)));
    // viewer.addRenderable(snow);


    //Finally, run the animation
    viewer.startAnimation();
}

