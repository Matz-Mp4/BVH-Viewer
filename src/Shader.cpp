#include <Shader.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(getUniformLocation(id, name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(getUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(getUniformLocation(id, name.c_str()), value);
}
