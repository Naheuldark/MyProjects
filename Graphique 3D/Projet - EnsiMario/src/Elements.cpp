#include "../include/Elements.hpp"

std::shared_ptr<HierarchicalRenderable> buildASmallTree (ShaderProgramPtr phongShader, ShaderProgramPtr texShader) {
	#define PI 3.14159265
    MaterialPtr wood = Material::Wood();
    MaterialPtr pearl = Material::Pearl();
    MaterialPtr snow = Material::Snow();

    //trunk
    std::shared_ptr<LightedCylinderRenderable> trunk = std::make_shared<LightedCylinderRenderable>(phongShader, wood);
    trunk->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(0.35, 0.35, 0.9)));

    //lower cone
    std::shared_ptr<TexturedMeshRenderable> lowercone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    lowercone->setParentTransform(glm::rotate(glm::translate(glm::mat4(), glm::vec3(0,0,1.5)), (float)PI/2, glm::vec3(1.0, 0.0, 0.0)));
    lowercone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(2.5, 1.5, 2.5)));
    lowercone->setMaterial(snow);

    //middle cone
    std::shared_ptr<TexturedMeshRenderable> middlecone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    middlecone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,1,0)));
    middlecone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(1.8, 1.5, 1.8)));
    middlecone->setMaterial(snow);

    //upper cone
    std::shared_ptr<LightedMeshRenderable> uppercone = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/cone.obj", snow);
    uppercone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,0.7,0)));
    uppercone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(1.1, 0.8, 1.1)));
    uppercone->setMaterial(snow);


    // Define parent/children relationships
    HierarchicalRenderable::addChild(trunk, lowercone);
    HierarchicalRenderable::addChild(lowercone, middlecone);
    HierarchicalRenderable::addChild(middlecone, uppercone);

    return trunk;
}

std::shared_ptr<HierarchicalRenderable> buildATallTree (ShaderProgramPtr phongShader, ShaderProgramPtr texShader) {
	#define PI 3.14159265
    MaterialPtr wood = Material::Wood();
    MaterialPtr pearl = Material::Pearl();
    MaterialPtr snow = Material::Snow();

    //trunk
    std::shared_ptr<LightedCylinderRenderable> trunk = std::make_shared<LightedCylinderRenderable>(phongShader, wood);
    trunk->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(0.5, 0.5, 0.9)));

    //1st cone
    std::shared_ptr<TexturedMeshRenderable> firstcone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    firstcone->setParentTransform(glm::rotate(glm::translate(glm::mat4(), glm::vec3(0,0,1.5)), (float)PI/2, glm::vec3(1.0, 0.0, 0.0)));
    firstcone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(3, 1.8, 3)));
    firstcone->setMaterial(snow);

    //2rd cone
    std::shared_ptr<TexturedMeshRenderable> secondcone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    secondcone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,1.0,0)));
    secondcone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(2.3, 1.7, 2.3)));
    secondcone->setMaterial(snow);

    //3nd cone
    std::shared_ptr<TexturedMeshRenderable> thirdcone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    thirdcone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,0.9,0)));
    thirdcone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(1.7, 1.4, 1.7)));
    thirdcone->setMaterial(snow);

    //4th cone
    std::shared_ptr<TexturedMeshRenderable> forthcone = std::make_shared<TexturedMeshRenderable>(texShader, "../meshes/cone.obj", "../textures/treeconetex.png");
    forthcone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,0.7,0)));
    forthcone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(1.1, 0.8, 1.1)));
    forthcone->setMaterial(snow);

    //5th cone
    std::shared_ptr<LightedMeshRenderable> fifthcone = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/cone.obj", snow);
    fifthcone->setParentTransform(glm::translate(glm::mat4(), glm::vec3(0,0.5,0)));
    fifthcone->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(0.7, 0.5, 0.7)));
    fifthcone->setMaterial(snow);


    // Define parent/children relationships
    HierarchicalRenderable::addChild(trunk, firstcone);
    HierarchicalRenderable::addChild(firstcone, secondcone);
    HierarchicalRenderable::addChild(secondcone, thirdcone);
    HierarchicalRenderable::addChild(thirdcone, forthcone);
    HierarchicalRenderable::addChild(forthcone, fifthcone);
    return trunk;
}

std::shared_ptr<HierarchicalRenderable> buildASnowman (ShaderProgramPtr phongShader) {

    #define PI 3.14159265
    float pisur2 = PI/2;
    MaterialPtr pearl = Material::Pearl();
    MaterialPtr emerald = Material::Emerald();
    MaterialPtr snow = Material::Snow();
    MaterialPtr ruby = Material::Ruby();
    MaterialPtr bronze = Material::Bronze();
    MaterialPtr wood = Material::Wood();
    MaterialPtr redplastic = Material::RedPlastic();
    MaterialPtr blackplastic = Material::BlackPlastic();

    std::shared_ptr<LightedMeshRenderable> bottom = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/sphere.obj", snow);
    std::shared_ptr<LightedMeshRenderable> middle = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/sphere.obj", snow);
    std::shared_ptr<LightedMeshRenderable> head = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/sphere.obj", snow);

    std::shared_ptr<LightedMeshRenderable> carrot = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/cone.obj", bronze);
    std::shared_ptr<LightedMeshRenderable> lefteye = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/icosahedron.obj", emerald);
    std::shared_ptr<LightedMeshRenderable> righteye = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/icosahedron.obj", emerald);

    std::shared_ptr<LightedMeshRenderable> button1 = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/icosahedron.obj", ruby);
    std::shared_ptr<LightedMeshRenderable> button2 = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/icosahedron.obj", ruby); 
    std::shared_ptr<LightedMeshRenderable> button3 = std::make_shared<LightedMeshRenderable>(phongShader, "../meshes/icosahedron.obj", ruby);

    //bottom sphere
    glm::mat4 bottomParentTransform = glm::mat4(1.0); 
    glm::mat4 bottomLocalTransform = glm::scale(glm::mat4(), glm::vec3(3, 3, 3));
    bottom->setParentTransform(bottomParentTransform);
    bottom->setLocalTransform(bottomLocalTransform);

    //middle sphere
    glm::mat4 middleParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 2.0));
    glm::mat4 middleLocalTransform = glm::scale(glm::mat4(), glm::vec3(2, 2, 2));
    middle->setParentTransform(middleParentTransform);
    middle->setLocalTransform(middleLocalTransform);

    //head sphere
    glm::mat4 headParentTransform = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 1.5));
    glm::mat4 headLocalTransform = glm::scale(glm::mat4(), glm::vec3(1.5, 1.5, 1.5));
    head->setParentTransform(headParentTransform);
    head->setLocalTransform(headLocalTransform);

    //carrot
    glm::mat4 carrotParentTransform = glm::translate(glm::mat4(), glm::vec3(1, 0.0, 0.0));
    glm::mat4 carrotLocalTransform = glm::scale(glm::mat4(), glm::vec3(1.2, 0.5, 0.5));
    carrotLocalTransform = glm::rotate(carrotLocalTransform, pisur2, glm::vec3(0.0, 0.0, -1.0));
    carrot->setParentTransform(carrotParentTransform);
    carrot->setLocalTransform(carrotLocalTransform);

    //lefteye
    glm::mat4 lefteyeParentTransform = glm::translate(glm::mat4(), glm::vec3(0.8, 0.0, 0.0));
    glm::mat4 lefteyeLocalTransform = glm::translate(glm::mat4(), glm::vec3(-0.2, 0.3, 0.4));
    lefteyeLocalTransform = glm::scale(lefteyeLocalTransform, glm::vec3(0.15, 0.15, 0.15));
    lefteye->setParentTransform(lefteyeParentTransform);
    lefteye->setLocalTransform(lefteyeLocalTransform);

    //righteye
    glm::mat4 righteyeParentTransform = glm::translate(glm::mat4(), glm::vec3(0.8, 0.0, 0.0));
    glm::mat4 righteyeLocalTransform = glm::translate(glm::mat4(), glm::vec3(-0.2, -0.3, 0.4));
    righteyeLocalTransform = glm::scale(righteyeLocalTransform, glm::vec3(0.15, 0.15, 0.15));
    righteye->setParentTransform(righteyeParentTransform);
    righteye->setLocalTransform(righteyeLocalTransform);

    //buttons
    glm::mat4 button1ParentTransform = glm::translate(glm::mat4(), glm::vec3(0.90, 0.0, 0.4));
    glm::mat4 buttonLocalTransform = glm::scale(glm::mat4(), glm::vec3(0.12, 0.12, 0.12));
    buttonLocalTransform = glm::rotate(buttonLocalTransform, pisur2, glm::vec3(0.0, 1.0, 0.0));
    button1->setParentTransform(button1ParentTransform);
    button1->setLocalTransform(buttonLocalTransform);

    glm::mat4 button2ParentTransform = glm::translate(glm::mat4(), glm::vec3(1.0,0.0,0.0));
    button2->setParentTransform(button2ParentTransform);
    button2->setLocalTransform(buttonLocalTransform);

    glm::mat4 button3ParentTransform = glm::translate(glm::mat4(), glm::vec3(0.90, 0.0, -0.4));
    button3->setParentTransform(button3ParentTransform);
    button3->setLocalTransform(buttonLocalTransform);

    //LEFT ARM :

     //Left Arm
    auto leftarm = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    leftarm->setLocalTransform(GeometricTransformation( glm::vec3{0,1,0}, glm::quat(), glm::vec3{0.1,0.1,1.5}).toMatrix() );
    leftarm->addParentTransformKeyframe(0.0, GeometricTransformation( glm::vec3{0,0,0.5}, glm::quat(glm::vec3(-0.4, 0, 0))) );
    leftarm->addParentTransformKeyframe(1.0, GeometricTransformation( glm::vec3{0,0.1,0.7}, glm::quat(glm::vec3(-0.7, 0, 0))) );
    leftarm->addParentTransformKeyframe(2.0, GeometricTransformation( glm::vec3{0,0,0.5}, glm::quat(glm::vec3(-0.4, 0, 0))) );
    leftarm->setMaterial(wood);

    //Left Forearm
    auto lfa = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    lfa->addParentTransformKeyframe(0.0, GeometricTransformation( glm::vec3{0,1,1.5}, glm::angleAxis( float(M_PI_4), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    lfa->addParentTransformKeyframe(1.0, GeometricTransformation( glm::vec3{0,1,1.5}, glm::angleAxis( float(2*M_PI), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    lfa->addParentTransformKeyframe(2.0, GeometricTransformation( glm::vec3{0,1,1.5}, glm::angleAxis( float(M_PI_4), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    HierarchicalRenderable::addChild(leftarm, lfa);
    lfa->setMaterial(wood);

    //RIGHT ARM :

     //Right Arm
    auto rightarm = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    rightarm->setLocalTransform(GeometricTransformation( glm::vec3{0,-1,0}, glm::quat(), glm::vec3{0.1,0.1,1.5}).toMatrix() );
    rightarm->addParentTransformKeyframe(0.0, GeometricTransformation( glm::vec3{0,0,0.5}, glm::quat(glm::vec3(0.4, 0, 0))) );
    rightarm->addParentTransformKeyframe(1.0, GeometricTransformation( glm::vec3{0,-0.1,0.7}, glm::quat(glm::vec3(0.7, 0, 0))) );
    rightarm->addParentTransformKeyframe(2.0, GeometricTransformation( glm::vec3{0,0,0.5}, glm::quat(glm::vec3(0.4, 0, 0))) );
    rightarm->setMaterial(wood);

    //right Forearm
    auto rfa = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    rfa->addParentTransformKeyframe(0.0, GeometricTransformation( glm::vec3{0,-1,1.5}, glm::angleAxis( -float(M_PI_4), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    rfa->addParentTransformKeyframe(1.0, GeometricTransformation( glm::vec3{0,-1,1.5}, glm::angleAxis( -float(2*M_PI), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    rfa->addParentTransformKeyframe(2.0, GeometricTransformation( glm::vec3{0,-1,1.5}, glm::angleAxis( -float(M_PI_4), glm::normalize(glm::vec3(1,0,0)) ), glm::vec3{0.1,0.1,1}) );
    HierarchicalRenderable::addChild(rightarm, rfa);
    rfa->setMaterial(wood);

    //HAT :

    //Lower Hat
    auto lowerhat = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    lowerhat->setLocalTransform(GeometricTransformation( glm::vec3{0,0,0}, glm::quat(), glm::vec3{0.7,0.7,0.15}).toMatrix() );
    lowerhat->addParentTransformKeyframe(0.0, GeometricTransformation( glm::vec3{0,0,0.6}, glm::quat()) );
    lowerhat->addParentTransformKeyframe(1.0, GeometricTransformation( glm::vec3{0,0,1.6}, glm::quat()) );
    lowerhat->addParentTransformKeyframe(2.0, GeometricTransformation( glm::vec3{0,0,0.6}, glm::quat()) );
    lowerhat->setMaterial(blackplastic);

    //Middle Hat
    auto middlehat = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    middlehat->setLocalTransform(GeometricTransformation( glm::vec3{0,0,0.15}, glm::quat(), glm::vec3{0.5,0.5,0.15}).toMatrix() );
    middlehat->setMaterial(redplastic);

    //Upper Hat
    auto upperhat = std::make_shared<KeyframedCylinderRenderable>(phongShader);
    upperhat->setLocalTransform(GeometricTransformation( glm::vec3{0,0,0.30}, glm::quat(), glm::vec3{0.5,0.5,1}).toMatrix() );
    upperhat->setMaterial(blackplastic);

    // Define parent/children relationships
    HierarchicalRenderable::addChild(bottom, middle);
    HierarchicalRenderable::addChild(middle, head);
    HierarchicalRenderable::addChild(head, carrot);
    HierarchicalRenderable::addChild(head, lefteye);
    HierarchicalRenderable::addChild(head, righteye);
    HierarchicalRenderable::addChild(head, lowerhat);
    HierarchicalRenderable::addChild(lowerhat, middlehat);
    HierarchicalRenderable::addChild(middlehat, upperhat);
    HierarchicalRenderable::addChild(middle, button1);
    HierarchicalRenderable::addChild(middle, button2);
    HierarchicalRenderable::addChild(middle, button3);
    HierarchicalRenderable::addChild(middle, leftarm);
    HierarchicalRenderable::addChild(middle, rightarm);


    return bottom;
}

std::shared_ptr<HierarchicalRenderable> buildAnAdPanel (ShaderProgramPtr phongShader, ShaderProgramPtr texShader, int who) {

    MaterialPtr pearl = Material::Pearl();
    std::shared_ptr<TexturedCubeRenderable> panel;
    if (who == 0)
        panel = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/panels/panelpaulinecomp.png");
    if (who == 1)
        panel = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/panels/paneljuliencomp.png");
    if (who == 2)
        panel = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/panels/panelantoinecomp.png");
    if (who == 3)
        panel = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/panels/finish.png");
    if (who == 4)
        panel = std::make_shared<TexturedCubeRenderable>(texShader, "../textures/panels/start.png");

    //panel->setLocalTransform(glm::scale(glm::mat4(), glm::vec3(0.05, 10, 2)));
    panel -> setMaterial(pearl);

    return panel;

}