#include "render.h"

#include <iostream>

float rendering::delta_time = 0.0f;
float rendering::last_frame = 0.0f;

float rendering::lastx = 0.0f;
float rendering::lasty = 0.0f;
bool rendering::first_mouse = true;
bool rendering::left_mb_down = false;

unsigned int rendering::scr_width = 1280;
unsigned int rendering::scr_height = 720;

const float rendering::ORBIT_DT = 3600.0f * 48.0f;
const float rendering::N_GRAV = 6.67e-11;
const float rendering::PI = 3.14159265359f;

objects::Camera rendering::camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

// functions
void rendering::process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::RIGHT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::UP, delta_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        rendering::camera.process_keyboard_input(objects::CameraDirection::DOWN, delta_time);
}

void rendering::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    scr_height = height;
    scr_width = width;
}

void rendering::mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in){ 
    if (left_mb_down) {
        float xpos = static_cast<float>(xpos_in);
        float ypos = static_cast<float>(ypos_in);
        if (first_mouse)
        {
            lastx = xpos;
            lasty = ypos;
            first_mouse = false;
        }

        float xoffset = xpos - lastx;
        float yoffset = lasty - ypos; // reversed since y-coordinates go from bottom to top

        lastx = xpos;
        lasty = ypos;

        rendering::camera.process_mouse_movement(xoffset, yoffset);
    } else
        first_mouse = true;
}

void rendering::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    rendering::camera.process_mouse_scroll(static_cast<float>(yoffset));
}

void rendering::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        left_mb_down = true;
        return;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        std::cout << "released button" << std::endl;
    }
        
    left_mb_down = false;
}

GLFWwindow * rendering::init_glfw_glad() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "Solar System", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    else {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return NULL;
        }
    }

    return window;
}