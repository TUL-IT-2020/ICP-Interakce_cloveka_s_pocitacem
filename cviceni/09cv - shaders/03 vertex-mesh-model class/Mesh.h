#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp> 
#include <glm/ext.hpp>

#include "Vertex.h"
#include "ShaderProgram.h"

class Mesh {
public:
    // mesh data
    glm::vec3 origin{};
    glm::vec3 orientation{};
    
    GLuint texture_id{0}; // texture id=0  means no texture
    GLenum primitive_type = GL_POINT;
    ShaderProgram &shader;
    
    // mesh material
    glm::vec4 ambient_material{1.0f}; //white, non-transparent 
    glm::vec4 diffuse_material{1.0f}; //white, non-transparent 
    glm::vec4 specular_material{1.0f}; //white, non-transparent
    float reflectivity{1.0f}; 
    
    // indirect (indexed) draw 
	Mesh(GLenum primitive_type, ShaderProgram & shader, std::vector<vertex> const & vertices, std::vector<GLuint> const & indices, glm::vec3 const & origin, glm::vec3 const & orientation, GLuint const texture_id = 0):
        primitive_type(primitive_type),
        shader(shader),
        vertices(vertices),
        indices(indices),
        origin(origin),
        orientation(orientation),
        texture_id(texture_id)
    {
        // TODO: create and initialize VAO, VBO, EBO and parameters
    };

    
    void draw(glm::vec3 const & offset, glm::vec3 const & rotation ) {
 		if (VAO == 0) {
			std::cerr << "VAO not initialized!\n";
			return;
		}
 
        shader.activate();
        
        // for future use: set uniform variables: position, textures, etc...  
        //set texture id etc...
        //if (texture_id > 0) {
        //    ...
        //}
        
        //TODO: draw mesh: bind vertex array object, draw all elements with selected primitive type 
    }


	void clear(void) {
        texture_id = 0;
        primitive_type = GL_POINT;
        // TODO: clear rest of the member variables to safe default
        
        // TODO: delete all allocations 
        glDeleteBuffers...
        glDeleteVertexArrays...
        
    };

private:
    // OpenGL buffer IDs
    // ID = 0 is reserved (i.e. uninitalized)
     unsigned int VAO{0}, VBO{0}, EBO{0};
};
  


