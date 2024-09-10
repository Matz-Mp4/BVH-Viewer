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
        Material(Color c, double k_amb, double k_dif, double k_spec,  double exp, double k_trans = 0, double index_ref = 0/*, IShade* luminance = nullptr*/);

        Material&      turn_into_matte(double k_amb, double k_dif);
        Material&    turn_into_plastic(double k_spec, double exp);
        Material& turn_into_reflective(double k_trans, double index_ref);
        Material&         change_color(Color c);
        


    private:
        Color   color;
        double  k_amb;
        double  k_dif;
        double  k_spec;
        double  k_trans;
        double  exp;
        double  index_ref;
        /* IShade* luminance; */
};

