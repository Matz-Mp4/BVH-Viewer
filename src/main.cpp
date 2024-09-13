#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
float x = 0.0f;
float inc = 0.01f;

const char* vertex_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragment_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
   glShaderSource(vertexShader, 1, &vertex_source, NULL);
    glCompileShader(vertexShader);

    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_source, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgam = glCreateProgram();
    glAttachShader(shaderProgam, vertexShader);
    glAttachShader(shaderProgam, fragmentShader);
    glLinkProgram(shaderProgam);

    //Delete they now useless Vertex and fragment  shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLfloat vertices [] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3))  / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    };

    GLint indices[] = {
        0, 3, 5, //Lower left  triangle
        3, 2, 4, //Lower right triangle
        5, 4, 1, //Upper       triangle
    };
    
    //Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO, EBO;
    //Geneerate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Make the VAO the current Vertex Array Object by binding it. binding it = vinculá-lo
    glBindVertexArray(VAO);
    
    //Bind the VBO specifying it's a Array Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Inject the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Configure the Vertex Attribute so taht OpenGL know how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Enable the Vertex Attribute so taht OpenGL know to use it 
    glEnableVertexAttribArray(0);

	//Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    
        



    while (!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgam);
        glBindVertexArray(VAO);
        /* glDrawArrays(GL_TRIANGLES, 0, 3); */
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgam);

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
