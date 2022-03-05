#ifndef RENDER_H
#define RENDER_H

#include "../objects/camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace rendering {

	extern float delta_time;
	extern float last_frame;

	extern float lastx;
	extern float lasty;
	extern bool first_mouse;

	extern const unsigned int SCR_WIDTH;
	extern const unsigned int SCR_HEIGHT;
	
	// CONSTANTS
	extern const float ORBIT_DT;
	extern const float N_GRAV;
	extern const float PI;

	extern objects::Camera camera;

	void process_input(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	GLFWwindow* init_glfw_glad();
}

#endif // !RENDER_H
