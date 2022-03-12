#ifndef BUTTON_H
#define BUTTON_H

#include "text_box.h"

namespace ui {
	class Button : public TextBox {
	public:
		Button(glm::vec3 colour, glm::vec3 text_colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader, const char* font, std::string text, float scale);
	
		objects::ShaderProgram m_bg_shader;
		glm::vec3 m_bg_colour;
		bool m_press;
		bool m_release;
		float m_pad;

		virtual void callback();

		void draw() override;
	};
}

#endif // !BUTTON_H
