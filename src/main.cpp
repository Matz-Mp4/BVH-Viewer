#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../include/GLSL/utils/ShaderGLSL.hpp"
#include "../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../include/GLSL/export-data/export-light/ExportAPD.hpp"
#include "../include/light/GlobalAmbient.hpp"
#include "../include/light/PointLight.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
#include "../include/camera/CameraGLSL.hpp"
#include "../include/objects/GeometricObject.hpp"
#include "../include/objects/GeometricObjectGLSL.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/ModelLoader.hpp"

const unsigned int width = 1600;
const unsigned int height = 900;

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
    bool defaultframe= false;
    bool gouraudframe = true;
    Material material = RED_PLASTIC;

    if (argc == 2){
        std::cout << argv[1];
        object = GeometricObject(new ModelLoader(argv[1]) , material);
    }else if (argc == 3) {
        object = GeometricObject(new ModelLoader(argv[1]) , material);
        float value =   std::stof(argv[2]);
        transformation = Transformation::scaling(value, value, value);
    }else if ( argc == 4) {
        object = GeometricObject(new ModelLoader(argv[1]) , material);
        float value =   std::stof(argv[2]);
        transformation = Transformation::scaling(value, value, value);
        std::string mode = argv[3];
        wireframe = !mode.find("--w");
     
    }else {
        object =  GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 3.5, 1.5, 500, 500), material);
    }

        
    GLFWwindow* window = create_window(width, height);

    std::cout << "Precompiling shaders programs ...\n\n";
    ShaderGLSL shader("../src/glsl-files/debug/debug.vert", "../src/glsl-files/debug/normal.frag");
    ShaderGLSL shader2("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/wireframe.geom");
    ShaderGLSL shader3("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/normal.geom");
    ShaderGLSL gouraud_shader("../src/glsl-files/gouraud/gouraud.vert", "../src/glsl-files/gouraud/gouraud.frag");


    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(90, (float)width / height, 0.1f, 200.0f);
    ExportCamera* export_camera = new ExportVP();
    CameraGLSL cameraGLSL = CameraGLSL(shader.ID, export_camera, camera, pinhole_ptr );

    GeometricObjectGLSL objectGLSL(shader.ID, object.with_transformation(transformation));

    std::cout << "Allocating memory to object ...\n\n";
    objectGLSL.export_mesh();

    GlobalAmbient ambient_light = GlobalAmbient(WHITE);
    PointLight point_light = PointLight(WHITE, Vector4(560.0, 100.0, 600.0, 1.0));
    ExportAPD export_light = ExportAPD();


	glEnable(GL_DEPTH_TEST);
    double prev_time = 0.0;
    double curr_time = 0.0;
    double time_delta;
    unsigned int counter = 0;

    
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.7f, 0.7f, 0.75f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate FPS
        curr_time = glfwGetTime();
        time_delta = curr_time - prev_time;
        counter++;
        if (time_delta >= 0.0333) { // 1.0 / 30.0
            std::string fps = std::to_string((1.0 / time_delta) * counter);
            std::string ms = std::to_string((time_delta / counter) * 1000);
            std::string title = "FPS: " + fps + " - ms: " + ms;
            std::cout << title <<"\r";
            glfwSetWindowTitle(window, title.c_str());
            prev_time = curr_time;
            counter = 0;
        }

        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            defaultframe = !defaultframe;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            wireframe = !wireframe;
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            normalframe = !normalframe;
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            gouraudframe = !gouraudframe;
        }
            cameraGLSL.handle_inputs(window, width, height);

        if(defaultframe) {
            shader.active_shader();
            cameraGLSL.change_shader(shader.ID);
            objectGLSL.change_shader(shader.ID);
            objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            objectGLSL.draw();
        }



        if(normalframe) {
            shader2.active_shader();
            cameraGLSL.change_shader(shader2.ID);
            objectGLSL.change_shader(shader2.ID);
            objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            objectGLSL.draw();
        }

        if(wireframe) {
            shader3.active_shader();
            cameraGLSL.change_shader(shader3.ID);
            objectGLSL.change_shader(shader3.ID);
            objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            objectGLSL.draw();

        }

        if(gouraudframe) {
            gouraud_shader.active_shader();
            cameraGLSL.change_shader(gouraud_shader.ID);
            objectGLSL.change_shader(gouraud_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            export_light.export_ambient(gouraud_shader.ID, ambient_light);
            export_light.export_point_light(gouraud_shader.ID, point_light);
            objectGLSL.draw();


        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    delete pinhole_ptr;
    objectGLSL.delete_mesh();
    shader.delete_shader();
    shader2.delete_shader();
    shader3.delete_shader();
    gouraud_shader.delete_shader();
    glfwDestroyWindow(window);
    glfwTerminate();

    
    exit(EXIT_SUCCESS);
}
