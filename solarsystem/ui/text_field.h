#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "button.h"

namespace ui {
	class TextField : public Button {
	public:
		TextField(glm::vec3 colour, glm::vec3 text_colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader, objects::ShaderProgram& bg_shader, const char* font, float scale);

		bool check_focus(float clickx, float clicky, float releasex, float releasey) override;
		void callback() override;
	};
}

#endif // !TEXT_FIELD_H
