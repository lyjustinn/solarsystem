#ifndef ELEMENT_H
#define ELEMENT_H

#include "../rendering/quad.h"
#include "../objects/shader_program.h"
#include <glm/glm.hpp>

namespace ui {
	class Element {

	public:
		float m_width;
		float m_height;
		bool m_press;
		bool m_release;
		glm::vec3 m_colour;
		glm::vec3 m_position;
		rendering::Quad m_quad;
		objects::ShaderProgram m_shader;

		Element(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader);

		virtual void draw();
	};
}

#endif // !ELEMENT_H
