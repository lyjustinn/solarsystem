#ifndef PLANET_H
#define PLANET_H

#include "sphere.h"
#include "../objects/shader_program.h"

#include <glm/glm.hpp>

namespace rendering {
	class Planet {
	private:
		Sphere m_sphere;
		objects::ShaderProgram m_shader;
		float m_radius;

	public:
		glm::vec3 m_colour;
		glm::vec3 m_position; // position in meters
		glm::vec3 m_velocity; // velocity in m/s
		float m_mass; // mass in kilograms

		Planet(Sphere sphere, objects::ShaderProgram shader_program, float radius, glm::vec3 colour, float position, float velocity, float mass);
		void draw_planet();

		friend bool operator== (const Planet& p1, const Planet& p2) {
			return p1.m_colour == p2.m_colour;
		}
	};
}

#endif // !PLANET_H
