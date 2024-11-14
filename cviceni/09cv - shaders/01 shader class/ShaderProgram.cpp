#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.hpp"

// set uniform according to name 
// https://docs.gl/gl4/glUniform

ShaderProgram::ShaderProgram(const std::filesystem::path& VS_file, const std::filesystem::path& FS_file)
{
	std::vector<GLuint> shader_ids;

	shader_ids.push_back(compile_shader(VS_file, GL_VERTEX_SHADER));
	shader_ids.push_back(compile_shader(FS_file, GL_FRAGMENT_SHADER));

	ID = link_shader(shader_ids);
}

inline void ShaderProgram::setUniform(const std::string& name, const float val) {
	auto loc = glGetUniformLocation(ID, name.c_str());
	if (loc == -1) {
		std::cerr << "no uniform with name:" << name << '\n';
		return;
	}
	glUniform1f(loc, val);
}

inline void ShaderProgram::setUniform(const std::string& name, const int val) {
    // TODO: implement
}

inline void ShaderProgram::setUniform(const std::string& name, const glm::vec3 val)
{
    //TODO: get location
	glUniform3fv(loc, 1, glm::value_ptr(val));
}

inline void ShaderProgram::setUniform(const std::string& name, const glm::vec4 in_vec4) {
    // TODO: implement
}

inline void ShaderProgram::setUniform(const std::string& name, const glm::mat3 val)
{
    //TODO: get location
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

inline void ShaderProgram::setUniform(const std::string& name, const glm::mat4 val) {
    // TODO: implement
}

std::string ShaderProgram::getShaderInfoLog(const GLuint obj)
{
    // TODO: implement

}

std::string ShaderProgram::getProgramInfoLog(const GLuint obj)
{
    // TODO: implement, check for result, print info & throw error (if any)

}

GLuint ShaderProgram::compile_shader(const std::filesystem::path& source_file, const GLenum type)
{
	GLuint shader_h;

    // TODO: implement

	return shader_h;
}

GLuint ShaderProgram::link_shader(const std::vector<GLuint> shader_ids)
{
	GLuint prog_h = glCreateProgram();

	for (const id : shader_ids)
		glAttachShader(prog_h, id);

	glLinkProgram(prog_h);
	{ // TODO: implement: check link result, print info & throw error (if any)
           

	}
	return prog_h;
}

std::string ShaderProgram::textFileRead(const std::filesystem::path& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Error opening file.\n");
	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}
