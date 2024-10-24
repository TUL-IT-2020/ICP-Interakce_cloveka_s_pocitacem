// Author: JJ

//
// WARNING:
// In general, you can NOT freely reorder includes!
//

// C++
// include anywhere, in any order
#include <iostream>
#include <chrono>
#include <stack>
#include <random>

// OpenCV (does not depend on GL)
#include <opencv2\opencv.hpp>

// OpenGL Extension Wrangler: allow all multiplatform GL functions
#include <GL/glew.h> 
// WGLEW = Windows GL Extension Wrangler (change for different platform) 
// platform specific functions (in this case Windows)
#include <GL/wglew.h> 

// GLFW toolkit
// Uses GL calls to open GL context, i.e. GLEW __MUST__ be first.
#include <GLFW/glfw3.h>

// OpenGL math (and other additional GL libraries, at the end)
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//---------------------------------------------------------------------
// global variables

GLFWwindow * window = null; // move App class 
//---------------------------------------------------------------------

int main(int argc, char** argv)
{
    
    // TODO: move to App::init(), add error checking! 
    {
    	// init glfw
    	// https://www.glfw.org/documentation.html
    	glfwInit();
    
    	// open window (GL canvas) with no special properties
        // https://www.glfw.org/docs/latest/quick.html#quick_create_window
    	window = glfwCreateWindow(800, 600, "OpenGL context", NULL, NULL);
        glfwMakeContextCurrent(window);
        
       	// init glew
    	// http://glew.sourceforge.net/basic.html
    	glewInit();
    	wglewInit();
    }
	
    // Application loop
    // move to App::run()
	while (!glfwWindowShouldClose(window))
	{
		// ... do_something();
		// 
		// if (condition)
        //   glfwSetWindowShouldClose(window, GLFW_TRUE);
		// 
		
		// Clear OpenGL canvas, both color buffer and Z-buffer
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}


    // move to App destructor
	if (window)
		glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}


