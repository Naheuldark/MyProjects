#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/SkierCharacter.hpp"

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


void initialize_collision_scene(Viewer& viewer)
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

    //Position the camera
    viewer.getCamera().setViewMatrix(
        glm::lookAt(glm::vec3(0,2, 2), // eye
                            glm::vec3(0, 0, 0), // direction + eye
                            glm::vec3(0,0,1)));

        // Two texture shaders: simple and multi-texturing
    ShaderProgramPtr texShader
        = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                          "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

        ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
        "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");
    viewer.addShaderProgram(phongShader);

    //Activate collision detection
    system->setCollisionsDetection(true);

    //Initialize the restitution coefficient for collision
    //1.0 = full elastic response
    //0.0 = full absorption
    system->setRestitution(0.0);

    //Initialize a plane from 3 points and add it to the system as an obstacle
    glm::vec3 p1(-1.0, -1.0, 0.0);
    glm::vec3 p2(1.0, -1.0, 0.0);
    glm::vec3 p3(1.0, 1.0, 0.0);
    glm::vec3 p4(-1.0, 1.0, 0.0);
    PlanePtr plane = std::make_shared<Plane>(p1, p2, p3,15,7);
    system->addPlaneObstacle(plane);

    //Create a plane renderable to display the obstacle
    PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(flatShader, p1,p2,p3,p4);
    HierarchicalRenderable::addChild( systemRenderable, planeRenderable );

    glm::vec3 px,pv;
    float pm, pr;
    //Particle vs Plane collision

        //Initialize a particle with position, velocity, mass and radius and add it to the system
        px = glm::vec3(0.0, 0.0, 1.0);
        pv = glm::vec3(0.0, 0.0, 0.0);
        pr = 0.1;
        pm = 1.0;
        ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
        system->addParticle(particle);

        //Create a particleRenderable for each particle of the system
        //DynamicSystemRenderable act as a hierarchical renderable
        //This which allows to easily apply transformation on the visualiazation of a dynamicSystem
        ParticleRenderablePtr particleRenderable = std::make_shared<ParticleRenderable>(flatShader, particle);
        HierarchicalRenderable::addChild(systemRenderable, particleRenderable);

    //Particle vs Particle collision
    
        //Initialize two particles with position, velocity, mass and radius and add it to the system
        //One of the particle is fixed
        px = glm::vec3(0.5, 0.0, 0.0);
        pv = glm::vec3(0.0, 0.0, 0.0);
        pr = 0.1;
        pm = 1000.0;
        ParticlePtr particle1 = std::make_shared<Particle>(px, pv, pm, pr);
        particle1->setFixed(true);
        system->addParticle(particle1);

        px = glm::vec3(3.0, 3.0, 0);
        pv = glm::vec3(0.0, 0.0, 0);
        pr = 1.0;
        pm = 0.00001;
        ParticlePtr particle2 = std::make_shared<Particle>(px, pv, pm, pr);
        //system->addParticle(particle2);

        //Create a particleRenderable for each particle of the system
        ParticleRenderablePtr particleRenderable1 = std::make_shared<ParticleRenderable>(flatShader, particle1);
        HierarchicalRenderable::addChild(systemRenderable, particleRenderable1);
        ParticleRenderablePtr particleRenderable2 = std::make_shared<ParticleRenderable>(flatShader, particle2);
        HierarchicalRenderable::addChild(particleRenderable, particleRenderable2);
    
      //Initialize a force field that apply to all the particles of the system to simulate gravity
    //Add it to the system as a force field
    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0,0,-10} );
    system->addForceField(gravityForceField);


    //Finally, run the animation
    viewer.startAnimation();
}

