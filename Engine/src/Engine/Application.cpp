#include "Application.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"

#include <iostream>

int main()
{
    // Initialize GLFW and set OpenGL 3.3 Core
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(Screen_Width, Screen_Height, "Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize Glad" << std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex Array Object
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    Shader shader("res/shaders/basic/basicVertex.glsl", "res/shaders/basic/basicFragment.glsl");
    VertexBuffer VBO(vertices, sizeof(vertices));
    IndexBuffer IBO(indices, sizeof(indices));

    VBO.Bind();
    IBO.Bind();

    // Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // Application Loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // rendering commands
        glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean
    glfwTerminate();
    return 0;
}
