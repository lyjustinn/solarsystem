#ifndef CARD_H
#define CARD_H

#include "element.h"

namespace ui {
	class Rectangle : public Element {

	public:
		Rectangle(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader);

		void draw() override;
	};
}

#endif // !CARD_H
