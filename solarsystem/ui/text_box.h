#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include "rectangle.h"
#include "glyph.h"

#include <string>
#include <map>

namespace ui {
	class TextBox : public Element {
	public:
		TextBox(float width, float height, glm::vec3 colour, glm::vec3 position, rendering::Quad& quad, objects::ShaderProgram& shader, const char * font, std::string text, float scale);
		
		float m_scale;
		std::string m_text;
		std::map<char, Glyph> m_glyphs;
			
		void draw();
	
	private:
		void render_text();
	};
}

#endif // !TEXT_BOX_H
