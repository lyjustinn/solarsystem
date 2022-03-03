#ifndef PROGRAM_H
#define PROGRAM_H

#include "../objects/camera.h"
#include "../objects/shader_program.h"
#include "cube_map.h"
#include "sphere.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rendering {
	class Program {
	private:
		rendering::CubeMap m_cube_map;
		rendering::Sphere m_sphere;
		objects::ShaderProgram m_sphere_shader;
		objects::ShaderProgram m_cubemap_shader;

	public:
		Program();
		void render_frame(GLFWwindow*);
	};
}

#endif // !PROGRAM_H
