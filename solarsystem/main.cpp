#include "rendering/render.h"
#include "rendering/Program.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

int main()
{

    GLFWwindow* window = rendering::init_glfw_glad();

    if (window == NULL)
        return -1;

    rendering::Program program;

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        program.render_frame(window);
    }

    glfwTerminate();
    return 0;
}



