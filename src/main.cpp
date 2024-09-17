#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

#include "../include/shader/GLSL/ShaderGLSL.hpp"
#include<glm/gtc/matrix_transform.hpp>
#include "../include/shader/GLSL/EBO.hpp"
#include "../include/shader/GLSL/VAO.hpp"
#include "../include/shader/GLSL/VBO.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"

#include <iostream>
#include <cmath>
const unsigned int width = 800;
const unsigned int height = 800;

void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {           // Loop over the rows
        for (int j = 0; j < 4; ++j) {       // Loop over the columns
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;              // New line after each row
    }
}

int main() {

    /*
     float FOVdeg = 45.0;
     float nearPlane  = 1.0;
     float farPlane = 100.0;

     ///////////OPENGL\\\\\\\\\\\\\\

     glm::vec3 Position = glm::vec3(0.0, 0.0, 0.2);
     glm::vec3 Orientation = glm::vec3(0.0, 0.0, -0.1);
     glm::vec3 Up = glm::vec3(0.0, 1.0, 0.0);

	glm::mat4 lookAt= glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	lookAt= glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    glm::mat4 view_proj = projection * lookAt;


     ///////////Mine\\\\\\\\\\\\\\
    
    Vector4 position = Vector4(0.0, 0.0, 0.2);
    Vector4 orientation = Vector4(0.0, 0.0, -0.1);
    Vector4 up = Vector4(0.0, 1.0, 0.0);

    Camera camera = Camera(position, orientation, up);
    Matrix4 m_lookAt = camera.look_at(CoordSystem::RIGH_HAND);
    Matrix4 m_projection =  Matrix4(PinHole(FOVdeg, (float)width / height,  nearPlane, farPlane).projection_matrix(CoordSystem::RIGH_HAND));
    Matrix4 m_view_proj =   m_lookAt * m_projection;

    std::cout << "LookAt Matrix OpenGL: " << std::endl;
    printMat4(lookAt);


    std::cout << "LookAt Matrix Mine: " << std::endl;
    std::cout << m_lookAt << std::endl; 


    std::cout << "Projection Matrix OpenGL: " << std::endl;
    printMat4(projection);

    std::cout << "Projection Matrix Mine: " << std::endl;
    std::cout << m_projection<< std::endl; 


    

    std::cout << "View Projection Matrix OpenGL: " << std::endl;
    printMat4(view_proj);

    std::cout << "View Projection Matrix Mine: " << std::endl;
    std::cout << m_view_proj << std::endl; 
    



    */


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Example 69", nullptr, nullptr);
    if (window == nullptr) {
		std::cerr << "Your Window did the L" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    glfwMakeContextCurrent(window);

    //Load Glew to it confuires OpenGL
    glewInit();

    glViewport(0, 0, width, height);

    std::string vertex_path = "../src/glsl-files/vertex.glsl";
    std::string frag_path = "../src/glsl-files/fragment.glsl";

    ShaderGLSL shader(vertex_path.c_str(), frag_path.c_str());

    GLfloat vertices [] = {
           /* positions    */      /*     colors     */
        -0.50f, 0.00f,  0.50f,     0.50f, 0.80f, 0.80f,
	    -0.50f, 0.00f, -0.50f,     0.30f, 0.30f, 0.30f,
	     0.50f, 0.00f, -0.50f,     0.50f, 0.50f, 0.50f,
	     0.50f, 0.00f,  0.50f,     0.83f, 0.70f, 0.44f,
	     0.00f, 0.80f,  0.00f,     0.92f, 0.86f, 0.76f
    };

    GLuint indices[] = {
        0, 1, 2,
	    0, 2, 3,
	    0, 1, 4,
	    1, 2, 4,
	    2, 3, 4,
	    3, 0, 4
    };

    VAO vao;
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
    EBO ebo(indices, sizeof(indices));    

    //Links VBO to VAO
    //Vertex Position data to layout = 0
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0 );
    //Vertex Color to layout = 1
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    //Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

	// Enables the Depth Buffer
    float unit_mtx[] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        1.0, 1.0, 0.0, 1.0
    };
    Matrix4 transform(unit_mtx); 
    
    // Variables that help the rotation of the pyramid
	float step_trans = 0.01f;
	double prevTime = glfwGetTime();
    float translate = 0.0;
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    Camera camera(Vector4(0.0f, 0.0f,  5.0f));
    Matrix4 view_proj = camera.compute_view_projection(new PinHole(90,1.0, 0.1f, 100.0f), CoordSystem::RIGH_HAND);

    while (!glfwWindowShouldClose(window)){
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.active_shader();

        double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0/60 ){
            translate += step_trans;
            transform = Transformation::rotation_x(translate)*
                        Transformation::rotation_y(translate) * 
                        Transformation::rotation_z(translate);
		}




        // Bind the VAO so OpenGL knows to use it
        shader.set_matrix4("transformation", transform);
        shader.set_matrix4("cameraProj", view_proj);
        vao.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.delete_shader();

    glfwDestroyWindow(window);

    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}
