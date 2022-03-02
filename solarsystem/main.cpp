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

int main()
{

    GLFWwindow* window = rendering::create_window();

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
        rendering::delta_time = currentFrame - rendering::last_frame;
        rendering::last_frame = currentFrame;

        // input
        rendering::process_input(window);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(rendering::camera.m_zoom), (float)rendering::SCR_WIDTH / (float)rendering::SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = rendering::camera.get_view_matrix();
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



