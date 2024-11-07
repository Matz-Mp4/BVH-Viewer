#include <iostream>
#include <algorithm>
#include "../third-party/glew/include/GL/glew.h"
#include "../third-party/glfw/include/GLFW/glfw3.h"
#include "../include/GLSL/utils/ShaderGLSL.hpp"
#include "../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../include/light/GlobalAmbient.hpp"
#include "../include/light/PointLight.hpp"
#include "../include/light/LightGLSL.hpp"
#include "../include/camera/Camera.hpp"
#include "../include/camera/camera-types/PinHole.hpp"
#include "../include/camera/CameraGLSL.hpp"
#include "../include/objects/GeometricObject.hpp"
#include "../include/objects/GeometricObjectGLSL.hpp"
#include "../include/material/Material.hpp"
#include "../include/objects/shapes/Sphere.hpp"
#include "../include/objects/shapes/Cylinder.hpp"
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/ModelLoader.hpp"
#include "../include/bvh/MDBVH.hpp"

const unsigned int width = 800;
const unsigned int height = 800;




GLFWwindow* create_window( unsigned int width, unsigned int height);
 
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
    double prev_time = 0.0;
    double curr_time = 0.0;
    double time_delta;
    unsigned int counter = 0;

    GLFWwindow* window = create_window(width, height);
    glewInit();
    glViewport(0, 0, width, height);
 

    std::cout << "## Creating the object ...\n";
      if (argc == 2) {
        object = GeometricObject(new ModelLoader(argv[1]) , material);
    }else {
        object =  GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 2.5, 1.0, 50, 50), material);
    }

    curr_time = glfwGetTime();
    time_delta = curr_time - prev_time;
    std::cout << object;
    std::cout << "** Duration: "<< time_delta << " seconds **\n\n";

    std::cout << "## Creating a BVH for this object ...\n";
    prev_time = curr_time; 
    MDBVH bvh = MDBVH();
    bvh.build(object.get_mesh());
    curr_time = glfwGetTime();
    time_delta = curr_time - prev_time;
    std::cout << "** Duration: "<< time_delta << " seconds **\n\n";

    GeometricObject bvh_object = GeometricObject(bvh.into_mesh(11), BLACK_RUBBER, UNIT_MATRIX4);
    /* GeometricObject bvh_object = object; */
    std::cout << bvh_object;


    std::cout << "## Precompiling shaders programs ...\n";
    ShaderGLSL shader("../src/glsl-files/debug/debug.vert", "../src/glsl-files/debug/normal.frag");
    std::cout << "  - Normal Color Shader compiled\n";
    ShaderGLSL shader2("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/wireframe.geom");
    std::cout << "  - WireFrame Shader compiled\n";
    ShaderGLSL shader3("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/normal.geom");
    std::cout << "  - Normals Viewer Shader compiled\n";
    ShaderGLSL gouraud_shader("../src/glsl-files/gouraud/gouraud.vert", "../src/glsl-files/gouraud/gouraud.frag");
    std::cout << "  - Gouraud Shader compiled\n";
    ShaderGLSL blin_phong_shader("../src/glsl-files/blin-phong/blin-phong.vert", "../src/glsl-files/blin-phong/blin-phong.frag");
    std::cout << "  - Blin-Phong Shader compiled\n";
    ShaderGLSL toon_shader("../src/glsl-files/toon/toon.vert", "../src/glsl-files/toon/toon.frag");
    std::cout << "  - Toon Shader compiled\n\n";


    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(90, (float)width / height, 0.1f, 200.0f);
    ExportCamera* export_camera = new ExportVP();
    CameraGLSL cameraGLSL = CameraGLSL(shader.ID, export_camera, camera, pinhole_ptr );

    GeometricObjectGLSL objectGLSL(shader.ID, object.with_transformation(transformation));
    objectGLSL.export_mesh();

    GeometricObjectGLSL bvh_objectGLSL(shader.ID, bvh_object.with_transformation(transformation));
    bvh_objectGLSL.export_mesh();



    GlobalAmbient ambient_light = GlobalAmbient(WHITE);
    PointLight point_light = PointLight(WHITE, Vector4(10.0, 10.0, 10.0, 1.0));
    LightGLSL lightGLSL = LightGLSL(gouraud_shader.ID, ambient_light, point_light);


	glEnable(GL_DEPTH_TEST);

    
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
        bvh_objectGLSL.handle_inputs(window, width, height);

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
            cameraGLSL.change_shader(shader3.ID);
            objectGLSL.change_shader(shader3.ID);
            bvh_objectGLSL.change_shader(shader3.ID);
            objectGLSL.export_transformation();
            bvh_objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            /* objectGLSL.draw(); */
            bvh_objectGLSL.draw();
        }

        if(wireframe) {
            shader3.active_shader();
            cameraGLSL.change_shader(shader2.ID);
            objectGLSL.change_shader(shader2.ID);
            bvh_objectGLSL.change_shader(shader2.ID);
            objectGLSL.export_transformation();
            bvh_objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            objectGLSL.draw();
            /* bvh_objectGLSL.draw(); */

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
            /* objectGLSL.draw(); */


            bvh_objectGLSL.change_shader(shader2.ID);
            bvh_objectGLSL.export_transformation();
            bvh_objectGLSL.draw();



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

GLFWwindow* create_window( unsigned int width, unsigned int height){
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


