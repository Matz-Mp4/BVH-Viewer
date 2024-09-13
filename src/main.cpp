#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "../include/shader/GLSL/ShaderGLSL.hpp"
#include "../include/shader/GLSL/EBO.hpp"
#include "../include/shader/GLSL/VAO.hpp"
#include "../include/shader/GLSL/VBO.hpp"

int main()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Example 69", nullptr, nullptr);
    if (window == NULL){
		std::cout << "You Window did the L" << std::endl;
		glfwTerminate();
		return -1;
	}
    glfwMakeContextCurrent(window);

    //Load Glew to it confuires OpenGL
    glewInit();

    glViewport(0, 0, 600, 600);

    std::string vertex_path = "/home/matz/Code/C++/Volumetric-Viewer/src/glsl-files/vertex.glsl";
    std::string frag_path = "/home/matz/Code/C++/Volumetric-Viewer/src/glsl-files/fragment.glsl";

    ShaderGLSL shader(vertex_path.c_str(), frag_path.c_str());


    GLfloat vertices [] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    };

    GLuint indices[] = {
        0, 3, 5, //Lower left  triangle
        3, 2, 4, //Lower right triangle
        5, 4, 1, //Upper       triangle
    };
    

    VAO vao;
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
    EBO ebo(indices, sizeof(indices));
    

    //Links VBO to VAO
    vao.LinkVBO(vbo, 0);
    //Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    

    while (!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.active_shader();
        // Bind the VAO so OpenGL knows to use it
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    /* ebo.Delete(); */
    shader.delete_shader();

    glfwDestroyWindow(window);
    glfwTerminate();
    

    exit(EXIT_SUCCESS);
}
