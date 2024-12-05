# LAB 11

## Task 1: Explore the source code of the GL demonstration

- implement: loading texture from file
- do NOT use stbi_image library! We already have OpenCV...

## Task 2: Use dynamic texture to show camera

- option 1: texture on rectangle
  - create VAO with rectangle (from two triangles forming triangle strip, with proper texture coordinates)
  - each frame:
    - switch to perspective projection
    - draw all 3d objects
    - switch to orthographic projection
    - draw camera image as a texture applied to the rectangle, placed in corner of the screen  
- option 2: ImGUI
  - use texture with ImGUI (<https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#example-for-opengl-users>)
    - load as in Task 1

    ``` C++
    GLuint mytex = textureInit("resources/my_favourite_texture.jpg");
    ```

    - display

    ``` C++
    // get texture size (this needs to be done just once, we use immutable format)
    int my_image_width = 0;
    int my_image_height = 0;
    int miplevel = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &my_image_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &my_image_height); 

    // show texture   
    ImGui::Begin("OpenGL Texture");
    ImGui::Image((ImTextureID)(intptr_t)my_tex, ImVec2(my_image_width, my_image_height));
    ImGui::End();
    ```

## Task 3: control the time

  When the user is not looking on the screen, pause the application. (Use camera to detect a face. If there is not face, multiply delta_t by 0.0f)

## Task 4: generate level

- maze from cubes
- textured heightmap
- optional: combine both (use heightmap as a start; set some area to fixed level; place the maze on fixed level)
