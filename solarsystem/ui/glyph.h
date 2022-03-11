#ifndef GLYPH_H
#define GLYPH_H

#include <glm/glm.hpp>

#include <map>

namespace ui {
	struct Glyph {
		unsigned int texture;
		unsigned int width;
		unsigned int height;
		glm::ivec2 bearing;
		unsigned int advance;
	};

	std::map<char, Glyph> load_font(const char * path);
}

#endif // !GLYPH_H

