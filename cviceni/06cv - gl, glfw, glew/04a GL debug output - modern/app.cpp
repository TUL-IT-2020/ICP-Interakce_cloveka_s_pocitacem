
//
// ADD to your application
//

#include "gl_err_callback.h"

class App {
public:
    GLFWwindow * window;

}

App::init() {

    //...

    //...after ALL GLFW & GLEW init ...
    
	if (GLEW_ARB_debug_output)
	{
		glDebugMessageCallback(MessageCallback, 0);
		glEnable(GL_DEBUG_OUTPUT);
        
        //default is asynchronous debug output, use this to simulate glGetError() functionality
        //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        
        std::cout << "GL_DEBUG enabled." << std::endl;
	}
	else
		std::cout << "GL_DEBUG NOT SUPPORTED!" << std::endl;
}
