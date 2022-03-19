#ifndef HDR_H
#define HDR_H

#include "../objects/shader_program.h"

#include <vector>

namespace rendering {
	class HDR {
	private:
		objects::ShaderProgram m_blur_shader;
		objects::ShaderProgram m_screen_shader;

		unsigned int m_fbo;
		unsigned int m_rbo_depth;
		unsigned int m_quad_vao;
		unsigned int m_quad_vbo;
		unsigned int m_blur_index;
		std::vector<unsigned int> m_colour_buffers;
		std::vector<unsigned int> m_pingpong_fbos;
		std::vector<unsigned int> m_pingpong_colour_buffers;

		void draw_quad();

	public:
		HDR(const char * blur_v, const char* blur_f, const char* screen_v, const char* screen_f);

		void prerender();
		void apply_blur();
		void render_to_screen();
	};
}

#endif // !HDR_H
