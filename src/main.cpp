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
static float speed = 0.1f;
static float sensitivity = 6.0f;
static bool firstClick = true;

void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {           // Loop over the rows
        for (int j = 0; j < 4; ++j) {       // Loop over the columns
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;              // New line after each row
    }
}

void handle_inputs(GLFWwindow* window, Camera& camera) {
    // Handles key inputs for world-space movement (Up, Back, Left, Right, Front)

    // Move up (along the global Y axis)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        /* camera.eye  = speed * camera.direction + camera.eye; // Up */

        camera.eye  = Transformation::translation(0.0, 0.0, -0.1) *  camera.eye; // Up */
    }
    // Move back (along the global -Z axis)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        /* camera.eye  =   camera.eye - camera.direction * speed  ; // Back */
        camera.eye  = Transformation::translation(0.0, 0.0,  0.1) *  camera.eye; // Up */
    }
    // Move left (along the global -X axis)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        /* camera.eye  =  camera.eye - speed * (camera.direction | camera.up).normalize(); // Left */
        camera.eye  = Transformation::translation( -0.1,  0.0,  0.0) *  camera.eye; // Up */
    }
    // Move right (along the global X axis)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        /* camera.eye  = speed * camera.right + camera.eye; // Right */
        camera.eye  = Transformation::translation( 0.1,  0.0,  0.0) *  camera.eye; // Up */
    }
    // Move front (along the global Z axis)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        /* camera.eye  =  speed * camera.up + camera.eye; // Front */
        camera.eye  = Transformation::translation( 0.0 ,  -0.1,  0.0) *  camera.eye; // Up */
    }
    // Move down (along the global -Y axis)
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.eye  = Transformation::translation( 0.0,   0.1,  0.0) *  camera.eye; 
        /* camera.eye  =   camera.eye - speed * camera.up  ; // Front */
    }

    
    // Speed boost with shift
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f; // Increase speed
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f; // Reset speed
    }

    // Handles mouse inputs for rotation (camera orientation)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

        // Vertical rotation (rotate around global X axis)
        Vector4 newDirection = Transformation::rotation_x(glm::radians(-rotX)) * camera.direction;
        if (fabs(acos(newDirection.y) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
            camera.direction = newDirection;
        }

        // Horizontal rotation (rotate around global Y axis)
        camera.direction = Transformation::rotation_y(glm::radians(-rotY)) * camera.direction;
        camera.direction = camera.direction.normalize();

        // Reset the cursor to the center of the screen
        glfwSetCursorPos(window, width / 2.0, height / 2.0);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        // Show cursor when the camera is not rotating
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
        
    }
}

int main() {

    /*
    Vector4 m(1.0, 1.0, 1.0, 1.0);
    std::cout << "Translation " << std::endl;
    std::cout << "Vec4 m = " << m <<std::endl;
    m = Transformation::translation(5.0, 5.0, 5.0) * m;
    std::cout << "Vec4 m  after tranlation = " << m   <<std::endl;
    

    
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




        handle_inputs(window, camera);
        Matrix4 view_proj = camera.compute_view_projection(new PinHole(45,1.0, 0.1f, 100.0f), CoordSystem::RIGH_HAND);

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
