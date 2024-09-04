#include "IShader.hpp"
class ShaderGLSL: IShader {
    public:
        ShaderGLSL(const char* vertex_path, const char* frag_path);

        void       use() override;
        void  set_bool(const std::string &name, bool value) const override;
        void   set_int(const std::string &name, int value) const override;
        void set_float(const std::string &name, float value) const override;
        size_t ID;
};
