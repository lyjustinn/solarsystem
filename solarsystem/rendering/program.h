#ifndef PROGRAM_H
#define PROGRAM_H

#include "../objects/camera.h"
#include "../objects/shader_program.h"
#include "sphere.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rendering {
	class Program {
	private:

		objects::ShaderProgram shader;
		rendering::Sphere sphere;

	public:
		Program();
		void render_frame(GLFWwindow*);
	};
}

#endif // !PROGRAM_H
