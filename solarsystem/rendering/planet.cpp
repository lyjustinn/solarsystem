#include "planet.h"

rendering::Planet::Planet(Sphere sphere, objects::ShaderProgram shader_program, float radius, glm::vec3 colour, glm::vec3 position):
	m_sphere(sphere), m_shader(shader_program), m_radius(radius), m_colour(colour), m_position(position) {
}

void rendering::Planet::draw_planet(glm::mat4 projection, glm::mat4 view) {
	m_shader.use();
	m_shader.set_mat4("projection", projection);
	m_shader.set_mat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position);
	model = glm::scale(model, glm::vec3(m_radius));
	m_shader.set_mat4("model", model);
	m_shader.set_vec3("u_colour", m_colour);
	m_sphere.draw_sphere();
}
