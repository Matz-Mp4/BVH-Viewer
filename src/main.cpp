#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../include/GLSL/utils/ShaderGLSL.hpp"
#include "../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../include/light/GlobalAmbient.hpp"
#include "../include/light/PointLight.hpp"
#include "../include/light/LightGLSL.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/math/Transforamation.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
#include "../include/camera/CameraGLSL.hpp"
#include "../include/objects/GeometricObject.hpp"
#include "../include/objects/GeometricObjectGLSL.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/Sphere.hpp"
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
   
    return window;
}


int main(int argc, char* argv[]) {
    GeometricObject object;
    Matrix4 transformation = UNIT_MATRIX4; 
    bool wireframe = false;
    bool normalframe = false;
    bool defaultframe= false;
    bool gouraudframe = false;
    bool blin_phong_frame = true;
    bool toon_frame = false;
    Material material = RED_METALLIC;

    if (argc == 2) {
        object = GeometricObject(new ModelLoader(argv[1]) , material);
    }else {
        object =  GeometricObject(new Sphere(Vector4(0.0 , 0.0, 0.0), 1.5, 50, 50), material);
    }



    GLFWwindow* window = create_window(width, height);
    glewInit();
    glViewport(0, 0, width, height);
         

    std::cout << "Precompiling shaders programs ...\n\n";
    ShaderGLSL shader("../src/glsl-files/debug/debug.vert", "../src/glsl-files/debug/normal.frag");
    ShaderGLSL shader2("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/wireframe.geom");
    ShaderGLSL shader3("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/normal.geom");
    ShaderGLSL gouraud_shader("../src/glsl-files/gouraud/gouraud.vert", "../src/glsl-files/gouraud/gouraud.frag");
    ShaderGLSL blin_phong_shader("../src/glsl-files/blin-phong/blin-phong.vert", "../src/glsl-files/blin-phong/blin-phong.frag");
    ShaderGLSL toon_shader("../src/glsl-files/toon/toon.vert", "../src/glsl-files/toon/toon.frag");


    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(90, (float)width / height, 0.1f, 200.0f);
    ExportCamera* export_camera = new ExportVP();
    CameraGLSL cameraGLSL = CameraGLSL(shader.ID, export_camera, camera, pinhole_ptr );

    GeometricObjectGLSL objectGLSL(shader.ID, object.with_transformation(transformation));

    std::cout << "Allocating memory to object ...\n\n";
    objectGLSL.export_mesh();

    GlobalAmbient ambient_light = GlobalAmbient(WHITE);
    PointLight point_light = PointLight(WHITE, Vector4(10.0, 10.0, 10.0, 1.0));
    LightGLSL lightGLSL = LightGLSL(gouraud_shader.ID, ambient_light, point_light);


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
        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
            blin_phong_frame = !blin_phong_frame;
        }

        if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
            toon_frame = !toon_frame;
        }





        cameraGLSL.handle_inputs(window, width, height);
        objectGLSL.handle_inputs(window, width, height);

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
            lightGLSL.change_shader(gouraud_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            lightGLSL.export_ambient();
            lightGLSL.export_point_light();
            objectGLSL.draw();


        }

        if(blin_phong_frame) {
            blin_phong_shader.active_shader();
            cameraGLSL.change_shader(blin_phong_shader.ID);
            objectGLSL.change_shader(blin_phong_shader.ID);
            lightGLSL.change_shader(blin_phong_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            lightGLSL.export_ambient();
            lightGLSL.export_point_light();
            objectGLSL.draw();
        }

        if(toon_frame) {
            toon_shader.active_shader();
            cameraGLSL.change_shader(toon_shader.ID);
            objectGLSL.change_shader(toon_shader.ID);
            lightGLSL.change_shader(toon_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            lightGLSL.export_ambient();
            lightGLSL.export_point_light();
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
