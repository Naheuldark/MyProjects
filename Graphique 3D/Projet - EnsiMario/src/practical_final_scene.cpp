#include "../include/Elements.hpp"
#include "../include/SkierCharacter2.hpp"

#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/Geometries.hpp"

#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/lighting/LightedMeshRenderable.hpp"
#include "../include/lighting/LightedCubeRenderable.hpp"

#include "../include/texturing/TexturedPlaneRenderable.hpp"
#include "../include/texturing/TexturedMapRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"
#include "../include/texturing/TexturedMountainsRenderable.hpp"
#include "../include/texturing/TexturedCubeRenderable.hpp"

#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"
#include "../include/dynamics/Particle.hpp"

#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderableSkier.hpp"
#include "../include/dynamics_rendering/ParticleListRenderable.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringListRenderable.hpp"
#include "../include/dynamics_rendering/ControlledForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/QuadRenderable.hpp"

#include <stdlib.h>

void initialize_final_scene(Viewer& viewer)
{
    // create all shaders of this scene, then add them to the viewer
    ShaderProgramPtr flatShader
        = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                          "../shaders/flatFragment.glsl");   
    viewer.addShaderProgram(flatShader);


    ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
        "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");
    viewer.addShaderProgram(phongShader);

        //Add a 3D frame to the viewer
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);


    DynamicSystemPtr system = std::make_shared<DynamicSystem>();
    EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
    system->setSolver(solver);
    system->setDt(0.01);

    DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
    viewer.addRenderable(systemRenderable);


    //Position the camera
    //Length : 200  ;;  maxHeight : 80  ;;  Width : 30;
    // viewer.getCamera().setViewMatrix(glm::lookAt(glm::vec3(0, 15, 85), // eye
    //                                              glm::vec3(1, 15, 85), // direction + eye
    //                                              glm::vec3(0,0,1)));

    viewer.getCamera().setViewMatrix(glm::lookAt(glm::vec3(-3,9.5, 90), // eye
                                                 glm::vec3(5, 10, 83), // direction + eye
                                                 glm::vec3(0,0,1)));

    // Two texture shaders: simple and multi-texturing
    ShaderProgramPtr texShader
        = std::make_shared<ShaderProgram>("../shaders/textureVertex.glsl",
                                          "../shaders/textureFragment.glsl");
    viewer.addShaderProgram(texShader);

        //Activate collision and set the restitution coefficient to 1.0
    system->setCollisionsDetection(true);
    system->setRestitution(0.0);

    // Textured Snowball
    glm::vec3 CamPos = viewer.getCamera().getPosition();


    int width = 30;
    int length = 200;
    int maxHeight = 80;
    int topwidth = 10;

    // COLLISION
    // Starter pad plane
    glm::vec3 p1(10.0, 30.0, 80.0);
    glm::vec3 p2(0.0, 0.0, 80.0);
    glm::vec3 p3(0.0, 30.0, 80.0);
    glm::vec3 p4(10.0, 0.0, 80.0);
    float longueur = 10;
    float milieu = 5;
    PlanePtr plane = std::make_shared<Plane>(p1, p3, p2, longueur, milieu);
    system->addPlaneObstacle(plane);

    //Start slope plane
    float h_start = maxHeight + 4 - 13.0*maxHeight/length;
    p1 = glm::vec3(10.0, 30.0, 80.0);
    p2 = glm::vec3(10.0, 0.0, 80.0);
    p3 = glm::vec3(13.0, 0.0, h_start-13.0+10);
    p4 = glm::vec3(13.0, 30.0, h_start-13.0+10);
    longueur = 3;
    milieu = 11.5;
    PlanePtr start_slope = std::make_shared<Plane>(p1, p2, p3, longueur, milieu);
    system->addPlaneObstacle(start_slope);

    // PlaneRenderablePtr start_slope_rend = std::make_shared<QuadRenderable>(flatShader, p2,p1,p4,p3);
    // HierarchicalRenderable::addChild(systemRenderable, start_slope_rend);

    //Lower slope plane
    float h_lower = maxHeight + 4 - (length-15.0)*maxHeight/length;
    p1 = glm::vec3(length-15.0, 30.0, h_lower-3.0);
    p2 = glm::vec3(length-15.0, 0.0, h_lower-3.0);
    p3 = glm::vec3(13.0, 0.0, h_start-13.0+10);
    p4 = glm::vec3(13.0, 30.0, h_start-13.0+10);
    longueur = length-15-13;
    milieu = 13 + longueur/2;
    PlanePtr lower_slope = std::make_shared<Plane>(p4, p3, p2, longueur, milieu);
    system->addPlaneObstacle(lower_slope);

    // PlaneRenderablePtr lower_slope_rend = std::make_shared<QuadRenderable>(flatShader, p3,p4,p1,p2);
    // HierarchicalRenderable::addChild(systemRenderable, lower_slope_rend);
    
    //Finish plane
    // p1 = glm::vec3(length-13.0, 0.0, 0);
    // p2 = glm::vec3(length-13.0, 1.0, 0);
    // p3 = glm::vec3(length-13, 0,1);
    // longueur = 0;
    // milieu = 0;
    // PlanePtr finish_plane = std::make_shared<Plane>(p1,p3,p2, longueur, milieu);
    // system->addPlaneObstacle(finish_plane);

    //Floor plane
    p1 = glm::vec3(0, 0, 0);
    p2 = glm::vec3(0, 1,0);
    p3 = glm::vec3(1, 0.0, 0);
    longueur = 0;
    milieu = 0;
    PlanePtr floor = std::make_shared<Plane>(p1, p3,p2, longueur, milieu);
    system->addPlaneObstacle(floor);

    glm::vec3 px,pv;
    float pm, pr;
    int sign = 1;

    // ParticlePtr particles[1000];
    // ParticleRenderablePtr particleRenderables[1000];

    // for (int i = 0; i < 1000; ++i) {
    //     if (i%2 == 0)
    //         sign = -1;
    //     else
    //         sign = 1;
    //     px = glm::vec3(CamPos[0]+1, CamPos[1]+sign*(random()%1000)/500.0, 95);
    //     pv = glm::vec3(0.0, 0.0, (random()%100)/5.0);
    //     pr = 0.01;
    //     pm = (random()%100)/100.0;
    //     particles[i] = std::make_shared<Particle>(px, pv, pm, pr);
    //     system->addParticle(particles[i]);
    // }

    // ConstantForceFieldPtr gravityForceField
    //     = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0, 0, -10} );
    // system->addForceField(gravityForceField);

    // for (int i = 0; i < 1000; ++i) {
    //     particleRenderables[i] = std::make_shared<ParticleRenderable>(flatShader, particles[i]);
    //     HierarchicalRenderable::addChild(systemRenderable, particleRenderables[i]);
    // }


    //Temporary variables
    glm::mat4 parentTransformation(1.0), localTransformation(1.0);
    std::string filename;
    MaterialPtr snow = Material::Snow();
    MaterialPtr skyblue = Material::SkyBlue(); 


   
    //Define a directional light for the whole scene
    glm::vec3 d_direction = glm::normalize(glm::vec3(0.0,0.0,-1.0));
    glm::vec3 d_ambient(1.0,1.0,1.0), d_diffuse(1.0,1.0,0.8), d_specular(1.0,1.0,1.0);
    DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, d_ambient, d_diffuse, d_specular);
    //Add a renderable to display the light and control it via mouse/key event
    glm::vec3 lightPosition(0.0,0.0,5.0);
    DirectionalLightRenderablePtr directionalLightRenderable = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
    localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
    directionalLightRenderable->setLocalTransform(localTransformation);
    viewer.setDirectionalLight(directionalLight);
    viewer.addRenderable(directionalLightRenderable);



    //Textured map
    filename = "../textures/snow_texture.jpg";
    TexturedMapRenderablePtr texMap = std::make_shared<TexturedMapRenderable>(texShader, filename);
    
    // ### Ligne suivante à commenter
    //parentTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.01,0.01,0.01));    

    texMap->setParentTransform(parentTransformation);
    texMap->setMaterial(snow);
    viewer.addRenderable(texMap);

    //Surounding mountains
    filename = "../textures/rock_texture.jpg";
    TexturedMountainsRenderablePtr texMount = std::make_shared<TexturedMountainsRenderable>(texShader, filename);
    texMount->setParentTransform(parentTransformation);
    texMount->setMaterial(snow);
    viewer.addRenderable(texMount);

    

    HierarchicalRenderablePtr talltree;

    //Treelines at the start 
    float pmTree = 800.0, prTree = 1; 
    ParticlePtr treePar;
    ParticleRenderablePtr treeParRen;

    for (int i = 0; i <= topwidth; i+= 2) {
        talltree = buildATallTree(phongShader, texShader);
        talltree->setParentTransform(glm::scale(glm::translate(talltree->getParentTransform(), glm::vec3(i,0,maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(i,0,maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(talltree);


        talltree = buildATallTree(phongShader, texShader);
        talltree->setParentTransform(glm::scale(glm::translate(talltree->getParentTransform(), glm::vec3(i,width,maxHeight)), glm::vec3(1,1,1)));
        
        treePar = std::make_shared<Particle>(glm::vec3(i,width,maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(talltree);

    }

    for (int i = 2; i <= width-2; i+= 2) {
        talltree = buildATallTree(phongShader, texShader);
        talltree->setParentTransform(glm::scale(glm::translate(talltree->getParentTransform(), glm::vec3(0,i,maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(0,i,maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(talltree);
    }

    HierarchicalRenderablePtr smalltree;
    prTree = 0.8; 
    for (int i = 2; i <= topwidth; i+= 2) {
        smalltree = buildASmallTree(phongShader, texShader);
        smalltree->setParentTransform(glm::scale(glm::translate(smalltree->getParentTransform(), glm::vec3(i,2,maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(i,2,maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);   

        viewer.addRenderable(smalltree);

        smalltree = buildASmallTree(phongShader, texShader);
        smalltree->setParentTransform(glm::scale(glm::translate(smalltree->getParentTransform(), glm::vec3(i,width-2,maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(i, width-2, maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(smalltree);
    }
    for (int i = 4; i <= width-4; i+= 2) {
        smalltree = buildASmallTree(phongShader, texShader);
        smalltree->setParentTransform(glm::scale(glm::translate(smalltree->getParentTransform(), glm::vec3(2,i,maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(2, i, maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(smalltree);
    }

    for (int i = 0; i <= 5; i++) {
        talltree = buildATallTree(phongShader, texShader);
        talltree->setParentTransform(glm::scale(glm::translate(talltree->getParentTransform(), glm::vec3(10, width-2*(i+2),maxHeight)), glm::vec3(1,1,1)));

        treePar = std::make_shared<Particle>(glm::vec3(10, width-2*(i+2),maxHeight+0.5), glm::vec3(0,0,0), pmTree, prTree);
        system->addParticle(treePar);
        treePar->setFixed(true);
        treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
        HierarchicalRenderable::addChild(systemRenderable, treeParRen);

        viewer.addRenderable(talltree);
    }

    //Random trees anywhere on the map
    for (int i = 0; i <=50; i++) {
        int x = rand()%(length-10)+10;
        int y = rand()%width;
        float z = height(x, y, maxHeight, length, width);
        if (rand()%2) {
            talltree = buildATallTree(phongShader, texShader);
            talltree->setParentTransform(glm::scale(glm::translate(talltree->getParentTransform(), glm::vec3(x, y, z-0.05)), glm::vec3(1,1,1)));

            prTree = 1;
            treePar = std::make_shared<Particle>(glm::vec3(x, y, z+0.45), glm::vec3(0,0,0), pmTree, prTree);
            system->addParticle(treePar);
            treePar->setFixed(true);
            treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
            HierarchicalRenderable::addChild(systemRenderable, treeParRen);


            viewer.addRenderable(talltree);
        } else {
            smalltree = buildASmallTree(phongShader, texShader);
            smalltree->setParentTransform(glm::scale(glm::translate(smalltree->getParentTransform(), glm::vec3(x, y, z-0.05)), glm::vec3(1,1,1)));

            prTree = 0.80;
            treePar = std::make_shared<Particle>(glm::vec3(x, y, z+0.45), glm::vec3(0,0,0), pmTree, prTree);
            system->addParticle(treePar);
            treePar->setFixed(true);
            treeParRen = std::make_shared<ParticleRenderable>(flatShader, treePar);
            HierarchicalRenderable::addChild(systemRenderable, treeParRen);

            viewer.addRenderable(smalltree);
        }
    }

    //Snowmen
    ParticlePtr snowmanPar;
    ParticleRenderablePtr snowmanParRen;
    HierarchicalRenderablePtr snowman = buildASnowman(phongShader);
    snowman->setParentTransform(glm::scale(glm::translate(snowman->getParentTransform(), glm::vec3(topwidth - 2, width/2, maxHeight + 0.5)), glm::vec3(0.5,0.5,0.5)));
    
    float prSnowman = 0.8;
    float pmSnowman = 15;
    snowmanPar = std::make_shared<Particle>(glm::vec3(topwidth - 2, width/2, maxHeight + 0.5), glm::vec3(0,0,0), pmSnowman, prSnowman);
    system->addParticle(snowmanPar);
    snowmanPar->setFixed(true);
    snowmanParRen = std::make_shared<ParticleRenderable>(flatShader, snowmanPar);
    HierarchicalRenderable::addChild(systemRenderable, snowmanParRen);

    viewer.addRenderable(snowman);

    ParticlePtr endSnowmanPar;
    ParticleRenderablePtr endSnowmanParRen;
    HierarchicalRenderablePtr endSnowman = buildASnowman(phongShader);
    endSnowman->setParentTransform(glm::translate(endSnowman->getParentTransform(), glm::vec3(length - 16, width*3.0/4, height(length-16, width*3.0/4, maxHeight, length, width)+1)));
    endSnowman->setParentTransform(glm::rotate(endSnowman->getParentTransform(), (float)(3*M_PI/2), glm::vec3(0, 0, 1)));
    endSnowman->setParentTransform(glm::scale(endSnowman->getParentTransform(), glm::vec3(0.5,0.5,0.5)));
    
    prSnowman = 0.8;
    pmSnowman = 15;
    endSnowmanPar = std::make_shared<Particle>(glm::vec3(length - 16, width*3.0/4, height(length-16, width*3.0/4, maxHeight, length, width)+1), glm::vec3(0,0,0), pmSnowman, prSnowman);
    system->addParticle(endSnowmanPar);
    endSnowmanPar->setFixed(true);
    endSnowmanParRen = std::make_shared<ParticleRenderable>(flatShader, endSnowmanPar);
    HierarchicalRenderable::addChild(systemRenderable, endSnowmanParRen);

    viewer.addRenderable(endSnowman);

    //Panels
    #define PI 3.14159265
    HierarchicalRenderablePtr panel;
    float i = 15;
    int compteur = 0;
    while (i <= length -15){
        float j_middle;
        float angle = (float)((-2*(cos(20*((float)i+2.5)/length)*sin(20*((float)i+2.5)/length))));
        if (std::abs(angle) > 0.3) {
            if (angle > 0) {
                j_middle = 17*cos(20*((float)i+2.5)/length)*cos(20*((float)i+2.5)/length);
            } else {
                j_middle = width - 17*sin(20*(i+2.5)/length)*sin(20*(i+2.5)/length);
            }
            panel = buildAnAdPanel(phongShader, texShader, compteur++%3);
            panel->setLocalTransform(glm::translate(glm::mat4(), glm::vec3(i, j_middle, (maxHeight + 4 - i*maxHeight/length) -2.5)));
            panel->setLocalTransform(glm::rotate(panel->getLocalTransform(), (float)PI/2, glm::vec3(0, 0, 1)));
            panel->setLocalTransform(glm::rotate(panel->getLocalTransform(), (float)PI/9, glm::vec3(1, 0, 0)));
            panel->setLocalTransform(glm::rotate(panel->getLocalTransform(), angle, glm::vec3(0, 0, 1)));
            panel->setLocalTransform(glm::scale(panel->getLocalTransform(), glm::vec3(0.025, 5, 1)));            
            viewer.addRenderable(panel);
        }
        i+=5*(1-0.5*std::abs(angle));
    }



    // Start
    HierarchicalRenderablePtr start;
    start = buildAnAdPanel(phongShader, texShader, 4);
    start->setLocalTransform(glm::translate(glm::mat4(), glm::vec3(viewer.getCamera().getPosition().x+3, viewer.getCamera().getPosition().y, viewer.getCamera().getPosition().z-2)));
    start->setLocalTransform(glm::rotate(start->getLocalTransform(), (float)PI/50, glm::vec3(0,0,1)));
    start->setLocalTransform(glm::rotate(start->getLocalTransform(), (float)PI/6, glm::vec3(0,1,0)));
    start->setLocalTransform(glm::scale(start->getLocalTransform(), glm::vec3(0.025, 12, 8)));
    viewer.addRenderable(start);



    // Finish
    HierarchicalRenderablePtr finish;
    finish = buildAnAdPanel(phongShader, texShader, 3);
    finish->setLocalTransform(glm::translate(glm::mat4(), glm::vec3(185.0, 21.5, 12.0)));
    finish->setLocalTransform(glm::scale(finish->getLocalTransform(), glm::vec3(0.025, 10, 2)));            
    viewer.addRenderable(finish);

    HierarchicalRenderablePtr potteau1;
    potteau1 = buildAnAdPanel(phongShader, texShader, 3);
    potteau1->setLocalTransform(glm::translate(glm::mat4(), glm::vec3(185.0, 17.5, 8.0)));
    potteau1->setLocalTransform(glm::scale(potteau1->getLocalTransform(), glm::vec3(0.2, 0.2, 6.3)));            
    viewer.addRenderable(potteau1);

    HierarchicalRenderablePtr potteau2;
    potteau2 = buildAnAdPanel(phongShader, texShader, 3);
    potteau2->setLocalTransform(glm::translate(glm::mat4(), glm::vec3(185.0, 25.5, 8.0)));
    potteau2->setLocalTransform(glm::scale(potteau2->getLocalTransform(), glm::vec3(0.2, 0.2, 6.3)));            
    viewer.addRenderable(potteau2);



    // Trampoline
    //Initialize particle attributes (radius, mass)
    float pr_spring = 0.1, pm_spring = 10.0;
    glm::vec3 px_spring(0.0,0.0,0.0), pv_spring(0.0,0.0,0.0);

    //Create particles on a squared uniform grid starting at origin
    std::vector<ParticlePtr> particles_spring;
    glm::vec3 origin(185.0,17.0,4.0), displacement(0.0,0.0,0.0);

    int particlePerLine = 20;
    float gridSize = 11.0;
    float xstep = gridSize / (float)(particlePerLine-1);
    float ystep = xstep;
    particles_spring.resize(particlePerLine*particlePerLine);

    for (size_t i = 0; i < particlePerLine; ++ i) {
        for (size_t j = 0; j < particlePerLine; ++ j) {
            displacement = glm::vec3(i*xstep, j*ystep, 0);
            px_spring = origin + displacement;
            particles_spring[i*particlePerLine+j] = std::make_shared<Particle>( px_spring, pv_spring, pm_spring, pr_spring );
            system->addParticle( particles_spring[i*particlePerLine+j] );
        }
    }

    //Fix particles on the borders
    for (size_t i = 0; i < particlePerLine; ++i) {
        for (size_t j = 0; j < particlePerLine; ++j) {
            if (i == 0) {
                particles_spring[j]->setFixed(true);
            }
            if (i == particlePerLine-1) {
                particles_spring[(particlePerLine-1)*particlePerLine+j]->setFixed(true);
            }
            if (j == 0) {
                particles_spring[i*particlePerLine]->setFixed(true);
            }
            if (j == particlePerLine-1) {
                particles_spring[i*particlePerLine+particlePerLine-1]->setFixed(true);
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
            SpringForceFieldPtr spring1 = std::make_shared<SpringForceField>( particles_spring[(i-1)*particlePerLine+j], particles_spring[i*particlePerLine+j], stiffness, l0, damping );
            springForceFields.push_back(spring1);
            system->addForceField(spring1);
            SpringForceFieldPtr spring2 = std::make_shared<SpringForceField>( particles_spring[i*particlePerLine+(j-1)], particles_spring[i*particlePerLine+j], stiffness, l0, damping );
            springForceFields.push_back(spring2);
            system->addForceField(spring2);
        }
    }
    //Border case 1
    for (size_t j = 1; j < particlePerLine; ++ j) {
        SpringForceFieldPtr spring = std::make_shared<SpringForceField>( particles_spring[0*particlePerLine+j], particles_spring[0*particlePerLine+(j-1)], stiffness, l0, damping );
        springForceFields.push_back(spring);
        system->addForceField(spring);
    }
    //Border case 2
    for (size_t i = 1; i < particlePerLine; ++ i) {
        SpringForceFieldPtr spring = std::make_shared<SpringForceField>( particles_spring[(i-1)*particlePerLine+0], particles_spring[i*particlePerLine+0], stiffness, l0, damping );
        springForceFields.push_back(spring);
        system->addForceField(spring);
    }

    //Initialize a force field that apply to all the particles of the system to simulate gravity
    //Add it to the system as a force field
    ConstantForceFieldPtr gravity = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0, 0, -10});
    system->addForceField(gravity);

    //Initialize a force field that apply to all the particles of the system to simulate vicosity (air friction)
    float dampingCoefficient = 0.0;
    DampingForceFieldPtr dampingFF = std::make_shared<DampingForceField>(system->getParticles(), dampingCoefficient);
    system->addForceField(dampingFF);


    //Create a particleListRenderable to efficiently visualize the particles of the system
    ParticleListRenderablePtr particle_springListRenderable = std::make_shared<ParticleListRenderable>( flatShader, particles_spring);
    HierarchicalRenderable::addChild(systemRenderable, particle_springListRenderable);

    //Create a springListRenderable to efficiently visualize the springs of the system
    SpringListRenderablePtr springsRenderable = std::make_shared<SpringListRenderable>(flatShader, springForceFields);
    HierarchicalRenderable::addChild(systemRenderable, springsRenderable);



    // Skier
    glm::vec3 positionSkier = glm::vec3(5,10,85);
    glm::vec3 velocitySkier(0.0, 0.0, 0.0);
    float massSkier = 50.0, angleSkier = 0;
    float rayonSkier = 0.5;

    ParticleSkierPtr mobile = std::make_shared<ParticleSkier>( positionSkier, velocitySkier, massSkier, rayonSkier,angleSkier,0);
    system->addParticle( mobile );
    system->addParticleSkier( mobile );

    //Create a particleRenderable for each particle of the system
    //Add them to the system renderable
    ParticleRenderableSkierPtr mobileRenderable = std::make_shared<ParticleRenderableSkier>(flatShader, mobile, &viewer, start);
    HierarchicalRenderable::addChild(systemRenderable, mobileRenderable);

    HierarchicalRenderablePtr skier = buildASkier2(phongShader,texShader);
    skier->setParentTransform(glm::translate(skier->getParentTransform(),glm::vec3(0,0,2) ));
    skier->setParentTransform(glm::rotate(skier->getParentTransform(),(glm::mediump_float)(-PI/5 - PI/2), glm::vec3(0, 0, 1)));
    skier->setParentTransform(glm::scale(skier->getParentTransform(), glm::vec3(1, 1, 1)));

    HierarchicalRenderable::addChild(mobileRenderable,skier);

    //viewer.addRenderable(skier); // masse des particules à 100

    //Initialize a force field that apply only to the mobile particle
    glm::vec3 nullForce(0.0, 0.0, 0.0);
    std::vector<ParticlePtr> vParticle;

    vParticle.push_back(mobile);

    ConstantForceFieldPtr gravityForceFieldSkier
        = std::make_shared<ConstantForceField>(vParticle, glm::vec3{0, 0, -20} );
    system->addForceField(gravityForceFieldSkier);

    ConstantForceFieldPtr force2 = std::make_shared<ConstantForceField>(vParticle, nullForce);
    system->addForceField(force2);

    // ConstantForceFieldPtr force = std::make_shared<ConstantForceField>(vSParticle, glm::vec3{0,0,-9.8} );
    // system->addForceField(force);

    //Initialize a renderable for the force field applied on the mobile particle.
    //This renderable allows to modify the attribute of the force by key/mouse events
    //Add this renderable to the systemRenderable.
    ControlledForceFieldRenderablePtr forceRenderable = std::make_shared<ControlledForceFieldRenderable>(flatShader,force2);
    HierarchicalRenderable::addChild(systemRenderable, forceRenderable);

    //Add a damping force field to the mobile.
    // DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(vParticle, 0.9);
    // system->addForceField(dampingForceField);



    //Activate collision and set the restitution coefficient to 1.0
    system->setCollisionsDetection(true);
    system->setRestitution(0.0f);
    viewer.startAnimation();
    //viewer.setAnimationLoop(true, 2.0);

}