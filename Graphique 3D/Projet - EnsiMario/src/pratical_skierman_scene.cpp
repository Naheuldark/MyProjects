#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/MeshRenderable.hpp"
#include "../include/CylinderRenderable.hpp"
#include "../include/ConeRenderable.hpp"
#include "../include/CubeRenderable.hpp"
#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/SkierCharacter.hpp"
#include "../include/SkierCharacter2.hpp"

#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"
#include "../include/dynamics/Particle.hpp"
#include "../include/dynamics/ParticleSkier.hpp"

#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderableSkier.hpp"
#include "../include/dynamics_rendering/ParticleListRenderable.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringListRenderable.hpp"
#include "../include/dynamics_rendering/ControlledForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/QuadRenderable.hpp"

#include "../include/keyframes/KeyframedCylinderRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"

#include <iostream>
#include <iomanip>



void initialize_skierman_scene(Viewer& viewer)
{
    // Shaders
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(
        "../shaders/flatVertex.glsl", "../shaders/flatFragment.glsl");
    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
        "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");
    viewer.addShaderProgram(flatShader);
    viewer.addShaderProgram(phongShader);

    // Frame
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

    // Two texture shaders: simple and multi-texturing
    ShaderProgramPtr texShader
        = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                          "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

    //Position the camera
    //Length : 200  ;;  maxHeight : 80  ;;  Width : 30;
    // viewer.getCamera().setViewMatrix(glm::lookAt(glm::vec3(3, -3, 5), // eye
    //                                              glm::vec3(0, 0, 2), // direction + eye
    //                                              glm::vec3(0,0,1)));
    viewer.getCamera().setViewMatrix(glm::lookAt(glm::vec3(-8, -0.5, 10), // eye -7 7 5
                                                 glm::vec3(0,0,3), // direction + eye 00 3
                                                 glm::vec3(0,0,1)));

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
    

    // Add only the root of the 
     //viewer.addRenderable(buildASkier(flatShader,texShader));
      #define PI 3.14159265
     // Skier
     //glm::vec3 positionSkier = glm::vec3(5,10,82.5);
     glm::vec3 velocitySkier(0.0, 0.0, 0.0);
     float massSkier = 90.0, angleSkier = 0;
    // glm::vec3 sizeSkier = glm::vec3(0.5,4,5);
    // glm::vec3 axisSkier = glm::vec3(0,0,1);
    // BoxPtr boxSkier = std::make_shared<Box>(positionSkier,velocitySkier,sizeSkier,angleSkier,axisSkier,massSkier);
    // system->addBox(boxSkier);
    glm::vec3 positionSkier = glm::vec3(0.0,0.0,1.0);
    float pm = 1.0, pr = 0.5;
    ParticleSkierPtr mobile = std::make_shared<ParticleSkier>( positionSkier, velocitySkier, pm, pr,angleSkier,0);
    system->addParticle( mobile );


    HierarchicalRenderablePtr start;


    //Create a particleRenderable for each particle of the system
    //Add them to the system renderable
    // Sous-classe de ParticleRenderable qui a pour champ viewer (initialisé dans le constructeur) et dans le animate on actualise la position
    // de la camera en fonction de la position de la particle
    
    ParticleRenderableSkierPtr mobileRenderable = std::make_shared<ParticleRenderableSkier>(flatShader, mobile,&viewer, start);
    HierarchicalRenderable::addChild(systemRenderable, mobileRenderable);

    HierarchicalRenderablePtr skier = buildASkier2(phongShader,texShader);
    //skier->setParentTransform(glm::translate(skier->getParentTransform(), positionSkier));
    skier->setParentTransform(glm::rotate(glm::mat4(),(glm::mediump_float)(-PI/5 - PI/2), glm::vec3(0, 0, 1)));
    skier->setParentTransform(glm::scale(skier->getParentTransform(), glm::vec3(1.5, 1.5, 1.5)));


    HierarchicalRenderable::addChild(mobileRenderable,skier);

    glm::vec3 positionSkierTranslateFront = glm::vec3(-1.4,1.4,-2);
    ParticlePtr frontSki = std::make_shared<Particle>(positionSkierTranslateFront,velocitySkier, pm, 0.2);
    system->addParticle(frontSki);

    ParticleRenderablePtr frontSkiRdr = std::make_shared<ParticleRenderable>(flatShader, frontSki);
    HierarchicalRenderable::addChild(skier, frontSkiRdr);

    glm::vec3 positionSkierTranslateBack = glm::vec3(0.7,-0.7,-2);
    ParticlePtr backSki = std::make_shared<Particle>(positionSkierTranslateBack,velocitySkier, pm, 0.2);
    system->addParticle(backSki);

    ParticleRenderablePtr backSkiRdr = std::make_shared<ParticleRenderable>(flatShader, backSki);
    HierarchicalRenderable::addChild(skier, backSkiRdr);

    //viewer.addRenderable(skier);


    //Initialize a force field that apply only to the mobile particle
    glm::vec3 nullForce(0.0, 0.0, 0.0);
    std::vector<ParticlePtr> vParticle;
    // vParticule.push_back(boxSkier);
    // ConstantForceFieldBoxPtr force = std::make_shared<ConstantForceFieldBox>(vBox, nullForce);
    // system->addForceField(force);
    vParticle.push_back(mobile);
    ConstantForceFieldPtr force = std::make_shared<ConstantForceField>(vParticle, nullForce);
    system->addForceField(force);

    std::vector<ParticlePtr> particleAnnexe;

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

    viewer.startAnimation();
}