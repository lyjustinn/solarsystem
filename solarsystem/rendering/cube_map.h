#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include <string>
#include <vector>

namespace rendering {
	class CubeMap {
	private:
		unsigned int m_texture;
		unsigned int m_vao;
		unsigned int m_vbo;

	public:
		CubeMap(std::string face);

		void draw_cubemap();

		static unsigned int load_cubemap(std::vector<std::string> faces);
	};
}

#endif // !CUBE_MAP_H
