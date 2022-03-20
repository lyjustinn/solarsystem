#include "render.h"
#include "sphere.h"
#include "../objects/shader_program.h"
#include "../objects/camera.h"
#include "../ui/rectangle.h"
#include "../ui/text_box.h"
#include "../ui/button.h"
#include "../ui/text_field.h"
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
    m_ui_shader("./shaders/ui_v_shader.glsl", "./shaders/ui_f_shader.glsl"),
    m_text_shader("./shaders/text_v_shader.glsl", "./shaders/text_f_shader.glsl"),
    m_hdr("./shaders/blur_v_shader.glsl", "./shaders/blur_f_shader.glsl", "./shaders/screen_v_shader.glsl", "./shaders/screen_f_shader.glsl")
{

    // opengl config
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    // init textures and shaders
    m_cubemap_shader.use();
    m_cubemap_shader.set_int("skybox", 0);
    m_star_shader.use();
    m_star_shader.set_int("u_texture", 0);
    m_star_texture = load_texture("./resources/sun.jpg");

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
    //m_planets.emplace_back(m_sphere, m_planet_shader, 0.25f, glm::vec3(0.0f, 0.0f, 1.0f), 150e9, 29.78e3, 5.972e24);

    // init UI
    m_ui_elements.emplace_back(new ui::Rectangle(0.4, 0.75, glm::vec3(0.09f, 0.071f, 0.098f), glm::vec3(0.6f, 0.25f, 0.0), m_quad, m_ui_shader));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.72f, 0.92f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "Add Planet", 0.4f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.64f, 0.82f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "Pos.", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.64f, 0.72f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "Vel.", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.64f, 0.62f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "Mass", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.64f, 0.52f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "Radius", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.64f, 0.42f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "R:", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.75f, 0.42f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "G:", 0.3f));
    m_ui_elements.emplace_back(new ui::TextBox(glm::vec3(1.0f), glm::vec3(0.86f, 0.42f, 0.0f), m_quad, m_text_shader, "./resources/Roboto-Medium.ttf", "B:", 0.3f));
    // submit button
    m_input_elements.emplace_back(new ui::Button( glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.78f, 0.31f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", "Add", 0.3f));

    // fields for mass, velocity, position, colour
    m_input_elements.emplace_back(new ui::TextField(0.2f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.77f, 0.82f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.2f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.77f, 0.72f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.2f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.77f, 0.62f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.2f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.77f, 0.52f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.08f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.67f, 0.42f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.08f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.78f, 0.42f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    m_input_elements.emplace_back(new ui::TextField(0.08f, 0.07f, glm::vec3(1.0f), glm::vec3(0.223f, 0.243f, 0.255f), glm::vec3(0.89f, 0.42f, 0.0f), m_quad, m_text_shader, m_ui_shader, "./resources/Roboto-Medium.ttf", 0.3f));
    //m_ui_elements.emplace_back(new ui::Rectangle(0.4, 0.75, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.72f, 0.85f, 0.0f), m_quad, m_ui_shader));
}

void rendering::Program::render_frame(GLFWwindow* window) {

    // per-frame logic
    float currentFrame = static_cast<float>(glfwGetTime());
    delta_time = currentFrame - last_frame;
    last_frame = currentFrame;

    // input
    poll_inputs(window);

    // render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_hdr.prerender();

    // draw star
    m_star_shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
    glm::mat4 view = camera.get_view_matrix();
    m_star_shader.set_mat4("projection", projection);
    m_star_shader.set_mat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    m_star_shader.set_mat4("model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_star_texture);
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

    // draw skybox/cubemap
    m_cubemap_shader.use();
    view = glm::mat4(glm::mat3(camera.get_view_matrix()));
    m_cubemap_shader.set_mat4("view", view);
    m_cubemap_shader.set_mat4("projection", projection);

    m_cube_map.draw_cubemap();

    // reset fbo
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_hdr.apply_blur();
    m_hdr.render_to_screen();

    // draw ui
    for (unsigned int i = 0; i < m_ui_elements.size(); i++) {
        m_ui_elements[i]->draw();
    }

    for (unsigned int i = 0; i < m_input_elements.size(); i++) {
        m_input_elements[i]->draw();
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void rendering::Program::poll_inputs(GLFWwindow* window) {

    bool camera_lock = false;

    for (unsigned int i = 1; i < m_input_elements.size(); i++) {
        if (m_input_elements[i]->check_focus(clickx, clicky, releasex, releasey)) {
            camera_lock = true;
            switch (input_char) {
                case (GLFW_KEY_0):
                    m_input_elements[i]->m_text.push_back('0');
                    break;
                case GLFW_KEY_1:
                    m_input_elements[i]->m_text.push_back('1');
                    break;
                case GLFW_KEY_2:
                    m_input_elements[i]->m_text.push_back('2');
                    break;
                case GLFW_KEY_3:
                    m_input_elements[i]->m_text.push_back('3');
                    break;
                case GLFW_KEY_4:
                    m_input_elements[i]->m_text.push_back('4');
                    break;
                case GLFW_KEY_5:
                    m_input_elements[i]->m_text.push_back('5');
                    break;
                case GLFW_KEY_6:
                    m_input_elements[i]->m_text.push_back('6');
                    break;
                case GLFW_KEY_7:
                    m_input_elements[i]->m_text.push_back('7');
                    break;
                case GLFW_KEY_8:
                    m_input_elements[i]->m_text.push_back('8');
                    break;
                case GLFW_KEY_9:
                    m_input_elements[i]->m_text.push_back('9');
                    break;
                case GLFW_KEY_PERIOD:
                    m_input_elements[i]->m_text.push_back('.');
                    break;
                case GLFW_KEY_COMMA:
                    m_input_elements[i]->m_text.push_back(',');
                    break;
                case GLFW_KEY_BACKSPACE:
                    if (m_input_elements[i]->m_text.length() > 0)
                        m_input_elements[i]->m_text.pop_back();
                    break;
            }
            
        }
        m_input_elements[i]->callback();
    }

    if (m_input_elements[0]->check_focus(clickx, clicky, releasex, releasey))
        add_planet();

    m_input_elements[0]->callback();

    input_char = -1;

    if (!camera_lock) {
        update_camera(window);
    }

    if (releasex != rendering::INVALID_COOR && releasey != rendering::INVALID_COOR) {
        clickx = rendering::INVALID_COOR, clicky = rendering::INVALID_COOR;
        releasex = rendering::INVALID_COOR, releasey = rendering::INVALID_COOR;
    }
}

void rendering::Program::add_planet() {

    float params[7] = {};
    float base = 1e24;
    float mantissa = 0;
    float decimal_base = 1.0f;

    for (unsigned int i = 1; i < m_input_elements.size(); i++) {
        for (std::string::const_iterator c = m_input_elements[i]->m_text.begin(); c != m_input_elements[i]->m_text.end(); c++) {
            
            
            if (*c >= '0' && *c <= '9') {
                int digit = *c - '0';

                if (decimal_base == 1) mantissa *= 10.0f;

                mantissa += digit * decimal_base;
             
            } 
                
            if (*c == '.' || decimal_base != 1) {
                decimal_base /= 10.0f;
            }
        }

        params[i-1] = mantissa;
        mantissa = 0;
        decimal_base = 1.0f;
    }

    glm::vec3 colour(params[4] / 255.0f, params[5] / 255.0f, params[6] / 255.0f);

    std::cout << colour.x << "," << colour.y << "," << colour.z << std::endl;

    m_planets.emplace_back(m_sphere, m_planet_shader, params[3], colour, params[0] * 1e9, params[1] * 1e3, params[2] * 1e24);

}