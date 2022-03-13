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

	// mouse data
	extern float lastx; // last x position of mouse while dragging
	extern float lasty; // last y position of mouse while dragging
	extern bool first_mouse; // whether or not to reset lastx before panning camera
	extern bool left_mb_down; // if lmb is down
	extern float clickx; // x coordinate when lmb
	extern float clicky; // y coordinate when lmb
	extern float releasex; // x coordinate when lmb released
	extern float releasey; // y coordinate when lmb reelased

	extern bool map_mode;

	extern int input_char;

	extern unsigned int scr_width;
	extern unsigned int scr_height;
	
	// CONSTANTS
	extern const float ORBIT_DT;
	extern const float N_GRAV;
	extern const float PI;
	extern const float INVALID_COOR;

	extern objects::Camera camera;

	void update_camera(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	GLFWwindow* init_glfw_glad();
}

#endif // !RENDER_H
