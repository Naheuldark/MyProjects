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


void initialize_airbag_scene(Viewer& viewer)
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
    system->setRestitution(0.0f);

    //Create a renderable associated to the dynamic system
    //This renderable is responsible for calling DynamicSystem::computeSimulationStep()in the animate() function
    //It also handles some of the key/mouse events
    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);

    //Position the camera
    viewer.getCamera().setViewMatrix(
        glm::lookAt(glm::vec3(-10, 0, 2), glm::vec3(5,5,5), glm::vec3(0,0,1)) );


    //Initialize particle attributes (radius, mass)
    float pr = 0.1, pm = 10.0;
    glm::vec3 px(0.0,0.0,0.0), pv(0.0,0.0,0.0);

    //Create particles on a squared uniform grid starting at origin
    std::vector<ParticlePtr> particles;
    glm::vec3 origin(0.0,0.0,0.0), displacement(0.0,0.0,0.0);
    int particlePerLine = 20;
    float gridSize = 10.0;
    float xstep = gridSize / (float)(particlePerLine-1);
    float ystep = xstep;
    particles.resize(particlePerLine*particlePerLine);

    for (size_t i = 0; i < particlePerLine; ++ i) {
        for (size_t j = 0; j < particlePerLine; ++ j) {
            displacement = glm::vec3(i*xstep, j*ystep, 0);
            px = origin + displacement;
            particles[i*particlePerLine+j] = std::make_shared<Particle>( px, pv, pm, pr );
            system->addParticle( particles[i*particlePerLine+j] );
        }
    }

    //Fix particles on the borders
    for (size_t i = 0; i < particlePerLine; ++i) {
        for (size_t j = 0; j < particlePerLine; ++j) {
            if (i == 0) {
                particles[j]->setFixed(true);
            }
            if (i == particlePerLine-1) {
                particles[(particlePerLine-1)*particlePerLine+j]->setFixed(true);
            }
            if (j == 0) {
                particles[i*particlePerLine]->setFixed(true);
            }
            if (j == particlePerLine-1) {
                particles[i*particlePerLine+particlePerLine-1]->setFixed(true);
            }
        }
    }

    //Initialize springs attributes (stiffness, rest length, damping)
    float stiffness = 5000;
    float l0 = 0.0;
    float damping = 0.0;

    //Create springs between particles of the grid
    //Store them in a list
    std::list<SpringForceFieldPtr> springForceFields;
    //Interior
    for (size_t i = 1; i < particlePerLine; ++ i) {
        for (size_t j = 1; j < particlePerLine; ++ j) {
            SpringForceFieldPtr spring1 = std::make_shared<SpringForceField>( particles[(i-1)*particlePerLine+j], particles[i*particlePerLine+j], stiffness, l0, damping );
            springForceFields.push_back(spring1);
            system->addForceField(spring1);
            SpringForceFieldPtr spring2 = std::make_shared<SpringForceField>( particles[i*particlePerLine+(j-1)], particles[i*particlePerLine+j], stiffness, l0, damping );
            springForceFields.push_back(spring2);
            system->addForceField(spring2);
        }
    }
    //Border case 1
    for (size_t j = 1; j < particlePerLine; ++ j) {
        SpringForceFieldPtr spring = std::make_shared<SpringForceField>( particles[0*particlePerLine+j], particles[0*particlePerLine+(j-1)], stiffness, l0, damping );
        springForceFields.push_back(spring);
        system->addForceField(spring);
    }
    //Border case 2
    for (size_t i = 1; i < particlePerLine; ++ i) {
        SpringForceFieldPtr spring = std::make_shared<SpringForceField>( particles[(i-1)*particlePerLine+0], particles[i*particlePerLine+0], stiffness, l0, damping );
        springForceFields.push_back(spring);
        system->addForceField(spring);
    }



    px = glm::vec3(5.0, 5.0, 5.0);
    pv = glm::vec3(0.0, 0.0, 0.0);
    pr = 0.5;
    pm = 60.0;
    ParticlePtr particle1 = std::make_shared<Particle>(px, pv, pm, pr);
    system->addParticle(particle1);

    //Create a particleRenderable for each particle of the system
    ParticleRenderablePtr particleRenderable1 = std::make_shared<ParticleRenderable>(flatShader, particle1);
    HierarchicalRenderable::addChild(systemRenderable, particleRenderable1);

    


    //Initialize a force field that apply to all the particles of the system to simulate gravity
    //Add it to the system as a force field
    ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0, 0, -10});
    system->addForceField(gravityForceField);

    //Initialize a force field that apply to all the particles of the system to simulate vicosity (air friction)
    float dampingCoefficient = 0.0;
    DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(system->getParticles(), dampingCoefficient);
    system->addForceField(dampingForceField);


    //Create a particleListRenderable to efficiently visualize the particles of the system
    ParticleListRenderablePtr particleListRenderable = std::make_shared<ParticleListRenderable>( flatShader, particles);
    HierarchicalRenderable::addChild(systemRenderable, particleListRenderable);

    //Create a springListRenderable to efficiently visualize the springs of the system
    SpringListRenderablePtr springsRenderable = std::make_shared<SpringListRenderable>(flatShader, springForceFields);
    HierarchicalRenderable::addChild(systemRenderable, springsRenderable);

    //Display gravity
    // ConstantForceFieldRenderablePtr gravityRenderable = std::make_shared<ConstantForceFieldRenderable>(flatShader, gravityForceField);
    // HierarchicalRenderable::addChild(systemRenderable, gravityRenderable);

    //Finally, run the animation
    viewer.startAnimation();
}

