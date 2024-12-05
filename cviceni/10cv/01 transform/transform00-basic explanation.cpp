int main(int argc, char* argv[])
{
  
// ...  init ...

    // set GL params
	glEnable(GL_DEPTH_TEST); // use Z buffer


//... create and activate shaders here ...
	ShaderProgram shader("resources/...", "resources/...");
	shader.activate();

    //
    // Create and set projection matrix
    // You can only set uniforms AFTER shader compile 
    //
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);    // Get GL framebuffer size	
    
	if (height <= 0) // avoid division by 0
		height = 1;

	float ratio = static_cast<float>(width) / height;
	
	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(60.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		ratio,			     // Aspect Ratio. Depends on the size of your window.
		0.1f,                // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		20000.0f              // Far clipping plane. Keep as little as possible.
	);
    
    //set uniform for shaders - projection matrix
    shader.setUniform("uProj_m", projectionMatrix);
    
    //
    // set viewport
    //
    glViewport(0, 0, width, height);
    
    //now your canvas has [0,0] in bottom left corner, and its size is [width x height] 
    
    //
    // set View matrix - no transformation (so far), e.g. identity matrix (unit matrix)
    //
   	glm::mat4 v_m = glm::identity<glm::mat4>();
    shader.setUniform("uV_m", v_m);
    
    //
    // set Model matrix - no transformations (so far), e.g. identity matrix (unit matrix)
    //
   	glm::mat4 m_m = glm::identity<glm::mat4>();
    shader.setUniform("uM_m", m_m);

    // now you are (camera is) at [0,0,0] point, looking at -Z direction  



    //some draw calls
    glDrawElements(...)   
    
    
    return EXIT_SUCCESS;
}
