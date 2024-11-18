#include "../third-party/imgui/imgui_impl_glfw.h"
#include "../third-party/imgui/imgui_impl_opengl3.h"


class Gui {
    public:
        void render();
        void   init(GLFWwindow* window);

        //Draw Normals
        bool draw_obj_normals;
        bool draw_bvh_normals;
        //Draw as Wireframe
        bool      draw_bvh_wf;
        bool      draw_obj_wf;
        float     wf_tickness;
        //Draw as Bling-Phong
        bool      draw_bvh_bp;
        bool      draw_obj_bp;

        float        color[3];
        float ka, kd, ks, exp;
        int         bvh_depth;

        bool         draw_bvh;
        bool         draw_obj;
        bool bvh_depth_changed;
        int     triangles_size;
        int         nodes_size;
        int        leaves_size;
        
    private:
        void render_object_ui();
        void    render_bvh_ui();
        void  render_usage_ui();
        void   render_misc_ui();
};


