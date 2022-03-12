#include "element.h"
#include <iostream>

ui::Element::Element(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader):
	m_width(width), m_height(height), m_colour(colour), m_position(position), 
	m_quad(quad), m_shader(shader), m_press(false), m_release(false){

}

void ui::Element::draw() {

}

void ui::Element::callback() {
	if (!m_press && !m_release) return;

	std::cout << "I was clicked" << std::endl;
}

void ui::Element::check_focus(float clickx, float clicky, float releasex, float releasey) {
	if (clickx >= m_position.x && clickx <= m_position.x + m_width && clicky >= m_position.y && clicky <= m_position.y + m_height) {
		m_press = true;
	}
	else m_press = false;

	if (releasex >= m_position.x && releasex <= m_position.x + m_width && releasey >= m_position.y && releasey <= m_position.y + m_height) {
		m_press = true;
	}
	else m_press = false;
}