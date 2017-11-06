#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/Elements.hpp"

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

#include "../include/CubeRenderable.hpp"

void practical_box_scene(Viewer& viewer,
    DynamicSystemPtr& system, DynamicSystemRenderablePtr& systemRenderable);
void practical07_collisions(Viewer& viewer,
    DynamicSystemPtr& system, DynamicSystemRenderablePtr& systemRenderable);


void initialize_box_scene(Viewer& viewer)
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

    practical07_collisions(viewer, system, systemRenderable);

    //Finally, run the animation
    viewer.startAnimation();
}

void practical07_collisions(Viewer& viewer, DynamicSystemPtr& system, DynamicSystemRenderablePtr &systemRenderable)
{
    //Position the camera
    viewer.getCamera().setViewMatrix(
        glm::lookAt(glm::vec3(0, 2, 2), glm::vec3(0,0,0), glm::vec3(0,0,1)) );

    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
        "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");

    viewer.addShaderProgram(phongShader);

    // Two texture shaders: simple and multi-texturing
    ShaderProgramPtr texShader
        = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                          "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

    //Initialize a shader for the following renderables
    ShaderProgramPtr flatShader
        = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl","../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);

    //Activate collision detection
    system->setCollisionsDetection(true);

    //Initialize the restitution coefficient for collision
    //1.0 = full elastic response
    //0.0 = full absorption
    system->setRestitution(0.6f);

    //Initialize a plane from 3 points and add it to the system as an obstacle
    glm::vec3 p1(-1.0, -1.0, 0.0);
    glm::vec3 p2(1.0, -1.0, 0.0);
    glm::vec3 p3(1.0, 1.0, 0.0);
    glm::vec3 p4(-1.0, 1.0, 0.0);
    PlanePtr plane = std::make_shared<Plane>(p1, p2, p3,0,0);
    system->addPlaneObstacle(plane);

    //Create a plane renderable to display the obstacle
    PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(flatShader, p1,p2,p3,p4);
    HierarchicalRenderable::addChild( systemRenderable, planeRenderable );

    glm::vec3 px,pv, psize;
    float pm, pr;

    // //Initialize a particle with position, velocity, mass and radius and add it to the system
    // px = glm::vec3(0.0, 0.0, 1.0);
    // pv = glm::vec3(0.0, 0.0, 0.0);
    // psize = glm::vec3(1.0, 1.0, 1.0);
    // pm = 1.0;
    // BoxPtr box = std::make_shared<Box>(px, pv, psize, 0.0f, glm::vec3(0,0,0), pm);
    // system->addBox(box);

    // //Create a particleRenderable for each particle of the system
    // //DynamicSystemRenderable act as a hierarchical renderable
    // //This which allows to easily apply transformation on the visualiazation of a dynamicSystem
    // HierarchicalRenderablePtr tree = std::make_shared<HierarchicalRenderable>(flatShader, box);


    //Particle vs Particle collision
    {
        //Initialize two particles with position, velocity, mass and radius and add it to the system
        //One of the particle is fixed
        px = glm::vec3(0.5, 0.0, 0.1);
        pv = glm::vec3(0.0, 0.0, 0.0);
        pr = 0.1;
        psize = glm::vec3(1.0, 1.0, 1.0);
        pm = 1000.0;
        //BoxPtr box1 = std::make_shared<Box>(px, pv, psize, 0.0f, glm::vec3(0,0,0), pm);
        //box1->setFixed(true);
        //system->addBox(box1);

        px = glm::vec3(0.5, 0.0, 1.0);
        pv = glm::vec3(0.0, 0.0, -0.5);
        psize = glm::vec3(1.0, 1.0, 1.0);
        pr = 0.1;
        pm = 1.0;
        //BoxPtr box2 = std::make_shared<Box>(px, pv, psize, 0.0f, glm::vec3(0,0,0), pm);
        //system->addBox(box2);

        //Create a particleRenderable for each particle of the system
        HierarchicalRenderablePtr tree1 = buildASmallTree(phongShader, texShader);
        HierarchicalRenderable::addChild(systemRenderable, tree1);
        HierarchicalRenderablePtr tree2 = buildASmallTree(phongShader, texShader);
        HierarchicalRenderable::addChild(systemRenderable, tree2);
    }

    //Initialize a force field that apply to all the particles of the system to simulate gravity
    //Add it to the system as a force field
    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0,0,-10} );
    system->addForceField(gravityForceField);
    //Activate collision and set the restitution coefficient to 1.0
    system->setCollisionsDetection(true);
    system->setRestitution(1.0f);

}
