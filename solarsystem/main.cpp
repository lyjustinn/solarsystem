#include "rendering/render.h"
#include "rendering/sphere.h"
#include "objects/camera.h"
#include "objects/shader_program.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

objects::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

float delta_time = 0;
float last_frame = 0;

float lastx = 0;
float lasty = 0;
bool first_mouse = true;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::FORWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::BACKWARD, delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::LEFT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::RIGHT, delta_time);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::UP, delta_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.process_keyboard_input(objects::CameraDirection::DOWN, delta_time);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos_in, double ypos_in)
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

    camera.process_mouse_movement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.process_mouse_scroll(static_cast<float>(yoffset));
}

GLFWwindow* create_window() {
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

int main()
{

    GLFWwindow* window = create_window();

    if (window == NULL)
        return -1;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    objects::ShaderProgram shader("./shaders/v_shader.glsl", "./shaders/f_shader.glsl");
    rendering::Sphere sphere;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame logic
        float currentFrame = static_cast<float>(glfwGetTime());
        delta_time = currentFrame - last_frame;
        last_frame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.get_view_matrix();
        shader.set_mat4("projection", projection);
        shader.set_mat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        shader.set_mat4("model", model);
        
        sphere.draw_sphere();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



