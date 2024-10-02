#pragma once

#include <string>

#include "../IShape.hpp"

class ModelLoader : public IShape {
public:
    ModelLoader(const std::string& filpath);

    virtual Mesh generate_mesh() const override;

private:
    std::string filepath;

    Mesh load_ply(const std::string& filepath) const;
    Mesh load_obj(const std::string& filepath) const;
};
