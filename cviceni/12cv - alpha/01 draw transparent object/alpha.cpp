class Model {
public:

//...

    /*  
    /   - transparency = final fragment alpha < 1.0; this can happen usually because
    /     - model has transparent material
    /     - model has transparent texture
    /   -> when updating material or texture, check alpha and set to TRUE when needed
    */
    bool transparent = false;   

};

//========================================================================

void App::init( void ) {
  //...

    init_assets("resources"); // transparent and non-transparent models 

  //...

    //transparency blending function
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDepthFunc(GL_LEQUAL);
}

int App::run(void) {
    ...
    ...
    while (!glfwWindowShouldClose(window))
    {

        //...
        // update all...
        //...
        
        // Draw whole scene...
        {
            std::vector<Model*> transparent;    // temporary, vector of pointers to transparent objects
            transparent.reserve(scene.size());  // reserve size for all objects to avoid reallocation

            // FIRST PART - draw all non-transparent in any order
            for (auto& m : scene) {
                if (!m.second.transparent)
                    m.second.draw();
                else
                    transparent.emplace_back(&m.second); // save pointer for painters algorithm
            }
            
            // SECOND PART - draw only transparent - painter's algorithm (sort by distance from camera, from far to near)
            std::sort(transparent.begin(), transparent.end(), [&](Model const * a, Model const * b) {
                glm::vec3 translation_a = glm::vec3(a->model_matrix[3]);  // get 3 values from last column of model matrix = translation
                glm::vec3 translation_b = glm::vec3(b->model_matrix[3]);  // dtto for model B
                return glm::distance(camera.Position, translation_a) < glm::distance(camera.Position, translation_b); // sort by distance from camera
                });

            // set GL for transparent objects
            glEnable(GL_BLEND);
            glDepthMask(GL_FALSE);
            glDisable(GL_CULL_FACE);

            // draw sorted transparent
            for (auto p : transparent) {
                p->draw();
            }
            
            // restore GL properties
            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);
            glEnable(GL_CULL_FACE);
        
        //end frame
        glfwSwapBuffers();
        ...
    }
    ...

}

