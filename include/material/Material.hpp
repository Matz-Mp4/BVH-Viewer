#pragma once
#include "Color.hpp"

/* enum class TYPE_SHADE{GLSL}; */

/** 
  The constants k_amb, k_dif, and k_spec are the coefficients of ambient, diffuse, and specular reflections. 
  The constant exp is the exponent of specular reflection. The constant k_trans is the transmittance coefficient, 
  and index_ref is the index of refraction of the material. Luminance computes the  brightness of the color when
  a ray hit the material
**/

class Material {
    public:
        Material() = default;
       ~Material();
        Material(Color c, float k_amb, float k_dif, float k_spec,  float exp, float k_trans = 0, float index_ref = 0/*, IShade* luminance = nullptr*/);

        Material&      turn_into_matte(float k_amb, float k_dif);
        Material&    turn_into_plastic(float k_spec, float exp);
        Material& turn_into_reflective(float k_trans, float index_ref);
        Material&         change_color(Color c);
        


    private:
        Color   color;
        float  k_amb;
        float  k_dif;
        float  k_spec;
        float  k_trans;
        float  exp;
        float  index_ref;
};

