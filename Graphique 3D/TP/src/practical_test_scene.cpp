#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"

#include "../include/MeshRenderable.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void initialize_practical_test_scene(Viewer& viewer)
{
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
                                                                  "../shaders/flatFragment.glsl");
    viewer.addShaderProgram(flatShader);
   

    std::shared_ptr<MeshRenderable> OBJ = std::make_shared<MeshRenderable>(flatShader, "../meshes/sphere.obj");
    

    glm::mat4 OBJParentTransform = glm::mat4(1.0);
    OBJ->setParentTransform(OBJParentTransform);


    viewer.addRenderable(OBJ);

}
