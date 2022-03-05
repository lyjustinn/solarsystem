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
    m_sphere(16),
    m_planet_shader("./shaders/planet_v_shader.glsl", "./shaders/planet_f_shader.glsl"),
    m_star_shader("./shaders/star_v_shader.glsl", "./shaders/star_f_shader.glsl"),
    m_cubemap_shader("./shaders/cubemap_v_shader.glsl", "./shaders/cubemap_f_shader.glsl") {

    // opengl config
    glEnable(GL_DEPTH_TEST);

    m_cubemap_shader.use();
    m_cubemap_shader.set_int("skybox", 0);

    m_planet_shader.use();
    // set lighting properties
    m_planet_shader.set_vec3("u_star.ambient", glm::vec3(0.1f));
    m_planet_shader.set_vec3("u_star.diffuse", glm::vec3(0.3f));

    // attenuation to a distance of 50
    m_planet_shader.set_float("u_star.constant", 1.0f);
    m_planet_shader.set_float("u_star.linear", 0.09f);
    m_planet_shader.set_float("u_star.quadratic", 0.032f);

    m_planets.emplace_back(m_sphere, m_planet_shader, 0.25f, glm::vec3(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
    m_planets.emplace_back(m_sphere, m_planet_shader, 0.25f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(5.0f, 0.0f, -2.0f));
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

    // draw star
    m_star_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.get_view_matrix();
    m_star_shader.set_mat4("projection", projection);
    m_star_shader.set_mat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    m_star_shader.set_mat4("model", model);
    m_sphere.draw_sphere();

    // draw planets
    for (rendering::Planet planet : m_planets) {
        planet.draw_planet(projection, view);
    }

    // draw skybox/cubemap
    m_cubemap_shader.use();
    view = glm::mat4(glm::mat3(camera.get_view_matrix()));
    m_cubemap_shader.set_mat4("view", view);
    m_cubemap_shader.set_mat4("projection", projection);

    m_cube_map.draw_cubemap();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}
