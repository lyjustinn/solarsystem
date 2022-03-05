#include "planet.h"
#include <iostream>

rendering::Planet::Planet(Sphere sphere, objects::ShaderProgram shader_program, float radius, glm::vec3 colour, float position, float velocity, float mass):
	m_sphere(sphere), m_shader(shader_program), m_radius(radius), m_colour(colour), 
	m_position(position, 0.0f, 0.0f), m_velocity(0.0f, 0.0f, velocity),
	m_mass(mass) {
}

void rendering::Planet::draw_planet(glm::mat4 projection, glm::mat4 view) {
	m_shader.use();

	// set transformation matrices
	m_shader.set_mat4("u_projection", projection);
	m_shader.set_mat4("u_view", view);
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, m_position / 30.0e9f);
	model = glm::scale(model, glm::vec3(m_radius));
	m_shader.set_mat4("u_model", model);

	// set lighting property
	m_shader.set_vec3("u_colour", m_colour);

	m_sphere.draw_sphere();
}