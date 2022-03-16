#include "text_field.h"
#include "../rendering/render.h"

#include <iostream>

ui::TextField::TextField(float width, float height, glm::vec3 colour, glm::vec3 bg_colour, glm::vec3 position, rendering::Quad& quad,
	objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader, const char* font, float scale) :
	Button(colour, bg_colour, position, quad, shader, bg_shader, font, "" , scale)
{
	m_width = width;
	m_height = height;
	m_pad = ((m_glyphs['0'].advance >> 6)) * m_scale / rendering::scr_width;
}

bool ui::TextField::check_focus(float clickx, float clicky, float releasex, float releasey) {
	if (clickx >= m_position.x - m_pad && clickx <= m_position.x - m_pad + m_width && clicky >= m_position.y - m_height / 4.0f && clicky <= m_position.y - m_pad + 0.75f * m_height) {

		if (!m_press) {
			glm::vec3 temp = m_colour;
			m_colour = m_bg_colour;
			m_bg_colour = temp;
		}

		m_press = true;
	}
	else if (clickx != rendering::INVALID_COOR && clicky != rendering::INVALID_COOR) {

		if (m_press) {
			glm::vec3 temp = m_colour;
			m_colour = m_bg_colour;
			m_bg_colour = temp;
		}

		m_press = false;
	}

	

	return m_press;
}
void ui::TextField::callback() {
	if (!m_press) return;

	//std::cout << "textfield was focused" << std::endl;
}

void ui::TextField::draw() {
	glDepthFunc(GL_ALWAYS);
	m_bg_shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position - glm::vec3(m_pad, m_height / 4.0f, 0.0f));
	model = glm::scale(model, glm::vec3(m_width, m_height, 1.0f));
	m_bg_shader.set_mat4("u_model", model);
	m_bg_shader.set_vec3("u_colour", m_bg_colour);
	m_quad.draw();
	glDepthFunc(GL_LESS);

	TextBox::draw();
}