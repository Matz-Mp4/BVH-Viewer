#pragma once

#include <string>
#include <GL/glew.h>
#include "../../math/Matrix4.hpp"
class ShaderGLSL {
    public:
        ShaderGLSL(const char* vertex_path, const char* frag_path);

        void       active_shader() ;
        void       delete_shader() ;
        void         create_prog(const char* vert_shader, const char* frag_shader) ;
        void            set_bool(const std::string &name, bool value) const ;
        void             set_int(const std::string &name, int value) const ;
        void           set_float(const std::string &name, float value) const;
        void         set_matrix4(const std::string &name, const Matrix4& mtx) const;
        size_t ID;
};
