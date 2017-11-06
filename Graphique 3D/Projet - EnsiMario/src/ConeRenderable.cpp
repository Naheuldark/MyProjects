#include "./../include/ConeRenderable.hpp"
#include "./../include/gl_helper.hpp"
#include "./../include/log.hpp"
#include "./../include/Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <math.h>

ConeRenderable::ConeRenderable(ShaderProgramPtr shaderProgram) :
    HierarchicalRenderable(shaderProgram),
    m_pBuffer(0), m_cBuffer(0)
{
    int nb_faces = 32;
    int h = 1;
    double r = 1.0;
    double theta = 2*M_PI/(double)nb_faces;

    glm::vec4 col_bottom = glm::vec4(0.0,0.0,0.0,1.0); // x,y,z,transparence
    glm::vec4 col_top = glm::vec4(0.0,0.0,1.0,1.0);
    
    m_positions.push_back(glm::vec3(0,0,1));
    m_colors.push_back(col_top);
    for (int i = 0; i < nb_faces; i++) {
        m_positions.push_back(glm::vec3(r*cos(i*theta),r*sin(i*theta),0));
        m_colors.push_back(glm::vec4(r*cos(i*theta),r*sin(i*theta),0.0,1.0));
    }



    for (int i = 1; i < nb_faces; i++)
        m_indices.push_back(glm::ivec3(0,i,i+1));
    m_indices.push_back(glm::ivec3(0,1,nb_faces));




    m_model = glm::mat4(1.0);


    glGenBuffers(1, &m_pBuffer);
    glGenBuffers(1, &m_cBuffer);
    glGenBuffers(1, &m_iBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glBufferData(GL_ARRAY_BUFFER, 
                 m_positions.size()*sizeof(glm::vec3), 
                 m_positions.data(), 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glBufferData(GL_ARRAY_BUFFER, 
                 m_colors.size()*sizeof(glm::vec4), 
                 m_colors.data(), 
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size()*sizeof(glm::ivec3),
                 m_indices.data(),
                 GL_STATIC_DRAW);
}

ConeRenderable::~ConeRenderable()
{
    glDeleteBuffers(1, &m_pBuffer);
    glDeleteBuffers(1, &m_cBuffer);
    glDeleteBuffers(1, &m_iBuffer);
}

void ConeRenderable::do_draw()
{
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));

    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    glEnableVertexAttribArray(positionLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
    glEnableVertexAttribArray(colorLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer);

    glDrawElements(GL_TRIANGLES, m_indices.size()*3, GL_UNSIGNED_INT, (void*)0);
        
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);

}

void ConeRenderable::do_animate(float time)
{
}
