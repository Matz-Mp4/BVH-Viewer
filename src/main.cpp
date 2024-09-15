#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "../include/shader/GLSL/ShaderGLSL.hpp"
#include "../include/shader/GLSL/EBO.hpp"
#include "../include/shader/GLSL/VAO.hpp"
#include "../include/shader/GLSL/VBO.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
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
		std::cout << "Your Window did the L" << std::endl;
		glfwTerminate();
		return -1;
	}
    glfwMakeContextCurrent(window);

    //Load Glew to it confuires OpenGL
    glewInit();

    glViewport(0, 0, 600, 600);

    std::string vertex_path = "../src/glsl-files/vertex.glsl";
    std::string frag_path = "../src/glsl-files/fragment.glsl";

    ShaderGLSL shader(vertex_path.c_str(), frag_path.c_str());


    GLfloat vertices [] = {
        -0.5f, 0.0f,  0.5f,     0.5, 0.70f, 0.3,	
	    -0.5f, 0.0f, -0.5f,     0.3, 0.80f, 0.2,	
	     0.5f, 0.0f, -0.5f,     0.9, 0.50f, 0.5,	
	     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	
	     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	
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
	/* glEnable(GL_DEPTH_TEST);  */
    /* Camera camera(Vector4(0.0f, 0.0f, 2.0f)); */
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


    while (!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.active_shader();
        double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0/60 ){
            translate += step_trans;
            transform = Transformation::rotation_y(translate);
		}

        shader.set_matrix4("transformation", transform);



        // Bind the VAO so OpenGL knows to use it
        /* Matrix4 view_proj = camera.compute_view_projection(new PinHole(45.0f,1.0, 0.01f, 100.0f)); */
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
