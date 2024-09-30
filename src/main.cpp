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
#include "../include/objects/GeometricObject.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Sphere.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/Cylinder.hpp"

#include <iostream>
#include <cmath>
const unsigned int width = 800;
const unsigned int height = 800;
static float speed = 0.1f;
static float sensitivity = 5.0f;
static bool firstClick = true;
static float prev_mouse_x = 0.0;
static float prev_mouse_y = 0.0; 

void handle_inputs(GLFWwindow* window, Camera& camera) {
    // Handles key inputs for world-space movement (Up, Back, Left, Right, Front)

    // Move up (along the global Y axis)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.eye  = camera.eye - speed * camera.forward ; // Up

        /* camera.eye  = Transformation::translation(0.0, 0.0, -0.1) *  camera.eye; // Up  */
    }
    // Move back (along the global -Z axis)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.eye  =   camera.eye + camera.forward * speed  ; // Back
        /* camera.eye  = Transformation::translation(0.0, 0.0,  0.1) *  camera.eye; // */
    }
    // Move left (along the global -X axis)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.eye  =  camera.eye - speed * (camera.direction | camera.up).normalize(); // Left
        /* camera.eye  = -speed * camera.right + camera.eye; // Right */
        /* camera.eye  = Transformation::translation( -0.1,  0.0,  0.0) *  camera.eye; //  */
    }
    // Move right (along the global X axis)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.eye  =  camera.eye + speed * (camera.direction | camera.up).normalize(); // Left
        /* camera.eye  = speed * camera.right + camera.eye; // Right */
        /* camera.eye  = Transformation::translation( 0.1,  0.0,  0.0) *  camera.eye; //  */
    }
    // Move front (along the global Z axis)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.eye  =  speed * camera.new_up + camera.eye; // Front
        /* camera.eye  = Transformation::translation( 0.0 ,  0.1,  0.0) *  camera.eye; // */
    }
    // Move down (along the global -Y axis)
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        /* camera.eye  = Transformation::translation( 0.0,   -0.1,  0.0) *  camera.eye;  */
        camera.eye  =   camera.eye - speed * camera.new_up  ; // Front
    }

    
    // Speed boost with shift
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f; // Increase speed
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f; // Reset speed
    }

    // Handles mouse inputs for rotation (camera orientation)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
        // Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */

        // Prevent camera jump on first click
        if (firstClick) {
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
            firstClick = false;
        }

        // Get cursor position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Calculate rotation based on cursor movement
        float rotX = sensitivity * (float)(mouseY - (height / 2.0)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2.0)) / width;

        // Vertical rotation (rotate around global X axis)j
        Vector4 newDirection = Transformation::rotation(glm::radians( -rotX) , (camera.direction | camera.up).normalize() ) * camera.direction;
        if (fabs(acos(newDirection.y) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
            camera.direction = newDirection;
        }
        camera.direction = Transformation::rotation(glm::radians( -rotY) , camera.up) * camera.direction;

        // Horizontal rotation (rotate around global Y axis)

        // Reset the cursor to the center of the screen
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Show cursor when the camera is not rotating
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;

        
    }
}

int main() {

    
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

    GeometricObject object = GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 1.5, 0.5, 50, 50), Material::RED_PLASTIC);
    /* GeometricObject object = GeometricObject(new Sphere(Vector4(0.0 , 0.0, 0.0), 1.5 , 50 , 50), Material::RED_PLASTIC); */
    /* GeometricObject object = GeometricObject(new Cylinder(Vector4(0.0 , 0.0, 0.0), 0.5, 0.5), Material::RED_PLASTIC); */

    VAO vao;
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    VBO vbo(object.get_vertices());
	// Generates Element Buffer Object and links it to indices
    EBO ebo(object.get_indices());    

    //Vertex Position data to layout = 0
    vao.LinkAttrib(vbo, 0, 4, GL_FLOAT, sizeof(Vertex), (void*)0 );
    //Vertex Color to layout = 1
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
    
    // Variables that help the rotation of the pyramid
	float step_trans = 0.01f;
	double prevTime = glfwGetTime();
    float translate = 0.0;
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    Matrix4 view_proj = camera.compute_view_projection(new PinHole(45, (float)width / height, 0.1f, 100.0f), CoordSystem::RIGH_HAND);

    unsigned int indices_size = object.get_indices().size();
    
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
        		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.active_shader();

        double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0/60 ){
            /* translate += step_trans; */
            /* transform = Transformation::rotation_z(translate) * */
                        /* Transformation::rotation_x(translate) ; */
                        /* Transformation::rotation_y(translate)  ; */
		}




        handle_inputs(window, camera);
        view_proj = camera.compute_view_projection(new PinHole(90, (float)width / height, 0.1f, 100.0f), CoordSystem::RIGH_HAND);

        // Bind the VAO so OpenGL knows to use it
        shader.set_matrix4("transformation", transform);
        shader.set_matrix4("cameraProj", view_proj);
        vao.Bind();
        /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  */
        glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
        /* glDrawElements(GL_TRIANGLES,indices_size, GL_UNSIGNED_INT, 0); */
        /* glDrawElements(GL_POINT, indices_size, GL_UNSIGNED_INT, 0); */
            // Draw the crosshair

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
