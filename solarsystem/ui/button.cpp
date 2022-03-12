#include "button.h"

#include <iostream>

ui::Button::Button(glm::vec3 colour, glm::vec3 bg_colour, glm::vec3 position, rendering::Quad& quad, 
	objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader,  const char* font, std::string text, float scale):
	TextBox(colour, position, quad, shader, font, text, scale), m_bg_shader(bg_shader),
	m_bg_colour(bg_colour), m_press(false), m_release(false) 
{
	m_pad = m_width / m_text.length();
}


void ui::Button::draw() {

	// draw background
	glDepthFunc(GL_ALWAYS);
	m_bg_shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position - glm::vec3(m_pad, m_pad*2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(m_width+m_pad*2.0f, m_height+m_pad*4.0f, 1.0f));
	m_bg_shader.set_mat4("u_model", model);
	m_bg_shader.set_vec3("u_colour", m_bg_colour);
	m_quad.draw();
	glDepthFunc(GL_LESS);

	TextBox::draw();
}

void ui::Button::callback() {
	std::cout << "I was clicked" << std::endl;
}