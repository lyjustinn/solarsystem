#ifndef QUAD_H
#define QUAD_H

namespace rendering {
	class Quad {
	private:
		unsigned int m_vbo;
		unsigned int m_vao;
		unsigned int m_ebo;

	public:
		Quad();
		void bind_vao();
		void draw();
	};
}

#endif // !QUAD_H
