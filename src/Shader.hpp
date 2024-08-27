#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
    unsigned int id;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setInt(const std::string& name, int value) const;
    void setBool(const std::string& name, bool value) const;
    void setFloat(const std::string& name, float value) const;
};
