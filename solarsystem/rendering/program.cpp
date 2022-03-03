#include "render.h"
#include "sphere.h"
#include "../objects/shader_program.h"
#include "../objects/camera.h"
#include "program.h"

#include <iostream>
#include <vector>
#include <string>

rendering::Program::Program():
    m_cube_map("./resources/background.jpg"),
    m_sphere_shader("./shaders/v_shader.glsl", "./shaders/f_shader.glsl"),
    m_cubemap_shader("./shaders/cubemap_v_shader.glsl", "./shaders/cubemap_f_shader.glsl") {

    glEnable(GL_DEPTH_TEST);
    m_cubemap_shader.use();
    m_cubemap_shader.set_int("skybox", 0);
}

void rendering::Program::render_frame(GLFWwindow* window) {

    // per-frame logic
    float currentFrame = static_cast<float>(glfwGetTime());
    delta_time = currentFrame - last_frame;
    last_frame = currentFrame;

    // input
    process_input(window);

    // render
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_sphere_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.get_view_matrix();
    m_sphere_shader.set_mat4("projection", projection);
    m_sphere_shader.set_mat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    m_sphere_shader.set_mat4("model", model);

    m_sphere.draw_sphere();

    m_cubemap_shader.use();
    view = glm::mat4(glm::mat3(camera.get_view_matrix()));
    m_cubemap_shader.set_mat4("view", view);
    m_cubemap_shader.set_mat4("projection", projection);

    m_cube_map.draw_cubemap();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}
