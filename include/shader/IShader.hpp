#pragma once

class IShader {
    public:
       virtual void       use() = 0;
       virtual void   create_prog(const char* vert_shader, const char* frag_shader) = 0;
       virtual void active_shader() = 0;
       virtual void delete_shader() = 0;
};
