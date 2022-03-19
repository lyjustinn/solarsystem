#ifndef PROGRAM_H
#define PROGRAM_H

#include "../objects/camera.h"
#include "../objects/shader_program.h"
#include "cube_map.h"
#include "sphere.h"
#include "planet.h"
#include "quad.h"
#include "hdr.h"
#include "../ui/element.h"
#include "../ui/button.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace rendering {
	class Program {
	private:

		// high dynamic range
		HDR m_hdr;

		// rendering primitives
		CubeMap m_cube_map;
		Sphere m_sphere;
		Quad m_quad;

		// shader programs
		objects::ShaderProgram m_planet_shader;
		objects::ShaderProgram m_star_shader;
		objects::ShaderProgram m_cubemap_shader;
		objects::ShaderProgram m_ui_shader;
		objects::ShaderProgram m_text_shader;

		// objects to render
		std::vector<Planet> m_planets;
		std::vector<std::unique_ptr<ui::Element>> m_ui_elements;
		std::vector<std::unique_ptr<ui::Button>> m_input_elements;

		void poll_inputs(GLFWwindow *);
		void add_planet();
	public:
		Program();
		void render_frame(GLFWwindow*);
	};
}

#endif // !PROGRAM_H
