#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../include/GLSL/utils/ShaderGLSL.hpp"
#include "../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../include/GLSL/export-data/export-object/ExportMMT.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
#include "../include/camera/CameraGLSL.hpp"
#include "../include/objects/GeometricObject.hpp"
#include "../include/objects/GeometricObjectGLSL.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/ModelLoader.hpp"

const unsigned int width = 800;
const unsigned int height = 800;

GLFWwindow* create_window( unsigned int width, unsigned int height) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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


int main(int argc, char* argv[]) {
    GeometricObject object;
    Matrix4 transformation = UNIT_MATRIX4; 
    bool wireframe = false;
    bool normalframe = false;
    bool defaultframe= true;

    if (argc == 2){
        std::cout << argv[1];
        object = GeometricObject(new ModelLoader(argv[1]) , RED_PLASTIC);
    }else if (argc == 3) {
        object = GeometricObject(new ModelLoader(argv[1]) , RED_PLASTIC);
        float value =   std::stof(argv[2]);
        transformation = Transformation::scaling(value, value, value);
    }else if ( argc == 4) {
        object = GeometricObject(new ModelLoader(argv[1]) , RED_PLASTIC);
        float value =   std::stof(argv[2]);
        transformation = Transformation::scaling(value, value, value);
        std::string mode = argv[3];
        wireframe = !mode.find("--w");
     
    }else {
        object =  GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 3.5, 0.5, 50, 50), RED_PLASTIC);
    }

        
    GLFWwindow* window = create_window(width, height);

    ShaderGLSL shader("../src/glsl-files/debug/vertex.glsl", "../src/glsl-files/debug/fragment.glsl");
    ShaderGLSL shader2("../src/glsl-files/test/vertex.glsl", "../src/glsl-files/test/fragment.glsl", "../src/glsl-files/test/wireframe.glsl");
    ShaderGLSL shader3("../src/glsl-files/test/vertex.glsl", "../src/glsl-files/test/fragment.glsl", "../src/glsl-files/test/geometry.glsl");



    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(90, (float)width / height, 0.1f, 200.0f);
    ExportCamera* export_camera = new ExportVP(shader.ID);
    ExportCamera* export_camera2 = new ExportVP(shader2.ID);
    ExportCamera* export_camera3 = new ExportVP(shader3.ID);

    /* CameraGLSL cameraGLSL = CameraGLSL(shader2.ID, camera, pinhole_ptr ); */
    CameraGLSL cameraGLSL = CameraGLSL(export_camera2, camera, pinhole_ptr );

    ExportObject* export_object = new ExportMMT(shader.ID);
    ExportObject* export_object2 = new ExportMMT(shader2.ID);
    ExportObject* export_object3 = new ExportMMT(shader2.ID);

    /* GeometricObjectGLSL objectGLSL(shader2.ID, object.with_transformation(transformation)); */
    GeometricObjectGLSL objectGLSL(export_object2, object.with_transformation(transformation));
    /* GeometricObjectGLSL objectGLSL(export_object2, object); */
    objectGLSL.export_mesh();

    // Variables that help the rotation of the pyramid
	float step_trans = 0.01f;
	double prevTime = glfwGetTime();
    float translate = 0.0;
    // Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)){
        glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            defaultframe = !defaultframe;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            wireframe = !wireframe;
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            normalframe = !normalframe;
        }
            cameraGLSL.handle_inputs(window, width, height);

        if(defaultframe) {
            shader.active_shader();
            objectGLSL.change_export(export_object);
            objectGLSL.export_transformation();
            cameraGLSL.handle_inputs(window, width, height);
            cameraGLSL.change_export(export_camera);
            cameraGLSL.export_projection();
            objectGLSL.draw();
        }



        if(normalframe) {
            shader2.active_shader();
            objectGLSL.change_export(export_object2);
            objectGLSL.export_transformation();
            cameraGLSL.change_export(export_camera2);
            /* cameraGLSL.handle_inputs(window, width, height); */
            cameraGLSL.export_projection();
            objectGLSL.draw();

        }

        if(wireframe) {
            shader3.active_shader();
            objectGLSL.change_export(export_object3);
            objectGLSL.export_transformation();
            cameraGLSL.change_export(export_camera3);
            /* cameraGLSL.handle_inputs(window, width, height); */
            cameraGLSL.export_projection();
            objectGLSL.draw();
        }

        
        
        


        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    delete pinhole_ptr;
    objectGLSL.delete_mesh();
    shader.delete_shader();
    shader2.delete_shader();
    glfwDestroyWindow(window);
    glfwTerminate();

    
    exit(EXIT_SUCCESS);
}
