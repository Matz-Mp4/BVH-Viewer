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
        static void            set_bool(size_t ID, const std::string &name, bool value) ;
        static void             set_int(size_t ID, const std::string &name, int value) ;
        static void           set_float(size_t ID, const std::string &name, float value) ;
        static void         set_matrix4(size_t ID, const std::string &name, const Matrix4& mtx) ;
        size_t ID;
};
