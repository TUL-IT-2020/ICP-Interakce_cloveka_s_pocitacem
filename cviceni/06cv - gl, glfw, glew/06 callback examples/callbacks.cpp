void App::error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}


void App::scroll_callback(double xoffset, double yoffset) {
    if (yoffset > 0.0) {
        std::cout << "wheel up...\n";
    }
}

void App::key_callback(int key, int scancode, int action, int mods) {
    if ((action == GLFW_PRESS) || (action == GLFW_REPEAT))
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_V:
            // TODO: toggle VSync on-off by glfwSwapInterval(...)
            // hint: create bool variable in App class to remember last choice...
                                
            break;  
        default:
            break;
        }
    }
}

