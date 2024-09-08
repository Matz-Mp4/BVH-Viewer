#include "../IShader.hpp"
#include <string>
class ShaderGLSL: IShader {
    public:
        ShaderGLSL(const char* vertex_path, const char* frag_path);

        void       active_shader() override;
        void       delete_shader() override;
        void         create_prog(const char* vert_shader, const char* frag_shader) override;
        void            set_bool(const std::string &name, bool value) const ;
        void             set_int(const std::string &name, int value) const ;
        void           set_float(const std::string &name, float value) const;
        size_t ID;
};
