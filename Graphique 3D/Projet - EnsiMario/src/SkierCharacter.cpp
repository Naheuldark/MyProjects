#include "../include/SkierCharacter.hpp"
#include <cmath>

std::shared_ptr<HierarchicalRenderable> buildASkier (ShaderProgramPtr phongShader, ShaderProgramPtr texShader) {

    #define PI 3.14159265
    float pisur2 = PI/2;
    MaterialPtr pearl = Material::Pearl();
    MaterialPtr emerald = Material::Emerald();
    MaterialPtr snow = Material::Snow();
    MaterialPtr ruby = Material::Ruby();
    MaterialPtr bronze = Material::Bronze();
    MaterialPtr wood = Material::Wood();
    
    std::shared_ptr<TexturedMeshRenderable> head = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/peau.jpg");
    std::shared_ptr<TexturedCubeRenderable> real_head = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/MarioHead.jpg");
    std::shared_ptr<TexturedCubeRenderable> lefthair = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/pull.png");
    std::shared_ptr<TexturedCubeRenderable> righthair = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/pull.png");
    std::shared_ptr<TexturedCubeRenderable> backhair = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/pull.png");
    std::shared_ptr<TexturedCubeRenderable> cap = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/pull.png");

    std::shared_ptr<TexturedCylinderRenderable> body1 = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedCylinderRenderable> body2 = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedCylinderRenderable> neck = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/peau.jpg");
    std::shared_ptr<TexturedConeRenderable> basin = std::make_shared<TexturedConeRenderable>(texShader,"../textures/bleu.png");

    std::shared_ptr<TexturedCylinderRenderable> collar = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/pull.png");

    std::shared_ptr<TexturedCylinderRenderable> upperLeftLeg = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedCylinderRenderable> upperRightLeg = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedMeshRenderable> leftKnee = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/bleu.png");
    std::shared_ptr<TexturedMeshRenderable> rightKnee = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/bleu.png");
    std::shared_ptr<TexturedCylinderRenderable> lowerLeftLeg = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedCylinderRenderable> lowerRightLeg = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/bleu.png");
    std::shared_ptr<TexturedMeshRenderable> leftShoulder = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/bleu.png");
    std::shared_ptr<TexturedMeshRenderable> rightShoulder = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/bleu.png");

    std::shared_ptr<TexturedCylinderRenderable> upperLeftArm = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/pull.png");
    std::shared_ptr<TexturedCylinderRenderable> upperRightArm = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/pull.png");
    std::shared_ptr<TexturedMeshRenderable> leftElbow = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/pull.png");
    std::shared_ptr<TexturedMeshRenderable> rightElbow = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/pull.png");
    std::shared_ptr<TexturedCylinderRenderable> lowerLeftArm = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/pull.png");
    std::shared_ptr<TexturedCylinderRenderable> lowerRightArm = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/pull.png");
    std::shared_ptr<TexturedMeshRenderable> leftWraist = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/gants.jpg");
    std::shared_ptr<TexturedMeshRenderable> rightWraist = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/gants.jpg");

    std::shared_ptr<TexturedMeshRenderable> lowerLeftFoot = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/marronclair.jpg");
    std::shared_ptr<TexturedMeshRenderable> lowerRightFoot = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/marronclair.jpg");
    std::shared_ptr<TexturedCylinderRenderable> leftFoot = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/marronclair.jpg");
    std::shared_ptr<TexturedCylinderRenderable> rightFoot = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/marronclair.jpg");
    std::shared_ptr<TexturedMeshRenderable> upperLeftFoot = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/marronclair.jpg");
    std::shared_ptr<TexturedMeshRenderable> upperRightFoot = std::make_shared<TexturedMeshRenderable>(texShader,"../meshes/sphere.obj","../textures/marronclair.jpg");

    std::shared_ptr<TexturedCylinderRenderable> upperLeftStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/noir-gris.jpg");
    std::shared_ptr<TexturedCylinderRenderable> upperRightStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/noir-gris.jpg");
    std::shared_ptr<TexturedCylinderRenderable> leftStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/rouge_metal.jpg");
    std::shared_ptr<TexturedCylinderRenderable> rightStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/rouge_metal.jpg");
    std::shared_ptr<TexturedCylinderRenderable> lowerLeftStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/noir-gris.jpg");
    std::shared_ptr<TexturedCylinderRenderable> lowerRightStick = std::make_shared<TexturedCylinderRenderable>(texShader,"../textures/noir-gris.jpg");

    std::shared_ptr<TexturedCubeRenderable> leftSki = std::make_shared<TexturedCubeRenderable>(texShader,"../textures/orange-yellow.jpg");
    std::shared_ptr<TexturedCubeRenderable> rightSki = std::make_shared<TexturedCubeRenderable>(texShader,"../textures/orange-yellow.jpg");
    std::shared_ptr<TexturedCubeRenderable> lowerLeftSki = std::make_shared<TexturedCubeRenderable>(texShader,"../textures/orange-yellow.jpg");
    std::shared_ptr<TexturedCubeRenderable> lowerRightSki = std::make_shared<TexturedCubeRenderable>(texShader,"../textures/orange-yellow.jpg");

    //head sphere
    glm::mat4 headParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0,0.6));
    glm::mat4 headLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.8, 0.8,0.8));
    head->setParentTransform(headParentTransform);
    head->setLocalTransform(headLocalTransform);
    head->setMaterial(pearl);

    //read head
    glm::mat4 rhParentTransform = glm::rotate(glm::mat4(), (glm::mediump_float)(M_PI/4), glm::vec3(0, 0, 1));
    rhParentTransform = glm::translate(rhParentTransform, glm::vec3(0.0, 0.0, 0.7));
    real_head->setParentTransform(rhParentTransform);
    real_head->setMaterial(pearl);

    //leftHair
    glm::mat4 lhLocalTransform = glm::translate(glm::mat4(), glm::vec3(0.5,0,0));
    lhLocalTransform = glm::scale(lhLocalTransform, glm::vec3(0.01, 1, 1));
    lefthair->setLocalTransform(lhLocalTransform);
    lefthair->setMaterial(pearl);

    // neck cylinder
    glm::mat4 neckParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0,1.5));
    glm::mat4 neckLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.1, 0.1,0.3));
    neck->setParentTransform(neckParentTransform);
    neck->setLocalTransform(neckLocalTransform);
    neck->setMaterial(pearl);

    // collar cylinder
    glm::mat4 collarParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0,1.5));
    glm::mat4 collarLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4,0.4,0.005));
    collar->setParentTransform(collarParentTransform);
    collar->setLocalTransform(collarLocalTransform);
    collar->setMaterial(pearl);

    // body1 cylinder
    glm::mat4 body1ParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0,0.1));
    glm::mat4 body1LocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4, 0.4,1.5));
    body1->setParentTransform(body1ParentTransform);
    body1->setLocalTransform(body1LocalTransform);
    body1->setMaterial(pearl);

    // body2 cylinder
    glm::mat4 body2ParentTransform = glm::mat4(1.0);
    glm::mat4 body2LocalTransform = glm::scale(glm::mat4(), glm::vec3(0.5, 0.5,0.2));
    body2->setParentTransform(body2ParentTransform);
    body2->setLocalTransform(body2LocalTransform);
    body2->setMaterial(pearl);

     // basin cone
    glm::mat4 basinParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0,0));
    glm::mat4 basinRotation = glm::rotate(glm::mat4(),(glm::mediump_float)PI,glm::vec3(1.0,1.0,0.0));
    glm::mat4 basinLocalTransform = glm::scale(basinRotation,glm::vec3(0.5, 0.5,0.4));
    basin->setParentTransform(basinParentTransform);
    basin->setLocalTransform(basinLocalTransform);
    basin->setMaterial(pearl);

    // right upper leg cylinder
    glm::mat4 upperRightLegParentTransform = glm::translate(glm::mat4(), glm::vec3(0.1, 0.1,0.0));
    glm::mat4 upperRightLegRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/6),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 upperRightLegLocalTransform = glm::scale(upperRightLegRotation, glm::vec3(0.2, 0.2,1));
    //upperRightLeg->setParentTransform(glm::rotate(upperRightLegParentTransform,(glm::mediump_float)(PI/4),glm::vec3(1.0,1.0,0.0)));
    upperRightLeg->setParentTransform(upperRightLegParentTransform);
    upperRightLeg->setLocalTransform(upperRightLegLocalTransform);
    upperRightLeg->setMaterial(pearl);

      // right knee
    glm::mat4 rightKneeParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.3, 0.5,-1.0));
    glm::mat4 rightKneeLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4, 0.4,0.4));
    rightKnee->setParentTransform(rightKneeParentTransform);
    rightKnee->setLocalTransform(rightKneeLocalTransform);
    rightKnee->setMaterial(pearl);

    // right lower leg cylinder
    glm::mat4 lowerRightLegParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1, -0.1,0.0));
    glm::mat4 lowerRightLegRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(-PI/6),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerRightLegLocalTransform = glm::scale(lowerRightLegRotation, glm::vec3(0.15, 0.15,1));
    lowerRightLeg->setParentTransform(lowerRightLegParentTransform);
    lowerRightLeg->setLocalTransform(lowerRightLegLocalTransform);
    lowerRightLeg->setMaterial(pearl);

    //lower right foot 
    glm::mat4 lowerRightFootParentTransform = glm::translate(glm::mat4(), glm::vec3(0.5, -0.3,-1.0));
    glm::mat4 lowerRightFootLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.27, 0.27,0.27));
    lowerRightFoot->setParentTransform(lowerRightFootParentTransform);
    lowerRightFoot->setLocalTransform(lowerRightFootLocalTransform);
    lowerRightFoot->setMaterial(pearl);

    // right foot cylinder
    glm::mat4 rightFootParentTransform = glm::translate(glm::mat4(), glm::vec3(0.3, -0.5,0));
    glm::mat4 rightFootRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/2),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 rightFootLocalTransform = glm::scale(rightFootRotation, glm::vec3(0.12, 0.12,0.5));
    rightFoot->setParentTransform(rightFootParentTransform);
    rightFoot->setLocalTransform(rightFootLocalTransform);
    rightFoot->setMaterial(pearl);

    //upper right foot 
    glm::mat4 upperRightFootParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,0));
    glm::mat4 upperRightFootLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.24, 0.24,0.24));
    upperRightFoot->setParentTransform(upperRightFootParentTransform);
    upperRightFoot->setLocalTransform(upperRightFootLocalTransform);
    upperRightFoot->setMaterial(pearl);

      // left upper leg cylinder
    glm::mat4 upperLeftLegParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1, -0.1,0.0));
    glm::mat4 upperLeftLegRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/6),glm::vec3(1.0,1.0,0.0)),glm::vec3(-0.1,-0.1,-1.1));
    glm::mat4 upperLeftLegLocalTransform = glm::scale(upperLeftLegRotation, glm::vec3(0.2, 0.2,1));
    upperLeftLeg->setParentTransform(upperLeftLegParentTransform);
    upperLeftLeg->setLocalTransform(upperLeftLegLocalTransform);
    upperLeftLeg->setMaterial(pearl);

    //left knee 
    glm::mat4 leftKneeParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.5, 0.3,-1.0));
    glm::mat4 leftKneeLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4, 0.4,0.4));
    leftKnee->setParentTransform(leftKneeParentTransform);
    leftKnee->setLocalTransform(leftKneeLocalTransform);
    leftKnee->setMaterial(pearl);

    // left lower leg cylinder
    glm::mat4 lowerLeftLegParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1, -0.1,0.0));
    glm::mat4 lowerLeftLegRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(-PI/6),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerLeftLegLocalTransform = glm::scale(lowerLeftLegRotation, glm::vec3(0.15, 0.15,1));
    lowerLeftLeg->setParentTransform(lowerLeftLegParentTransform);
    lowerLeftLeg->setLocalTransform(lowerLeftLegLocalTransform);
    lowerLeftLeg->setMaterial(pearl);

    //lower left foot 
    glm::mat4 lowerLeftFootParentTransform = glm::translate(glm::mat4(), glm::vec3(0.5, -0.3,-1.0));
    glm::mat4 lowerLeftFootLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.24, 0.24,0.24));
    lowerLeftFoot->setParentTransform(lowerLeftFootParentTransform);
    lowerLeftFoot->setLocalTransform(lowerLeftFootLocalTransform);
    lowerLeftFoot->setMaterial(pearl);

    // left foot cylinder
    glm::mat4 leftFootParentTransform = glm::translate(glm::mat4(), glm::vec3(0.3, -0.5,0));
    glm::mat4 leftFootRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/2),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 leftFootLocalTransform = glm::scale(leftFootRotation, glm::vec3(0.12, 0.12,0.5));
    leftFoot->setParentTransform(leftFootParentTransform);
    leftFoot->setLocalTransform(leftFootLocalTransform);
    leftFoot->setMaterial(pearl);

    //upper left foot 
    glm::mat4 upperLeftFootParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,0));
    glm::mat4 upperLeftFootLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.24, 0.24,0.24));
    upperLeftFoot->setParentTransform(upperLeftFootParentTransform);
    upperLeftFoot->setLocalTransform(upperLeftFootLocalTransform);
    upperLeftFoot->setMaterial(pearl);

    //right shoulder
    glm::mat4 rightShoulderParentTransform = glm::translate(glm::mat4(), glm::vec3(0.25, 0.25,1.35));
    glm::mat4 rightShoulderLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4, 0.4,0.4));
    rightShoulder->setParentTransform(rightShoulderParentTransform);
    rightShoulder->setLocalTransform(rightShoulderLocalTransform);
    rightShoulder->setMaterial(pearl);

    // right upper arm cylinder 
    glm::mat4 upperRightArmParentTransform = glm::translate(glm::mat4(), glm::vec3(0,-0.01,0.1));
    glm::mat4 upperRightArmRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 upperRightArmLocalTransform = glm::scale(upperRightArmRotation, glm::vec3(0.15, 0.15,1));
    upperRightArm->setParentTransform(upperRightArmParentTransform);
    upperRightArm->setLocalTransform(upperRightArmLocalTransform);
    upperRightArm->setMaterial(pearl);

    //right elbow
    glm::mat4 rightElbowParentTransform = glm::translate(glm::mat4(), glm::vec3(0.1,0.1,-1.12));
    glm::mat4 rightElbowLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.3, 0.3,0.3));
    rightElbow->setParentTransform(rightElbowParentTransform);
    rightElbow->setLocalTransform(rightElbowLocalTransform);
    rightElbow->setMaterial(pearl);

    // right lower arm cylinder
    glm::mat4 lowerRightArmParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1, -0.1,0.0));
    glm::mat4 lowerRightArmRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/2),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerRightArmLocalTransform = glm::scale(lowerRightArmRotation, glm::vec3(0.12, 0.12,1));
    lowerRightArm->setParentTransform(lowerRightArmParentTransform);
    lowerRightArm->setLocalTransform(lowerRightArmLocalTransform);
    lowerRightArm->setMaterial(pearl);

    //right wraist
    glm::mat4 rightWraistParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,0));
    glm::mat4 rightWraistLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.24, 0.24,0.24));
    rightWraist->setParentTransform(rightWraistParentTransform);
    rightWraist->setLocalTransform(rightWraistLocalTransform);
    rightWraist->setMaterial(pearl);

    //left shoulder
    glm::mat4 leftShoulderParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.25, -0.25,1.35));
    glm::mat4 leftShoulderLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.4, 0.4,0.4));
    leftShoulder->setParentTransform(leftShoulderParentTransform);
    leftShoulder->setLocalTransform(leftShoulderLocalTransform);
    leftShoulder->setMaterial(pearl);

    // left upper arm cylinder
    glm::mat4 upperLeftArmParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.22,-0.24,0.1));
    glm::mat4 upperLeftArmRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 upperLeftArmLocalTransform = glm::scale(upperLeftArmRotation, glm::vec3(0.15, 0.15,1));
    upperLeftArm->setParentTransform(upperLeftArmParentTransform);
    upperLeftArm->setLocalTransform(upperLeftArmLocalTransform);
    upperLeftArm->setMaterial(pearl);

    //left elbow
    glm::mat4 leftElbowParentTransform = glm::translate(glm::mat4(), glm::vec3(0.1,0.1,-1.12));
    glm::mat4 leftElbowLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.3, 0.3,0.3));
    leftElbow->setParentTransform(leftElbowParentTransform);
    leftElbow->setLocalTransform(leftElbowLocalTransform);
    leftElbow->setMaterial(pearl);

    // left lower arm cylinder
    glm::mat4 lowerLeftArmParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1, -0.1,0.0));
    glm::mat4 lowerLeftArmRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(PI/2),glm::vec3(1.0,1.0,0.0)),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerLeftArmLocalTransform = glm::scale(lowerLeftArmRotation, glm::vec3(0.12, 0.12,1));
    lowerLeftArm->setParentTransform(lowerLeftArmParentTransform);
    lowerLeftArm->setLocalTransform(lowerLeftArmLocalTransform);
    lowerLeftArm->setMaterial(pearl);

    //left wraist
    glm::mat4 leftWraistParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,0));
    glm::mat4 leftWraistLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.24, 0.24,0.24));
    leftWraist->setParentTransform(leftWraistParentTransform);
    leftWraist->setLocalTransform(leftWraistLocalTransform);
    leftWraist->setMaterial(pearl);

    //upper right stick cylinder
    glm::mat4 upperRightStickParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1,-0.09,0.9));
    glm::mat4 upperRightStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 upperRightStickLocalTransform = glm::scale(upperRightStickRotation, glm::vec3(0.07, 0.07,0.35));
    upperRightStick->setParentTransform(upperRightStickParentTransform);
    upperRightStick->setLocalTransform(upperRightStickLocalTransform);
    upperRightStick->setMaterial(pearl);

     //right stick cylinder
    glm::mat4 rightStickParentTransform = glm::translate(glm::mat4(), glm::vec3(0,-0.02,-2.3));
    glm::mat4 rightStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 rightStickLocalTransform = glm::scale(rightStickRotation, glm::vec3(0.01, 0.01,2.55));
    rightStick->setParentTransform(rightStickParentTransform);
    rightStick->setLocalTransform(rightStickLocalTransform);
    rightStick->setMaterial(pearl);

    //lower right stick cylinder
    glm::mat4 lowerRightStickParentTransform = glm::translate(glm::mat4(), glm::vec3(0,0,0.2));
    glm::mat4 lowerRightStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerRightStickLocalTransform = glm::scale(lowerRightStickRotation, glm::vec3(0.1, 0.1,0.01));
    lowerRightStick->setParentTransform(lowerRightStickParentTransform);
    lowerRightStick->setLocalTransform(lowerRightStickLocalTransform);
    lowerRightStick->setMaterial(pearl);

    //right ski cube
    glm::mat4 rightSkiParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,-0.12));
    glm::mat4 rightSkiRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(3*PI/4),glm::vec3(0.0,0.0,1.0)),glm::vec3(-0.1,0,0));
    glm::mat4 rightSkiLocalTransform = glm::scale(rightSkiRotation, glm::vec3(3,0.2,0.01));
    rightSki->setParentTransform(rightSkiParentTransform);
    rightSki->setLocalTransform(rightSkiLocalTransform);
    rightSki->setMaterial(pearl);

    //lower right ski cube
    glm::mat4 lowerRightSkiParentTransform = glm::translate(glm::mat4(), glm::vec3(-1,1,0));
    glm::mat4 lowerRightSkiLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.2/sqrt(2),0.2/sqrt(2),0.01));
    lowerRightSki->setParentTransform(lowerRightSkiParentTransform);
    lowerRightSki->setLocalTransform(lowerRightSkiLocalTransform);
    lowerRightSki->setMaterial(pearl);


    //upper left stick cylinder
    glm::mat4 upperLeftStickParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.1,-0.09,0.9));
    glm::mat4 upperLeftStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 upperLeftStickLocalTransform = glm::scale(upperLeftStickRotation, glm::vec3(0.07, 0.07,0.35));
    upperLeftStick->setParentTransform(upperLeftStickParentTransform);
    upperLeftStick->setLocalTransform(upperLeftStickLocalTransform);
    upperLeftStick->setMaterial(pearl);

    //left stick cylinder
    glm::mat4 leftStickParentTransform = glm::translate(glm::mat4(), glm::vec3(0,-0.02,-2.3));
    glm::mat4 leftStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 leftStickLocalTransform = glm::scale(leftStickRotation, glm::vec3(0.01, 0.01,2.5));
    leftStick->setParentTransform(leftStickParentTransform);
    leftStick->setLocalTransform(leftStickLocalTransform);
    leftStick->setMaterial(pearl);

    //lower right stick cylinder
    glm::mat4 lowerLeftStickParentTransform = glm::translate(glm::mat4(), glm::vec3(0,0,0.2));
    glm::mat4 lowerLeftStickRotation = glm::translate(glm::mat4(),glm::vec3(0.1,0.1,-1.1));
    glm::mat4 lowerLeftStickLocalTransform = glm::scale(lowerLeftStickRotation, glm::vec3(0.1, 0.1,0.01));
    lowerLeftStick->setParentTransform(lowerLeftStickParentTransform);
    lowerLeftStick->setLocalTransform(lowerLeftStickLocalTransform);
    lowerLeftStick->setMaterial(pearl);

    //left ski cube
    glm::mat4 leftSkiParentTransform = glm::translate(glm::mat4(), glm::vec3(-0.7,0.9,-0.12));
    glm::mat4 leftSkiRotation = glm::translate(glm::rotate(glm::mat4(),(glm::mediump_float)(3*PI/4),glm::vec3(0.0,0.0,1.0)),glm::vec3(-0.1, 0, 0));
    glm::mat4 leftSkiLocalTransform = glm::scale(leftSkiRotation, glm::vec3(3,0.2,0.01));
    leftSki->setParentTransform(leftSkiParentTransform);
    leftSki->setLocalTransform(leftSkiLocalTransform);
    leftSki->setMaterial(pearl);

    //lower left ski cube
    glm::mat4 lowerLeftSkiParentTransform = glm::translate(glm::mat4(), glm::vec3(-1,1,0));
    glm::mat4 lowerLeftSkiLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.2/sqrt(2),0.2/sqrt(2),0.01));
    lowerLeftSki->setParentTransform(lowerLeftSkiParentTransform);
    lowerLeftSki->setLocalTransform(lowerLeftSkiLocalTransform);
    lowerLeftSki->setMaterial(pearl);


    // Define parent/children relationships
    HierarchicalRenderable::addChild(body2,body1);
    HierarchicalRenderable::addChild(body1,neck);
    HierarchicalRenderable::addChild(body1,collar);
    HierarchicalRenderable::addChild(neck,head);
    HierarchicalRenderable::addChild(neck,real_head);
    HierarchicalRenderable::addChild(real_head,lefthair);
    HierarchicalRenderable::addChild(real_head,righthair);
    HierarchicalRenderable::addChild(real_head,backhair);
    HierarchicalRenderable::addChild(real_head,cap);

    HierarchicalRenderable::addChild(body1,rightShoulder);
    HierarchicalRenderable::addChild(body1,leftShoulder);

    HierarchicalRenderable::addChild(rightShoulder,upperRightArm);
    HierarchicalRenderable::addChild(upperRightArm,rightElbow);
    HierarchicalRenderable::addChild(rightElbow,lowerRightArm);
    HierarchicalRenderable::addChild(lowerRightArm,rightWraist);

    HierarchicalRenderable::addChild(rightWraist,upperRightStick);
    HierarchicalRenderable::addChild(leftWraist,upperLeftStick);
    HierarchicalRenderable::addChild(upperRightStick,rightStick);
    HierarchicalRenderable::addChild(upperLeftStick,leftStick);
    HierarchicalRenderable::addChild(rightStick,lowerRightStick);
    HierarchicalRenderable::addChild(leftStick,lowerLeftStick);

    HierarchicalRenderable::addChild(leftShoulder,upperLeftArm);
    HierarchicalRenderable::addChild(upperLeftArm,leftElbow);
    HierarchicalRenderable::addChild(leftElbow,lowerLeftArm);
    HierarchicalRenderable::addChild(lowerLeftArm,leftWraist);

    HierarchicalRenderable::addChild(body2,basin);
    HierarchicalRenderable::addChild(basin,upperLeftLeg);
    HierarchicalRenderable::addChild(basin,upperRightLeg);

    HierarchicalRenderable::addChild(upperLeftLeg,leftKnee);
    HierarchicalRenderable::addChild(upperRightLeg,rightKnee);
    HierarchicalRenderable::addChild(leftKnee,lowerLeftLeg);
    HierarchicalRenderable::addChild(rightKnee,lowerRightLeg);

    HierarchicalRenderable::addChild(lowerRightLeg,lowerRightFoot);
    HierarchicalRenderable::addChild(lowerRightFoot,rightFoot);
    HierarchicalRenderable::addChild(lowerLeftLeg,lowerLeftFoot);
    HierarchicalRenderable::addChild(lowerLeftFoot,leftFoot);

    HierarchicalRenderable::addChild(rightFoot,upperRightFoot);
    HierarchicalRenderable::addChild(rightFoot,rightSki);
    HierarchicalRenderable::addChild(rightSki,lowerRightSki);
    HierarchicalRenderable::addChild(leftFoot,upperLeftFoot);
    HierarchicalRenderable::addChild(leftFoot,leftSki);
    HierarchicalRenderable::addChild(leftSki,lowerLeftSki);
    

    return body2;
}