#include "element.h"

ui::Element::Element(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader):
	m_width(width), m_height(height), m_colour(colour),
	m_position(position), m_quad(quad), m_shader(shader) {

}

void ui::Element::draw() {

}