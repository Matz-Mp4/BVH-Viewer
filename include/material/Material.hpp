#pragma once
#include "Color.hpp"

enum class MaterialType {
    RUBBER,
    PLASTIC,
    METALLIC,
    DIAMOND,
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
        Material&    turn_into_glossy(float k_spec, float exp);
        Material& turn_into_reflective(float k_trans, float index_ref);
        Material&         change_color(Color c);

         Color    get_color() const;
        float   get_ambient() const;
        float   get_diffuse() const;
        float  get_specular() const;
        float   get_expoent() const;

        // methods for material types
        static Material create_rubber(Color c);
        static Material create_plastic(Color c);
        static Material create_metallic(Color c);
        static Material create_diamond(Color c);


        
    private:
        Color   color;
        float  k_amb;
        float  k_dif;
        float  k_spec;
        float  k_trans;
        float  exp;
        float  index_ref;
};


//RUBBER
static const Material ORANGE_RUBBER =  Material(ORANGE, MaterialType::RUBBER);
static const Material RED_RUBBER    =  Material(RED, MaterialType::RUBBER);    
static const Material BLUE_RUBBER   =  Material(BLUE, MaterialType::RUBBER);   
static const Material GREEN_RUBBER  =  Material(GREEN, MaterialType::RUBBER);  
static const Material BLACK_RUBBER  =  Material(BLACK, MaterialType::RUBBER);  
static const Material WHITE_RUBBER  =  Material(WHITE, MaterialType::RUBBER);  

//PLASTIC
static const Material ORANGE_PLASTIC =Material(ORANGE, MaterialType::PLASTIC);
static const Material RED_PLASTIC =   Material(RED, MaterialType::PLASTIC);   
static const Material BLUE_PLASTIC =  Material(BLUE, MaterialType::PLASTIC);  
static const Material GREEN_PLASTIC=  Material(GREEN, MaterialType::PLASTIC); 
static const Material BLACK_PLASTIC = Material(BLACK, MaterialType::PLASTIC); 
static const Material WHITE_PLASTIC=  Material(WHITE, MaterialType::PLASTIC); 

//METALLIC
static const Material ORANGE_METALLIC =  Material(ORANGE, MaterialType::METALLIC); 
static const Material RED_METALLIC    =  Material(RED, MaterialType::METALLIC);    
static const Material BLUE_METALLIC   =  Material(BLUE, MaterialType::METALLIC);    
static const Material GREEN_METALLIC  =  Material(GREEN, MaterialType::METALLIC);   
static const Material BLACK_METALLIC  =  Material(BLACK, MaterialType::METALLIC);   
static const Material WHITE_METALLIC  =  Material(WHITE, MaterialType::METALLIC);   

//DIAMOND
static const Material ORANGE_DIAMOND   =Material(ORANGE, MaterialType::DIAMOND); 
static const Material RED_DIAMOND      =Material(RED, MaterialType::DIAMOND);     
static const Material BLUE_DIAMOND     =Material(BLUE, MaterialType::DIAMOND);   
static const Material GREEN_DIAMOND    =Material(GREEN, MaterialType::DIAMOND);   
static const Material BLACK_DIAMOND    =Material(BLACK, MaterialType::DIAMOND);  
static const Material WHITE_DIAMOND    =Material(WHITE, MaterialType::DIAMOND);  


