
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

#include "../third-party/imgui/imgui_impl_glfw.h"
#include "../third-party/imgui/imgui_impl_opengl3.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLFWwindow* create_window(unsigned int width, unsigned int height);

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

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

    float color[4] = { 1.0f,1.0f,1.0f,1.0f };
    float k_a = 0.2, k_d = 0.2, k_s = 0.2, exp = 100;
    bool is_camera_fixed = false;
    int bvh_depth = 1;
    bool draw_bvh = false;
    bool draw_object = true;
    float wf_tickness = 0.01;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.7f, 0.7f, 0.75f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        curr_time = glfwGetTime();
        time_delta = curr_time - prev_time;
        counter++;
        float fps = (1.0 / time_delta) * counter;
        float ms = (time_delta / counter) * 1000;
        prev_time = curr_time;
        counter = 0;

        ImGui::Begin("Settings");

        if (ImGui::CollapsingHeader("Rendering ")) {
            ImGui::Checkbox("WireFrame", &wireframe); 
            ImGui::SameLine();
            ImGui::Checkbox("Gouraud", &gouraudframe); 
            ImGui::SameLine();
            ImGui::Checkbox("Blin-Phong", &blin_phong_frame); 
            ImGui::SameLine();
            ImGui::Checkbox("Normals", &defaultframe);
            ImGui::Separator();


            if (wireframe ) {
                ImGui::SliderFloat("WireFrame Thickness", &wf_tickness, 0.001, 0.02, "Thickness: %.3f");
            }
            if (blin_phong_frame || gouraudframe) {
                  if(ImGui::ColorEdit3("Object Color", color)) {
                    objectGLSL = objectGLSL.with_color(color[0], color[1], color[2]);
                }
                ImGui::SliderFloat("Ambient", &k_a, 0, 1.0, "Ambient: %.2f");
                ImGui::SliderFloat("Diffuse", &k_d, 0, 1.0, "Diffuse: %.2f");
                ImGui::SliderFloat("Specular", &k_s, 0, 1.0, "Specular: %.2f");
                ImGui::SliderFloat("Exponent", &exp, 0, 500.0, "Exponent: %.1f");
                objectGLSL = objectGLSL.with_material(objectGLSL.get_material()
                                                                .turn_into_matte(k_a, k_d)
                                                                .turn_into_glossy(k_s, exp));
            }
        }

        if (ImGui::CollapsingHeader("Object")) {
            ImGui::Checkbox("Draw Object", &draw_object);

            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"Vertices Amount: %d", (int)object.get_vertices().size());
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"Triangles Amount: %d", (int)object.get_indices().size() / 3);
        }

        if (ImGui::CollapsingHeader("BVH ")) {
            ImGui::Checkbox("Draw BVH", &draw_bvh);
            if (ImGui::SliderInt("BVH Depth", &bvh_depth, 0, 30, "Depth: %d")) {
                bvh.into_mesh(bvh_depth);
                bvh_objectGLSL = bvh_objectGLSL.with_mesh(bvh.into_mesh(bvh_depth));
                bvh_objectGLSL.export_mesh();
            }
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"Nodes Amount: %d", bvh.nodes_size);
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"Leaves Amount: %d", bvh.leaves_size);
        }

        if (ImGui::CollapsingHeader("Camera")) {
            ImGui::Text("Press <F> to toggle camera lock/unlock");
            ImGui::Text("Press <W> to move forward");
            ImGui::Text("Press <S> to move backward");
            ImGui::Text("Press <A> to move left");
            ImGui::Text("Press <D> to move right");
            ImGui::Text("Press <Space> to move up");
            ImGui::Text("Press <Crtl> to move down");
            Vector4 camera_pos = cameraGLSL.get_position();
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Camera Postion: (%.3f, %.3f, %.3f)", camera_pos.x, camera_pos.y, camera_pos.z);
            Vector4 camera_dir= cameraGLSL.get_direction();
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"Camera Direction: (%.3f, %.3f, %.3f)", camera_dir.x, camera_dir.y, camera_dir.z);
        }
        ImGui::Text("FPS: %.2f | MS: %.2f", fps, ms);
        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            is_camera_fixed = !is_camera_fixed;
        }
 
        if(!is_camera_fixed) {
           cameraGLSL.handle_inputs(window, width, height);
        }
        objectGLSL.handle_inputs(window, width, height);
        bvh_objectGLSL.handle_inputs(window, width, height);

        if(defaultframe) {
            shader.active_shader();
            cameraGLSL.change_shader(shader.ID);
            objectGLSL.change_shader(shader.ID);
            bvh_objectGLSL.change_shader(shader.ID);
            objectGLSL.export_transformation();
            bvh_objectGLSL.export_transformation();
            cameraGLSL.export_projection();

            if (draw_object)
                objectGLSL.draw();
            if (draw_bvh)
                bvh_objectGLSL.draw();
 
        }

        if(wireframe) {
            wireframe_shader.active_shader();
            cameraGLSL.change_shader(wireframe_shader.ID);
            objectGLSL.change_shader(wireframe_shader.ID);
            bvh_objectGLSL.change_shader(wireframe_shader.ID);
            objectGLSL.export_transformation();
            bvh_objectGLSL.export_transformation();
            cameraGLSL.export_projection();
            ShaderGLSL::set_float(wireframe_shader.ID, "thickness", wf_tickness);

            if(draw_bvh)
                bvh_objectGLSL.draw();
            if(draw_object)
                objectGLSL.draw();
        }

        if(gouraudframe) {
            gouraud_shader.active_shader();
            cameraGLSL.change_shader(gouraud_shader.ID);
            objectGLSL.change_shader(gouraud_shader.ID);
            lightGLSL.change_shader(gouraud_shader.ID);
            bvh_objectGLSL.change_shader(gouraud_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            lightGLSL.export_ambient();
            lightGLSL.export_point_light();
            bvh_objectGLSL.export_transformation();

            if(draw_bvh)
                bvh_objectGLSL.draw();
            if(draw_object)
                objectGLSL.draw();
        }

        if(blin_phong_frame) {
            blin_phong_shader.active_shader();
            cameraGLSL.change_shader(blin_phong_shader.ID);
            objectGLSL.change_shader(blin_phong_shader.ID);
            lightGLSL.change_shader(blin_phong_shader.ID);
            bvh_objectGLSL.change_shader(blin_phong_shader.ID);
            objectGLSL.export_transformation();
            objectGLSL.export_material();
            cameraGLSL.export_projection();
            lightGLSL.export_ambient();
            lightGLSL.export_point_light();
            bvh_objectGLSL.export_transformation();


            if(draw_bvh)
                bvh_objectGLSL.draw();
            if(draw_object)
                objectGLSL.draw();


        }

        ImGui::Render();

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
