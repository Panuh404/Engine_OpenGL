#include "Application.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

#include "stb_image.h"

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
    VertexArray VAO;
    VAO.Bind();

    //Shader basicShader("Basic", "res/shaders/basic/basicVertex.glsl", "res/shaders/basic/basicFragment.glsl");
    //Shader textureShader("Texture","res/shaders/texture/textureVertex.glsl", "res/shaders/texture/textureFragment.glsl");
    Shader doubleTextureShader("DobleTexture","res/shaders/texture/doubleTextureVertex.glsl", "res/shaders/texture/doubleTextureFragment.glsl");

    VertexBuffer VBO(vertices3, sizeof(vertices3));
    IndexBuffer IBO(indices, sizeof(indices));

    VBO.Bind();
    IBO.Bind();

    // Texture
    Texture texture1("res/textures/container.jpg");
    Texture texture2("res/textures/awesomeface.png");

    doubleTextureShader.Bind();
    doubleTextureShader.SetInt("texture1", 0);
    doubleTextureShader.SetInt("texture2", 1);


    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // Application Loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // rendering commands
        glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        doubleTextureShader.Bind();
        texture1.Bind(0);
        texture2.Bind(1);
        VAO.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean
    glfwTerminate();
    return 0;
}
