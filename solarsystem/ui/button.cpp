#include "button.h"

#include <iostream>

ui::Button::Button(glm::vec3 colour, glm::vec3 bg_colour, glm::vec3 position, rendering::Quad& quad, 
	objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader,  const char* font, std::string text, float scale):
	TextBox(colour, position, quad, shader, font, text, scale), m_bg_shader(bg_shader), m_bg_colour(bg_colour)
{
	m_pad = m_text.length() > 0 ? m_width / m_text.length() : 0;
	m_width *= 3.0f;
	m_height += m_pad * 4.0f;
}


void ui::Button::draw() {

	// draw background
	glDepthFunc(GL_ALWAYS);
	m_bg_shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position - glm::vec3(m_width/3.0f, m_pad*2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(m_width, m_height, 1.0f));
	m_bg_shader.set_mat4("u_model", model);
	m_bg_shader.set_vec3("u_colour", m_bg_colour);
	m_quad.draw();
	glDepthFunc(GL_LESS);

	TextBox::draw();
}

bool ui::Button::check_focus(float clickx, float clicky, float releasex, float releasey) {
	if (clickx >= m_position.x - m_width / 3.0f && clickx <= m_position.x + m_width * 2.0f/3.0f && clicky >= m_position.y - m_pad * 2.0f && clicky <= m_position.y - m_pad * 2.0f + m_height) {
		m_press = true;
	}
	else m_press = false;

	if (releasex >= m_position.x - m_width / 3.0f && releasex <= m_position.x + m_width * 2.0f / 3.0f && releasey >= m_position.y - m_pad * 2.0f && releasey <= m_position.y - m_pad * 2.0f + m_height) {
		m_release = true;
	}
	else m_release = false;

	return (m_press && m_release);
}

void ui::Button::callback() {
	if (!m_press || !m_release) return;

	std::cout << "button was clicked" << std::endl;
	
}