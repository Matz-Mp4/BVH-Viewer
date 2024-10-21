#include "../../include/material/Material.hpp"


Material::Material(Color c, float k_amb, float k_dif, float k_spec,  float exp):
    color(c),
    k_amb(k_amb),
    k_dif(k_dif),
    k_spec(k_spec),
    exp(exp)
{}


Material& Material::turn_into_matte(float k_amb, float k_dif) {
    this->k_amb = k_amb;
    this->k_dif = k_dif;
    this->k_spec = 0.0;
    this->exp = 0.0;
    return *this;
}


Material& Material::turn_into_glossy(float k_spec, float exp) {
    this->k_spec = k_spec;
    this->exp = exp;
    return *this;
}

Material& Material::change_color(Color c) {
    this->color = c;
    return *this;
}

Material::Material(Color c, MaterialType type) {
    switch (type) {
        case MaterialType::RUBBER:
            *this = create_rubber(c);
            break;
        case MaterialType::PLASTIC:
            *this = create_plastic(c);
            break;
        case MaterialType::METALLIC:
            *this = create_metallic(c);
            break;
    
    }
}



Color Material:: get_color() const {
    return color;
}
float Material:: get_ambient() const {
    return k_amb;
} 
float Material:: get_diffuse() const {
    return k_dif;
} 
float Material::   get_specular() const {
    return k_spec;
} 
float Material::get_expoent() const {
    return exp;
} 





// Static methods for material types
Material Material::create_rubber(Color c) {
    return Material(c, 0.4f, 0.5f, 0.1f, 10.0f);
}

Material Material::create_plastic(Color c) {
    return Material(c, 0.1f, 0.3f, 1.0f, 100.0f);
}

Material Material::create_metallic(Color c) {
    return Material(c, 0.1f, 0.9f, 1.0f, 500.0f);
}


