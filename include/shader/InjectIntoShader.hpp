#pragma once
#include "IShader.hpp"

/**
    Transfer a data of an object to a shader file 
**/
class InjectIntoShader {
    virtual void inject_data(IShader* shader);
};
