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
    m_cubemap_shader("./shaders/cubemap_v_shader.glsl", "./shaders/cubemap_f_shader.glsl"),
    m_ui_shader("./shaders/ui_v_shader.glsl", "./shaders/ui_f_shader.glsl")
{

    // opengl config
    glEnable(GL_DEPTH_TEST);

    // init skybox texture
    m_cubemap_shader.use();
    m_cubemap_shader.set_int("skybox", 0);

    // set lighting properties
    m_planet_shader.use();
    m_planet_shader.set_vec3("u_star.ambient", glm::vec3(0.1f));
    m_planet_shader.set_vec3("u_star.diffuse", glm::vec3(0.3f));

    // attenuation to a distance of 100
    m_planet_shader.set_float("u_star.constant", 1.0f);
    m_planet_shader.set_float("u_star.linear", 0.045f);
    m_planet_shader.set_float("u_star.quadratic", 0.0075f);

    // init planets
    m_planets.emplace_back(m_sphere, m_planet_shader, 1.0f, glm::vec3(1.0f), 0.0f, 0.0f, 2.0e30);
    m_planets.emplace_back(m_sphere, m_planet_shader, 0.25f, glm::vec3(1.0f, 0.0f, 0.0f), 60e9, 50.0e3, 0.33011e24);
    m_planets.emplace_back(m_sphere, m_planet_shader, 0.25f, glm::vec3(0.0f, 1.0f, 0.0f), 110e9, 35.0e3, 4.867e24);

    // init UI
    m_ui_elements.emplace_back(0.25, 0.75, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f), m_quad, m_ui_shader);
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
    glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
    glm::mat4 view = camera.get_view_matrix();
    m_star_shader.set_mat4("projection", projection);
    m_star_shader.set_mat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    m_star_shader.set_mat4("model", model);
    m_sphere.draw_sphere();

    // draw planets
    // start at i = 1 to skip calculation for star
    // based on https://en.wikipedia.org/wiki/N-body_simulation

    for (unsigned int i = 1; i < m_planets.size(); i++) {

        glm::vec3 a_g = glm::vec3(0.0f);


        for (const rendering::Planet & planet_2 : m_planets) {
            if (m_planets[i].m_colour == planet_2.m_colour) continue;

            glm::vec3 r = m_planets[i].m_position - planet_2.m_position;

            float r_mag = glm::length(r);

            float accel = -1.0f * rendering::N_GRAV * planet_2.m_mass / (r_mag * r_mag);

            r = glm::normalize(r);

            a_g += accel * r;
        }

        m_planets[i].m_velocity += a_g * rendering::ORBIT_DT * delta_time;
        //std::cout << a_g.x << ", " << a_g.y << ", " << a_g.z << std::endl;
        //std::cout << m_planets[i].m_velocity.x << ", " << m_planets[i].m_velocity.y << ", " << m_planets[i].m_velocity.z << std::endl;
    }

    m_planet_shader.use();
    m_planet_shader.set_mat4("u_projection", projection);
    m_planet_shader.set_mat4("u_view", view);

    for (unsigned int i = 1; i < m_planets.size(); i++) {
        m_planets[i].m_position += m_planets[i].m_velocity * rendering::ORBIT_DT * delta_time;
        //std::cout << m_planets[i].m_position.x << ", " << m_planets[i].m_position.y << ", " << m_planets[i].m_position.z << std::endl;
        m_planets[i].draw_planet();
    }

    // draw ui
    for (ui::Rectangle ui_element : m_ui_elements) {
        ui_element.draw();
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
