#include "render.h"
#include "sphere.h"
#include "../objects/shader_program.h"
#include "../objects/camera.h"

#include <iostream>

objects::Camera rendering::camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

float rendering::delta_time = 0;
float rendering::last_frame = 0;

float rendering::lastx = 0;
float rendering::lasty = 0;
bool rendering::first_mouse = true;

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
}

void rendering::mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in)
{
    float xpos = static_cast<float>(xpos_in);
    float ypos = static_cast<float>(ypos_in);
    if (first_mouse)
    {
        lastx = xpos;
        lastx = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // reversed since y-coordinates go from bottom to top

    lastx = xpos;
    lasty = ypos;

    rendering::camera.process_mouse_movement(xoffset, yoffset);
}

void rendering::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    rendering::camera.process_mouse_scroll(static_cast<float>(yoffset));
}

GLFWwindow* rendering::create_window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System", NULL, NULL);

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
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    return window;
}
