#include <iostream>



#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>


/* #define NUM_VAOs 1 */

/* GLuint vao[NUM_VAOs]; */
/* GLuint renderingProgram; */
/*
void init(GLFWwindow* window)
{
    renderingProgram = Utils::createShaderProgram("vertex.glsl", "fragment.glsl");

    glGenVertexArrays(NUM_VAOs, vao);
    glBindVertexArray(vao[0]);
}*/

float x = 0.0f;
float inc = 0.01f;

void display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the background to black, each time

    /* glUseProgram(renderingProgram); */

    x += inc;                     // switch to movin the triangle to the right
    if (x >  1.0f) inc = -0.01f; // get ptr to "offset"
    if (x < -1.0f) inc =  0.01f; // send value in "x" to "offset"

    /* GLuint offsetLocation = glGetUniformLocation(renderingProgram, "offset"); */
    /* glProgramUniform1f(renderingProgram, offsetLocation, x); */

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 1", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    /* if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) */
    /* { */
        /* exit(EXIT_FAILURE); */
    /* } */

    glfwSwapInterval(1);

    /* init(window); */

while (!glfwWindowShouldClose(window))
    {
        /* display(window, glfwGetTime()); */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
