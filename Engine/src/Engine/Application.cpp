#include "Application.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

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

    Shader TestShader("Coordinate","res/shaders/transform/coordinateVexel.glsl", "res/shaders/transform/coordinateFragment.glsl");

    VertexBuffer VBO(verticesCube, sizeof(verticesCube));
    IndexBuffer IBO(indices, sizeof(indices));

    VBO.Bind();
    IBO.Bind();

    // Texture
    Texture texture1("res/textures/container.jpg");
    Texture texture2("res/textures/awesomeface.png");

    TestShader.Bind();
    TestShader.SetInt("texture1", 0);
    TestShader.SetInt("texture2", 1);


    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Application Loop
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering Commands
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render Loop
        texture1.Bind(0);
        texture2.Bind(1);

		// Model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        // View
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0));

    	// Projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::vec3 cubePositions[] = {
		    glm::vec3(0.0f,  0.0f,  0.0f),
		    glm::vec3(2.0f,  5.0f, -15.0f),
		    glm::vec3(-1.5f, -2.2f, -2.5f),
		    glm::vec3(-3.8f, -2.0f, -12.3f),
		    glm::vec3(2.4f, -0.4f, -3.5f),
		    glm::vec3(-1.7f,  3.0f, -7.5f),
		    glm::vec3(1.3f, -2.0f, -2.5f),
		    glm::vec3(1.5f,  2.0f, -2.5f),
		    glm::vec3(1.5f,  0.2f, -1.5f),
		    glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        TestShader.Bind();
        TestShader.SetMat4("model", model);
        TestShader.SetMat4("view", view);
        TestShader.SetMat4("projection", projection);
        VAO.Bind();

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            TestShader.SetMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean
    glfwTerminate();
    return 0;
}
