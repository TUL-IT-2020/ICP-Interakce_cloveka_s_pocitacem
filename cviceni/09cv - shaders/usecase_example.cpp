class App {
    ...
protected:
    std::unordered_map<std::string, Model> scene;
}

void App::init_assets(void)
{
    // load models, load textures, load shaders, initialize level, etc...
    ShaderProgram my_shader = ShaderProgram("resources/basic.vert", "resources/basic.frag");
    
    Model my_model = Model("resources/objects/whatever.obj", my_shader);

    scene.push_back("my_first_object", my_model); 
}


App::init() {
    ...
    init();
    init_assets(); // first init OpenGL, THAN init assets: valid context MUST exist  

}   

App::run() {

    glm::vec4 my_rgba = ...

    while(!glfwWindowShouldClose(window))
    {
      	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       
        ...
        
        my_shader.activate();
        // ... shader MUST be active to set its uniforms!
        my_shader.setUniform("my_color", my_rgba);
        
        //draw everything with selected shader
        for (auto const& model : scene) {
            model.draw();
        }
 
        ...
        // end of frame
        glfwSwapBuffers();
    }

}

App::~App()
{
    // clean-up
    my_shader.clear();
    other_shader.clear();
    ...
        
    std::cout << "Bye...\n";
}

