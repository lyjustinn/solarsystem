#include "rendering/render.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        rendering::render(window);
    }

    glfwTerminate();
    return 0;
}

