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
		glm::vec3 m_position;

		Planet(Sphere sphere, objects::ShaderProgram shader_program, float radius, glm::vec3 colour, glm::vec3 position);
		void draw_planet(glm::mat4 projection, glm::mat4 view);
	};
}

#endif // !PLANET_H
