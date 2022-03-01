#include "shader_program.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// implementation modified from https://github.com/JoeyDeVries/LearnOpenGL

objects::ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		gShaderFile.open(geometryPath);

		std::stringstream vShaderStream, fShaderStream, gShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "A shader file was not successfully read" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	unsigned int vertex, fragment, geometry;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Compile Vertex Shader\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Compile Fragment Shader\n" << infoLog << std::endl;
	}

	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Compile Geometry Shader\n" << infoLog << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glAttachShader(m_program, geometry);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Link Shader Program\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);
}

objects::ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "A shader file was not successfully read" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Compile Vertex Shader\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Compile Fragment Shader\n" << infoLog << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, 512, NULL, infoLog);
		std::cout << "ERROR Failed to Link Shader Program\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void objects::ShaderProgram::use() const {
	glUseProgram(m_program);
}

unsigned int objects::ShaderProgram::get_program() const {
	return m_program;
}

void objects::ShaderProgram::set_int(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(m_program, name), value);
}

void objects::ShaderProgram::set_float(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(m_program, name), value);
}

void objects::ShaderProgram::set_vec2(const char* name, float x, float y) const {
	glUniform2f(glGetUniformLocation(m_program, name), x, y);
}

void objects::ShaderProgram::set_vec2(const char* name, glm::vec2 vec) const {
	set_vec2(name, vec.x, vec.y);
}

void objects::ShaderProgram::set_vec3(const char* name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(m_program, name), x, y, z);
}

void objects::ShaderProgram::set_vec3(const char* name, glm::vec3 vec) const {
	set_vec3(name, vec.x, vec.y, vec.z);
}

void objects::ShaderProgram::set_mat4(const char* name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, glm::value_ptr(value));
}