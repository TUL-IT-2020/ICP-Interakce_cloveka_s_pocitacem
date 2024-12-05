#include <opencv2\opencv.hpp>

int main( int argc, char * argv[])
{
    ...
    init();
    ...
    Model model(GL_TRIANGLES,"model.obj");
    
    GLuint mytex = textureInit("mytexture.png");
    
    model.texture_id = mytex;
    model2.texture_id = mytex;
    
    // this will create texture name and initialize with data,
    // camera will periodically replace with data OF SAME SIZE, CHANNELS, AND DATA TYPE 
    model_dyntex.texture_id = textureInit("will_be_used_only_for_init.png"); 
    ...
    while(1) {
        ...
        VAO.draw();
        ...
        glfwSwapBuffers();
    }
    ...
}
//=============================================================================
void init( void )
{
    // ...
    
    glEnable( GL_DEPTH_TEST ); 

    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );

    // assume ALL objects are non-transparent 
    glEnable( GL_CULL_FACE );
}
//-----------------------------------------------------------------------------

GLuint textureInit(const std::filesystem::path& file_name)
{
	cv::Mat image = cv::imread(filepath.string(), cv::IMREAD_UNCHANGED);  // Read with (potential) Alpha
	if (image.empty())	{
		throw std::runtime_error("No texture in file: " + file_name.string());
	}

    // or print warning, and generate synthetic image with checkerboard pattern 
    // using OpenCV and use as a texture replacement 

	GLuint texture = gen_tex(image);
	
	return texture;
}

GLuint App::gen_tex(cv::Mat& image)
{
	GLuint ID;

	if (image.empty()) {
        throw std::runtime_error("Image empty?\n")
    }

	// Generates an OpenGL texture object
	glCreateTextures(GL_TEXTURE_2D, 1, &ID);

	switch (image.channels()) {
	case 3:
		// Create and clear space for data - immutable format
		glTextureStorage2D(ID, 1, GL_RGB8, image.cols, image.rows);
		// Assigns the image to the OpenGL Texture object
		glTextureSubImage2D(ID, 0, 0, 0, image.cols, image.rows, GL_BGR, GL_UNSIGNED_BYTE, image.data);
		break;
	case 4:
		glTextureStorage2D(ID, 1, GL_RGBA8, image.cols, image.rows);
		glTextureSubImage2D(ID, 0, 0, 0, image.cols, image.rows, GL_BGRA, GL_UNSIGNED_BYTE, image.data);
		break;
	default:
		throw std::runtime_error("texture failed"); // Check the image, we want Alpha in this example    
	}

	// Configures the type of algorithm that is used to make the image smaller or bigger
	// nearest neighbor - ugly & fast 
	//glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	//glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// bilinear - nicer & slower
	//glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
	//glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// MIPMAP filtering + automatic MIPMAP generation - nicest, needs more memory. Notice: MIPMAP is only for image minifying.
	glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // bilinear magnifying
	glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // trilinear minifying
	glGenerateTextureMipmap(ID);  //Generate mipmaps now.

	// Configures the way the texture repeats
	glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return ID;
}


void App::run(void)
{
    ...
    while(1) {
        ...
        model.draw();
        
    // Dynamic texture (=video)
    
    // - resize/crop to square image and size of 2^n in separate thread (camera thread) using e.g.
    //     cv::resize(image, proper_image, cv::Size(512, 512), cv::INTER_LINEAR);
    //
    // - if camera has new image, load texture to GPU into prepared immutable format texture ID
    //   - this can be done in camera thread - no drawcalls (!)
    //   - or synchronize and send image to main thread and update texture data there 

    //if (new_img)
    //{
    //      glTextureSubImage2D(model_dyntex.tex_id, 0, 0, 0, proper_image.cols, proper_image.rows, GL_BGR, GL_UNSIGNED_BYTE, proper_image.data);
    //} 
        
        
        model_dyntex.draw();
        
        ...
        glfwSwapBuffers();
    }
    
    
}

void Model::draw() {    
    //activate shader with texturing support        
    basic_tex_shader.activate();
    
    // send Model, View and Projection matrix
    glUniformMatrix4fv(glGetUniformLocation(basic_tex_shader.ID, "uM_m"), 1, GL_FALSE, glm::value_ptr(mv_m));
    glUniformMatrix4fv(glGetUniformLocation(basic_tex_shader.ID, "uV_m"), 1, GL_FALSE, glm::value_ptr(mv_m));
    glUniformMatrix4fv(glGetUniformLocation(basic_tex_shader.ID, "uP_m"), 1, GL_FALSE, glm::value_ptr(mv_m));

    //set texture unit
        // - use in for loop for multitexturing, set all textures and bind to different texture units and shader variable names
        int i = 0; 
        glBindTextureUnit(GL_TEXTURE0 + i, tex_id);

        //send texture unit number to FS
        glUniform1i(glGetUniformLocation(basic_tex_shader.ID, "tex0"), i);

    // draw object using VAO (Bind+DrawElements+Unbind)
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
}
