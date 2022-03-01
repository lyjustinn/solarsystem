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

		static unsigned int m_vao;
		static unsigned int m_vertex_count;

	};

	unsigned int Sphere::m_vao = 0;
	unsigned int Sphere::m_vertex_count = 0;
}

#endif // !SPHERE_H
