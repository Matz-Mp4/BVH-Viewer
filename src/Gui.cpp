#include "../include/Gui.hpp"

void Gui::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;

    ka = kd = ks = 0.2;
    exp = 100;

    bvh_depth_changed = draw_bvh_bp = draw_bvh_wf = draw_obj_normals =  draw_obj_wf = false;
    draw_obj_bp = true;
    wf_tickness = 0.01;
    bvh_depth = 1;

    draw_bvh = false;
    draw_obj = true;


}
void Gui::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");
    render_object_ui();
    render_bvh_ui();
    render_usage_ui();
    render_misc_ui();
    ImGui::End();

    ImGui::Render();
    /* ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); */
        
};


void Gui::render_misc_ui() {

     if (draw_obj_wf || draw_bvh_wf) {
         ImGui::SliderFloat("WireFrame Thickness", &wf_tickness, 0.001, 0.02, "Thickness: %.3f");
     }
     if (draw_obj_bp || draw_bvh_bp) {
        ImGui::ColorEdit3("Object Color", color);
        ImGui::SliderFloat("Ambient", &ka, 0, 1.0, "Ambient: %.2f");
        ImGui::SliderFloat("Diffuse", &kd, 0, 1.0, "Diffuse: %.2f");
        ImGui::SliderFloat("Specular", &ks, 0, 1.0, "Specular: %.2f");
        ImGui::SliderFloat("Exponent", &exp, 0, 500.0, "Exponent: %.1f");
     }
 
}
void Gui::render_bvh_ui() {
    if (ImGui::CollapsingHeader("BVH")) {
        ImGui::Checkbox("Draw BVH", &draw_bvh);
        if(draw_bvh) {
            ImGui::Checkbox("WireFrame", &draw_bvh_wf); 
            ImGui::Checkbox("Blin-Phong", &draw_bvh_bp); 
            bvh_depth_changed = ImGui::SliderInt("BVH Depth", &bvh_depth, 0, 30, "Depth: %d");
        }else {
            draw_bvh_wf = draw_bvh_bp = draw_bvh;
        }
    }
}

void Gui::render_object_ui() {
    if (ImGui::CollapsingHeader("Object")) {
        ImGui::Checkbox("Draw Object", &draw_obj);
        if( draw_obj) {
            ImGui::SameLine();
            ImGui::Checkbox("WireFrame", &draw_obj_wf); 
            ImGui::SameLine();
            ImGui::Checkbox("Blin-Phong", &draw_obj_bp); 
            ImGui::SameLine();
            ImGui::Checkbox("Normals", &draw_obj_normals);
            ImGui::Separator();
        }else {
            draw_obj_normals = draw_obj_wf = draw_obj_bp = draw_obj;
        }
    }
}


void  Gui::render_usage_ui() {
    if (ImGui::CollapsingHeader("Usage")) {
         ImGui::Text("Press <F> to toggle camera lock/unlock");
         ImGui::Text("Press <W> to move forward");
         ImGui::Text("Press <S> to move backward");
         ImGui::Text("Press <A> to move left");
         ImGui::Text("Press <D> to move right");
         ImGui::Text("Press <Space> to move up");
         ImGui::Text("Press <Crtl> to move down");
    }
}
