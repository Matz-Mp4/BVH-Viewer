
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
#include "../include/objects/shapes/Torus.hpp"
#include "../include/objects/shapes/ModelLoader.hpp"
#include "../include/bvh/MCBVH.hpp"
#include "../include/Gui.hpp"

#include "../third-party/imgui/imgui_impl_glfw.h"
#include "../third-party/imgui/imgui_impl_opengl3.h"


const unsigned int width = 800;
const unsigned int height = 800;

GLFWwindow* create_window(unsigned int width, unsigned int height);
void render_wireframe(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL, float thickness);
void render_normals(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL);
void render_bling_phong(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL, LightGLSL& lightGLSL);

int main(int argc, char* argv[]) {
    GeometricObject object;
    Matrix4 transformation = UNIT_MATRIX4;
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
        object = GeometricObject(new ModelLoader(argv[1]), material);
    } else {
        object = GeometricObject(new Torus(Vector4(0.0 , 0.0, 0.0), 1.5, 0.3, 50, 50), material);
    }

    curr_time = glfwGetTime();
    time_delta = curr_time - prev_time;
    std::cout << object;
    std::cout << "** Duration: "<< time_delta << " seconds **\n\n";

    std::cout << "## Creating a BVH for this object ...\n";
    prev_time = curr_time;
    MCBVH bvh = MCBVH(object.get_mesh().indices.size());
    bvh.build(object.get_mesh());
    curr_time = glfwGetTime();
    time_delta = curr_time - prev_time;
    std::cout << "** Duration: "<< time_delta << " seconds **\n\n";
    GeometricObject bvh_object = GeometricObject(bvh.into_mesh(0), BLACK_RUBBER, UNIT_MATRIX4);

    ShaderGLSL shader("../src/glsl-files/debug/debug.vert", "../src/glsl-files/debug/normal.frag");
    ShaderGLSL normal_shader("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/normal.geom");
    ShaderGLSL wireframe_shader("../src/glsl-files/debug/normal.vert", "../src/glsl-files/debug/normal.frag", "../src/glsl-files/debug/wireframe.geom");
    ShaderGLSL gouraud_shader("../src/glsl-files/gouraud/gouraud.vert", "../src/glsl-files/gouraud/gouraud.frag");
    ShaderGLSL blin_phong_shader("../src/glsl-files/blin-phong/blin-phong.vert", "../src/glsl-files/blin-phong/blin-phong.frag");

    Camera camera(Vector4(0.0f, 0.0f,  5.0f, 1.0));
    PinHole *pinhole_ptr = new PinHole(90, 4/3.0, 0.1f, 200.0f);
    ExportCamera* export_camera = new ExportVP();
    CameraGLSL cameraGLSL(shader.ID, export_camera, camera, pinhole_ptr);

    GeometricObjectGLSL objectGLSL(shader.ID, object.with_transformation(transformation));
    objectGLSL.export_mesh();

    GeometricObjectGLSL bvh_objectGLSL(shader.ID, bvh_object.with_transformation(transformation));
    bvh_objectGLSL.export_mesh();

    GlobalAmbient ambient_light = GlobalAmbient(WHITE);
    PointLight point_light = PointLight(WHITE, Vector4(10.0, 10.0, 10.0, 1.0));
    LightGLSL lightGLSL(gouraud_shader.ID, ambient_light, point_light);

    glEnable(GL_DEPTH_TEST);
    bool is_camera_fixed = false;

    Gui gui;
    gui.init(window, bvh, objectGLSL);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.7f, 0.75f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            is_camera_fixed = !is_camera_fixed;
        }
 
        if(!is_camera_fixed) {
           cameraGLSL.handle_inputs(window, width, height);
        }
        objectGLSL.handle_inputs(window, width, height);
        bvh_objectGLSL.handle_inputs(window, width, height);

        if(gui.draw_obj_normals) {
            render_normals(normal_shader, objectGLSL, cameraGLSL);
        }

        if(gui.draw_obj_wf) {
            render_wireframe(wireframe_shader, objectGLSL, cameraGLSL, gui.wf_tickness);
        }

        if(gui.draw_bvh_wf) {
            render_wireframe(wireframe_shader, bvh_objectGLSL, cameraGLSL, gui.wf_tickness);
        }

        if(gui.draw_obj_bp){
            objectGLSL = objectGLSL.with_color(gui.color[0], gui.color[1], gui.color[2]);
            Material material = objectGLSL.get_material();  
            material = material.turn_into_matte(gui.ka, gui.kd)
                               .turn_into_glossy(gui.ks, gui.exp);
            objectGLSL = objectGLSL.with_material(material); 
            render_bling_phong(blin_phong_shader, objectGLSL, cameraGLSL, lightGLSL);
        }

        if(gui.draw_bvh_bp){
            bvh_objectGLSL = bvh_objectGLSL.with_material(objectGLSL.get_material()); 
            render_bling_phong(blin_phong_shader, bvh_objectGLSL, cameraGLSL, lightGLSL);
        }

        if(gui.bvh_depth_changed) {
            bvh.into_mesh(gui.bvh_depth);
            bvh_objectGLSL = bvh_objectGLSL.with_mesh(bvh.into_mesh(gui.bvh_depth));
            bvh_objectGLSL.export_mesh();
        }

        gui.render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete pinhole_ptr;
    objectGLSL.delete_mesh();
    shader.delete_shader();
    wireframe_shader.delete_shader();
    gouraud_shader.delete_shader();
    blin_phong_shader.delete_shader();
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


void render_wireframe(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL, float thickness) {
    shader.active_shader();
    cameraGLSL.change_shader(shader.ID);
    objectGLSL.change_shader(shader.ID);
    objectGLSL.export_transformation();
    cameraGLSL.export_projection();
    ShaderGLSL::set_float(shader.ID, "thickness", thickness);
    objectGLSL.draw();
}


void render_bling_phong(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL, LightGLSL& lightGLSL){
     shader.active_shader();
     cameraGLSL.change_shader(shader.ID);
     objectGLSL.change_shader(shader.ID);
     lightGLSL.change_shader(shader.ID);
     objectGLSL.export_transformation();
     objectGLSL.export_material();
     cameraGLSL.export_projection();
     lightGLSL.export_ambient();
     lightGLSL.export_point_light();
     objectGLSL.draw();
}


void render_normals(ShaderGLSL& shader, GeometricObjectGLSL& objectGLSL, CameraGLSL& cameraGLSL) {
     shader.active_shader();
     cameraGLSL.change_shader(shader.ID);
     objectGLSL.change_shader(shader.ID);
     objectGLSL.change_shader(shader.ID);
     objectGLSL.export_transformation();
     objectGLSL.export_transformation();
     cameraGLSL.export_projection();
     objectGLSL.draw();
}
