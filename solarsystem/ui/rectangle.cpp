#include "rectangle.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

ui::Rectangle::Rectangle(float width, float height, glm::vec3 colour,
	glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader) :
	Element(width, height, colour, position, quad, shader) {
	
}
void ui::Rectangle::draw() {
	glDepthFunc(GL_ALWAYS);
	m_shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position);
	model = glm::scale(model, glm::vec3(m_width, m_height, 1.0f));
	m_shader.set_mat4("u_model", model);
	m_shader.set_vec3("u_colour", m_colour);
	m_quad.draw();
	glDepthFunc(GL_LESS);
}