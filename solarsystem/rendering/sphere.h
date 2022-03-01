#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include <vector>

namespace rendering {
	class Sphere {
	public:
		Sphere();

		void draw_sphere();

	private:

		void triangulate(float, float, const int, std::vector<glm::vec3> &);

		unsigned int m_vao;
		unsigned int m_vertex_count;

	};
}

#endif // !SPHERE_H
