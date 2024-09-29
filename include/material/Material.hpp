#pragma once
#include "Color.hpp"

enum class MaterialType {
    RUBBER,
    PLASTIC,
    METALLIC,
    GLASS,
    DIAMOND,
    GOLD,
};

/** 
  The constants k_amb, k_dif, and k_spec are the coefficients of ambient, diffuse, and specular reflections. 
  The constant exp is the exponent of specular reflection. The constant k_trans is the transmittance coefficient, 
  and index_ref is the index of refraction of the material. Luminance computes the  brightness of the color when
  a ray hit the material
**/

class Material {
    public:
        Material() = default;
       ~Material() = default;
        Material(Color c, float k_amb, float k_dif, float k_spec,  float exp, float k_trans = 0, float index_ref = 0);
        Material(Color c, MaterialType type);

        Material&      turn_into_matte(float k_amb, float k_dif);
        Material&    turn_into_plastic(float k_spec, float exp);
        Material& turn_into_reflective(float k_trans, float index_ref);
        Material&         change_color(Color c);
        

        // methods for material types
        static Material create_rubber(Color c);
        static Material create_plastic(Color c);
        static Material create_metallic(Color c);
        static Material create_glass(Color c);
        static Material create_diamond(Color c);
        static Material create_gold(Color c);

        //RUBBER
        static const Material ORANGE_RUBBER;
        static const Material RED_RUBBER;
        static const Material BLUE_RUBBER;
        static const Material GREEN_RUBBER;
        static const Material BLACK_RUBBER;
        static const Material WHITE_RUBBER;

        //PLASTIC
        static const Material ORANGE_PLASTIC;
        static const Material RED_PLASTIC;
        static const Material BLUE_PLASTIC;
        static const Material GREEN_PLASTIC;
        static const Material BLACK_PLASTIC;
        static const Material WHITE_PLASTIC;

        //METALLIC
        static const Material ORANGE_METALLIC;
        static const Material RED_METALLIC;
        static const Material BLUE_METALLIC;
        static const Material GREEN_METALLIC;
        static const Material BLACK_METALLIC;
        static const Material WHITE_METALLIC;

        //GLASS
        static const Material ORANGE_GLASS;
        static const Material RED_GLASS;
        static const Material BLUE_GLASS;
        static const Material GREEN_GLASS;
        static const Material BLACK_GLASS;
        static const Material WHITE_GLASS;

        //DIAMOND
        static const Material ORANGE_DIAMOND;
        static const Material RED_DIAMOND;
        static const Material BLUE_DIAMOND;
        static const Material GREEN_DIAMOND;
        static const Material BLACK_DIAMOND;
        static const Material WHITE_DIAMOND;

    private:
        Color   color;
        float  k_amb;
        float  k_dif;
        float  k_spec;
        float  k_trans;
        float  exp;
        float  index_ref;
};

