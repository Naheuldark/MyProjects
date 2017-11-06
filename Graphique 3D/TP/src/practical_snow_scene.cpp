#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"

#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"

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
    //Set up a shader and add a 3D frame.
    ShaderProgramPtr flatShader =
        std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                        "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);

    //Initialize a dynamic system (Solver, Time step, Restitution coefficient)
    DynamicSystemPtr system = std::make_shared<DynamicSystem>();
    EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
    system->setSolver(solver);
    system->setDt(0.01);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep()in the animate() function
    //It also handles some of the key/mouse events
    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);

    unsigned int scene_to_load = 71;

    //Position the camera
    viewer.getCamera().setViewMatrix(
        glm::lookAt(glm::vec3(0, -4, 0), glm::vec3(0,0,0), glm::vec3(0,0,1)) );


    //We diminish the time step to be able to see what happens before particles go too far
    system->setDt(5e-4);

    //Deactivate collision detection
    system->setCollisionsDetection(false);

    glm::vec3 px,pv;
    float pm, pr;
    //Two particles with gravity and damping
    {
        //Initialize each particle with its position, velocity, mass and radius
        //and add it to the system
        px = glm::vec3(0.0, 0.0, 1.0);
        pv = glm::vec3(3.0, 0.0, 0.0);
        pr = 0.1;
        pm = 1.0;
        ParticlePtr particle1 = std::make_shared<Particle>(px, pv, pm, pr);
        system->addParticle(particle1);

        px = glm::vec3(0.0, 0.0, 1.5);
        pv = glm::vec3(6.0, 0.0, 0.0);
        pr = 0.1;
        pm = 1.0;
        ParticlePtr particle2 = std::make_shared<Particle>(px, pv, pm, pr);
        system->addParticle(particle2);

        //Initialize a force field that apply to all the particles of the system to simulate gravity
        //Add it to the system as a force field
        ConstantForceFieldPtr gravityForceField
            = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0, 0, -10} );
        system->addForceField(gravityForceField);

        //Create a particleRenderable for each particle of the system
        //DynamicSystemRenderable act as a hierarchical renderable
        //This allows easily applying a transformation on the visualization of a dynamicSystem
        ParticleRenderablePtr particleRenderable1
            = std::make_shared<ParticleRenderable>(flatShader, particle1);
        HierarchicalRenderable::addChild(systemRenderable, particleRenderable1);
        ParticleRenderablePtr particleRenderable2
            = std::make_shared<ParticleRenderable>(flatShader, particle2);
        HierarchicalRenderable::addChild(systemRenderable, particleRenderable2);
    }

    //Finally, run the animation
    viewer.startAnimation();
}

