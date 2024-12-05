#pragma once

#include <filesystem>
#include <string>
#include <vector> 
#include <glm/glm.hpp> 

#include "Vertex.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class Model
{
public:
    std::vector<Mesh> meshes;
    std::string name;
    
    // original position
    glm::vec3 origin{};
    glm::vec3 orientation{};  //rotation by x,y,z axis, in radians
    glm::vec3 scale{};
    glm::mat4 local_model_matrix{}; //for complex transformations 
    
    
    Model(const std::filesystem::path & filename, ShaderProgram & shader) {
        ...
    }

    // update position etc. based on running time
    void update(const float delta_t) {
        // origin += glm::vec3(3,0,0) * delta_t; s=s0+v*dt
    }
    
    void draw(glm::vec3 const & offset = glm::vec3(0.0),
              glm::vec3 const & rotation = glm::vec3(0.0f),
              glm::vec3 const & scale_change = glm::vec3(1.0f) ) {

        // compute complete transformation
		glm::mat4 t = glm::translate(glm::mat4(1.0f), origin);
		glm::mat4 rx = glm::rotate(glm::mat4(1.0f), orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 ry = glm::rotate(glm::mat4(1.0f), orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rz = glm::rotate(glm::mat4(1.0f), orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 s = glm::scale(glm::mat4(1.0f), scale);

		glm::mat4 m_off = glm::translate(glm::mat4(1.0f), offset);
		glm::mat4 m_rx = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 m_ry = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 m_rz = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 m_s = glm::scale(glm::mat4(1.0f), scale_change);

		glm::mat4 model_matrix = local_model_matrix * s * rz * ry * rx * t * m_s * m_rz * m_ry * m_rx * m_off;
         
        // call draw() on mesh (all meshes)
        for (auto const& mesh : meshes) {
            mesh.draw(model_matrix);  // do not forget to implement draw() overload with glm::mat4 parameter
        }
    }
    
    void draw(glm::mat4 const & model_matrix) {
        for (auto const& mesh : meshes) {
            mesh.draw(local_model_matrix * model_matrix);  // do not forget to implement...
        }
    }
}

