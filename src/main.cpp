#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../include/shader/GLSL/ShaderGLSL.hpp"
#include "../include/shader/GLSL/EBO.hpp"
#include "../include/shader/GLSL/VAO.hpp"
#include "../include/shader/GLSL/VBO.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
#include "../include/camera/CameraGLSL.hpp"
#include "../include/objects/GeometricObject.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Sphere.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/Cylinder.hpp"
#include "../include/objects/shapes/ModelLoader.hpp"

#include <iostream>

const unsigned int width = 600;
const unsigned int height = 600;

GLFWwindow* create_window( unsigned int width, unsigned int height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, "Volumetric-Viewer", nullptr, nullptr);
    if (window == nullptr) {
		std::cerr << "Could not open the Window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    glfwMakeContextCurrent(window);
    glewInit();
    glViewport(0, 0, width, height);
    
    return window;
}


int main() {
    GLFWwindow* window = create_window(width, height);
    std::string vertex_path = "../src/glsl-files/vertex.glsl";
    std::string frag_path = "../src/glsl-files/fragment.glsl";

    ShaderGLSL shader(vertex_path.c_str(), frag_path.c_str());

    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(84, (float)width / height, 0.1f, 100.0f);
    CameraGLSL cameraGLSL = CameraGLSL(shader.ID, camera, pinhole_ptr, "cameraProj");

    /* GeometricObject object = GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 1.5, 0.5, 50, 50), RED_PLASTIC); */
    GeometricObject object = GeometricObject(new ModelLoader("../models/bunny.ply") , RED_PLASTIC);
    /* GeometricObject object = GeometricObject(new Sphere(Vector4(0.0 , 0.0, 0.0), 1.5 , 50 , 50),RED_PLASTIC); */
    /* GeometricObject object = GeometricObject(new Cylinder(Vector4(0.0 , 0.0, 0.0), 0.5, 0.5), Material::RED_PLASTIC); */
    VAO vao;
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    VBO vbo(object.get_vertices());
	// Generates Element Buffer Object and links it to indices
    EBO ebo(object.get_indices());    
    //Vertex Position data to layout = 0
    vao.LinkAttrib(vbo, 0, 4, GL_FLOAT, sizeof(Vertex), (void*)0 );
    //Vertex Normal to layout = 1
    vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
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
    /* Matrix4 transform = Transformation::scaling(40.0, 40.0, 40.0) ; */
    
    // Variables that help the rotation of the pyramid
	float step_trans = 0.01f;
	double prevTime = glfwGetTime();
    float translate = 0.0;
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
    unsigned int indices_size = object.get_indices().size();
    shader.active_shader();

    while (!glfwWindowShouldClose(window)){
        glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
        		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0/60 ){
            translate += step_trans;
            transform = Transformation::rotation_z(translate) *
                        Transformation::rotation_y(translate) ;

            transform   = transform *  Transformation::scaling(40.0, 40.0, 40.0) ;
		}
        cameraGLSL.handle_inputs(window, width, height);
        ShaderGLSL::set_matrix4(shader.ID, "transformation", transform);
        cameraGLSL.export_projection();
        // Bind the VAO so OpenGL knows to use it
        vao.Bind();
        /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  */
        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    delete pinhole_ptr;
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.delete_shader();
    glfwDestroyWindow(window);
    glfwTerminate();

    
    exit(EXIT_SUCCESS);
}
