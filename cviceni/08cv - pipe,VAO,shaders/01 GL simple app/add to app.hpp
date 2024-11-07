#include "assets.hpp"

class App {

private:
    
    //new GL stuff
    GLuint shader_prog_ID{ 0 };
    GLuint VBO_ID{ 0 };
    GLuint VAO_ID{ 0 };
    
    GLfloat r{ 1.0f }, g{ 0.0f }, b{ 0.0f }, a{ 1.0f };
    
    std::vector<vertex> triangle_vertices =
    {
    	{{0.0f,  0.5f,  0.0f}},
    	{{0.5f, -0.5f,  0.0f}},
    	{{-0.5f, -0.5f,  0.0f}}
    };
    
}

