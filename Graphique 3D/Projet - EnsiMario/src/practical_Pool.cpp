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


void practical_playPool(Viewer& viewer,
    DynamicSystemPtr& system, DynamicSystemRenderablePtr& systemRenderable);


void initialize_Pool_scene(Viewer& viewer)
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

    //Populate the dynamic system with particles, forcefields
    //and create renderables associated to them for visualization.

    practical_playPool(viewer, system, systemRenderable);

    //Finally, run the animation
    viewer.startAnimation();
}


void practical_playPool(Viewer& viewer, DynamicSystemPtr& system, DynamicSystemRenderablePtr& systemRenderable)
{
    //Initialize a shader for the following renderables
    ShaderProgramPtr flatShader
        = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl","../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);

    //Position the camera
    viewer.getCamera().setViewMatrix(
        glm::lookAt(glm::vec3(0, -15, 15), glm::vec3(0,0,0), glm::vec3(0,0,1)) );

    //Initialize two particles with position, velocity, mass and radius and add it to the system
    glm::vec3 px(0.0, 0.0, 0.0);
    glm::vec3 pv(0.0, 0.0, 0.0);
    float pm = 1.0, pr = 0.5;
    px = glm::vec3(0.0,0.0,1.0);
    ParticlePtr mobile = std::make_shared<Particle>( px, pv, pm, pr);
    system->addParticle( mobile );
    px = glm::vec3(0.0,5.0,1.0);
    ParticlePtr other = std::make_shared<Particle>( px, pv, pm, pr);
    system->addParticle( other );

    //Create a particleRenderable for each particle of the system
    //Add them to the system renderable
    ParticleRenderablePtr mobileRenderable = std::make_shared<ParticleRenderable>(flatShader, mobile);
    HierarchicalRenderable::addChild(systemRenderable, mobileRenderable);
    ParticleRenderablePtr otherRenderable = std::make_shared<ParticleRenderable>(flatShader, other);
    HierarchicalRenderable::addChild(systemRenderable, otherRenderable);

    //Initialize four planes to create walls arround the particles
    glm::vec3 planeNormal, planePoint;
    planeNormal = glm::vec3(-1, 0, 0);
    planePoint = glm::vec3(10, 0, 0);
    PlanePtr p0 = std::make_shared<Plane>(planeNormal, planePoint);
    system->addPlaneObstacle(p0);

    planeNormal = glm::vec3(1, 0, 0);
    planePoint = glm::vec3(-10, 0, 0);
    PlanePtr p1 = std::make_shared<Plane>(planeNormal, planePoint);
    system->addPlaneObstacle(p1);

    planeNormal = glm::vec3(0, -1, 0);
    planePoint = glm::vec3(0, 10, 0);
    PlanePtr p2 = std::make_shared<Plane>(planeNormal, planePoint);
    system->addPlaneObstacle(p2);

    planeNormal = glm::vec3(0, 1, 0);
    planePoint = glm::vec3(0, -10, 0);
    PlanePtr p3 = std::make_shared<Plane>(planeNormal, planePoint);
    system->addPlaneObstacle(p3);

    planeNormal = glm::vec3(0, 0, 1);
    planePoint = glm::vec3(0, 0, 0);
    PlanePtr floor = std::make_shared<Plane>( planeNormal, planePoint);
    system->addPlaneObstacle(floor);

    //Create  plane renderables to display each obstacle
    //Add them to the system renderable
    glm::vec3 x1, x2, x3, x4;
    glm::vec4 color;
    x1 = glm::vec3(10,  10, 5);
    x2 = glm::vec3(10,  10, 0);
    x3 = glm::vec3(10, -10, 0);
    x4 = glm::vec3(10, -10, 5);
    color = glm::vec4(7.0, 0.2, 0.2, 1.0);
    PlaneRenderablePtr p1Renderable = std::make_shared<QuadRenderable>(flatShader, x1, x2, x3, x4, color);
    HierarchicalRenderable::addChild(systemRenderable, p1Renderable);

    x1 = glm::vec3(-10, 10, 5);
    x2 = glm::vec3(-10, 10, 0);
    x3 = glm::vec3( 10, 10, 0);
    x4 = glm::vec3( 10, 10, 5);
    color = glm::vec4(7.0, 0.2, 0.2, 1.0);
    PlaneRenderablePtr p2Renderable = std::make_shared<QuadRenderable>(flatShader, x1, x2, x3, x4, color);
    HierarchicalRenderable::addChild(systemRenderable, p2Renderable);

    x1 = glm::vec3(-10, -10, 5);
    x2 = glm::vec3(-10, -10, 0);
    x3 = glm::vec3(-10,  10, 0);
    x4 = glm::vec3(-10,  10, 5);
    color = glm::vec4(0.2, 0.4, 0.4, 1.0);
    PlaneRenderablePtr p3Renderable = std::make_shared<QuadRenderable>(flatShader, x1, x2, x3, x4, color);
    HierarchicalRenderable::addChild(systemRenderable, p3Renderable);

    x1 = glm::vec3( 10, -10, 5);
    x2 = glm::vec3( 10, -10, 0);
    x3 = glm::vec3(-10, -10, 0);
    x4 = glm::vec3(-10, -10, 5);
    color = glm::vec4(0.2, 0.4, 0.4, 1.0);
    PlaneRenderablePtr p4Renderable = std::make_shared<QuadRenderable>(flatShader, x1, x2, x3, x4, color);
    HierarchicalRenderable::addChild(systemRenderable, p4Renderable);

    //Initialize a force field that apply only to the mobile particle
    glm::vec3 nullForce(0.0, 0.0, 0.0);
    std::vector<ParticlePtr> vParticle;
    vParticle.push_back(mobile);
    ConstantForceFieldPtr force = std::make_shared<ConstantForceField>(vParticle, nullForce);
    system->addForceField(force);

    //Initialize a renderable for the force field applied on the mobile particle.
    //This renderable allows to modify the attribute of the force by key/mouse events
    //Add this renderable to the systemRenderable.
    ControlledForceFieldRenderablePtr forceRenderable = std::make_shared<ControlledForceFieldRenderable>(flatShader, force);
    HierarchicalRenderable::addChild(systemRenderable, forceRenderable);

    //Add a damping force field to the mobile.
    DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(vParticle, 0.9);
    system->addForceField(dampingForceField);

    //Activate collision and set the restitution coefficient to 1.0
    system->setCollisionsDetection(true);
    system->setRestitution(1.0);
}