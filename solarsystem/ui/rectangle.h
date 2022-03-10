#ifndef CARD_H
#define CARD_H

#include "../rendering/quad.h"
#include "../objects/shader_program.h"
#include <glm/glm.hpp>

namespace ui {
	class Rectangle {
	private:
		float m_width;
		float m_height;
		glm::vec3 m_colour;
		glm::vec3 m_position;
		rendering::Quad m_quad;
		objects::ShaderProgram m_shader;

	public:
		Rectangle(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader);

		void draw();
	};
}

#endif // !CARD_H
