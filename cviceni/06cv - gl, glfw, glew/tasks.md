# Cvičení 6
- create functional project with all libraries (OpenCV, GLFW, GLEW, GLM)
  
- modify (extend) your app
    - open OpenGL context (https://www.glfw.org/docs/latest/quick.html#quick_create_window)
        - version 4.6, CORE profile
    - add proper error and quit handling (in C++ use exceptions)
        https://www.glfw.org/docs/latest/quick.html#quick_capture_error
        https://www.glfw.org/docs/latest/quick.html#quick_key_input
    - get basic info from created OpenGL context
        - verify, that you opened at least requested version and correct profile
        - optional: get version info from glfw, glm (or other interesting info)
    - measure FPS (frame per second)
        - display FPS as a window title
    - create and register GLFW error callback
    - create and register additional callbacks (maybe empty at the moment)
    	`glfwSetKeyCallback(window, key_callback);`
    	`glfwSetFramebufferSizeCallback(window, fbsize_callback);`
    	`glfwSetCursorPosCallback(window, cursor_position_callback);`
    	`glfwSetMouseButtonCallback(window, mouse_button_callback);`
    	`glfwSetCursorPosCallback(window, cursor_position_callback);`
    	`glfwSetCursorPosCallback(window, cursor_position_callback);`
    	`glfwSetScrollCallback(window, scroll_callback);`
    - use **glewinfo.exe** (or similar on other platforms) to get list of supported versions and extensions
        - verify, that you can use debug_output
    - GL debug output
    - implement **VSync** toggle
        - use function key F12
        - modify window title to show vsync off,on
        - note: see the FPS difference  
           
             
