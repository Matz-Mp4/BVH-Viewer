#include "../../include/material/Material.hpp"

Material::~Material(){
    if(!luminance){
        delete luminance;
        luminance = nullptr;
    }
}


Material::Material(Color c, double k_amb, double k_dif, double k_spec,  double exp, double k_trans , double index_ref , IShade* luminance ):
    color(c),
    k_amb(k_amb),
    k_dif(k_dif),
    k_spec(k_spec),
    k_trans(k_trans),
    exp(exp),
    index_ref(index_ref),
    luminance(luminance) 
{}


Material& Material::turn_into_matte(double k_amb, double k_dif) {
    this->k_amb = k_amb;
    this->k_dif = k_dif;
    this->k_spec = 0.0;
    this->k_trans = 0.0;
    this->index_ref = 0.0;
    this->exp = 0.0;
    return *this;
}


Material& Material::turn_into_plastic(double k_spec, double exp) {
    this->k_spec = k_spec;
    this->exp = exp;
    this->k_trans = 0.0;
    this->index_ref = 0.0;
    return *this;
}


Material& Material::turn_into_reflective(double k_trans, double index_ref) {
    this->k_trans = k_trans;
    this->index_ref = index_ref;
    this->exp = 0.0;
    return *this;
}

Material& Material::change_color(Color c) {
    this->color = c;
    return *this;
}

Material& Material::change_luminance(IShade* luminance) {
    if(luminance != nullptr) {
        this->luminance = luminance;
    }
    return *this;
}

void Material::shade() {
    luminance->shade();
}
