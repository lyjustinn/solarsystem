#ifndef PROGRAM_H
#define PROGRAM_H

#include "../objects/camera.h"
#include "../objects/shader_program.h"
#include "cube_map.h"
#include "sphere.h"
#include "planet.h"
#include "quad.h"
#include "../ui/element.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace rendering {
	class Program {
	private:
		// rendering primitives
		rendering::CubeMap m_cube_map;
		rendering::Sphere m_sphere;
		rendering::Quad m_quad;

		// shader programs
		objects::ShaderProgram m_planet_shader;
		objects::ShaderProgram m_star_shader;
		objects::ShaderProgram m_cubemap_shader;
		objects::ShaderProgram m_ui_shader;
		objects::ShaderProgram m_text_shader;

		// objects to render
		std::vector<Planet> m_planets;
		std::vector<std::unique_ptr<ui::Element>> m_ui_elements;

	public:
		Program();
		void render_frame(GLFWwindow*);
	};
}

#endif // !PROGRAM_H
