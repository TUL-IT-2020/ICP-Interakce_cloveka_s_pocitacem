App::init() {

    //init GL context
    //...


    // for current GL context switch vsync
    glfwSwapInterval(0);            // Set V-Sync OFF.
    //glfwSwapInterval(1);          // Set V-Sync ON.

}


App::key_callback(...) {

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			std::cout << "ESC has been pressed!\n";
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
        case GLFW_KEY_ ???   :
            // if vsync is on, set vsync off
            // if vsync is off, set vsync on
        default:
            break;
        }
    }

}
