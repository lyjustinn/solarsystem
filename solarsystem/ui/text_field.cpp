#include "text_field.h"
#include "../rendering/render.h"

#include <iostream>

ui::TextField::TextField(glm::vec3 colour, glm::vec3 bg_colour, glm::vec3 position, rendering::Quad& quad,
	objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader, const char* font, float scale) :
	Button(colour, bg_colour, position, quad, shader, bg_shader, font, "text field" , scale)
{

}

bool ui::TextField::check_focus(float clickx, float clicky, float releasex, float releasey) {
	if (clickx >= m_position.x - m_width / 3.0f && clickx <= m_position.x + m_width * 2.0f / 3.0f && clicky >= m_position.y - m_pad * 2.0f && clicky <= m_position.y - m_pad * 2.0f + m_height) {
		m_press = true;
	}
	else if (clickx != rendering::INVALID_COOR && clicky != rendering::INVALID_COOR) {
		m_press = false;
	}

	return m_press;
}
void ui::TextField::callback() {
	if (!m_press) return;

	//std::cout << "textfield was focused" << std::endl;
}