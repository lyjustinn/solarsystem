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

	extern float lastx; // last x position of mouse while dragging
	extern float lasty; // last y position of mouse while dragging
	extern bool first_mouse;
	extern bool left_mb_down;
	extern float clickx;
	extern float clicky;
	extern float releasex;
	extern float releasey;

	extern bool map_mode;

	extern unsigned int scr_width;
	extern unsigned int scr_height;
	
	// CONSTANTS
	extern const float ORBIT_DT;
	extern const float N_GRAV;
	extern const float PI;

	extern objects::Camera camera;

	void process_input(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	GLFWwindow* init_glfw_glad();
}

#endif // !RENDER_H
