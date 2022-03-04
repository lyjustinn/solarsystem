#include "planet.h"

rendering::Planet::Planet(Sphere sphere, objects::ShaderProgram shader_program, float radius, glm::vec3 colour, glm::vec3 position):
	m_sphere(sphere), m_shader(shader_program), m_radius(radius), m_colour(colour), m_position(position) {
}

void rendering::Planet::draw_planet(glm::mat4 projection, glm::mat4 view) {
	m_shader.use();

	// set transformation matrices
	m_shader.set_mat4("u_projection", projection);
	m_shader.set_mat4("u_view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position);
	model = glm::scale(model, glm::vec3(m_radius));
	m_shader.set_mat4("u_model", model);

	// set lighting properties
	m_shader.set_vec3("u_colour", m_colour);
	m_shader.set_vec3("u_star.ambient", glm::vec3(0.1f));
	m_shader.set_vec3("u_star.diffuse", glm::vec3(0.3f));

	// attenuation to a distance of 65
	m_shader.set_float("u_star.constant", 1.0f);
	m_shader.set_float("u_star.linear", 0.07f);
	m_shader.set_float("u_star.quadratic", 0.017f);

	m_sphere.draw_sphere();
}
