#include "../../include/light/GlobalAmbient.hpp"

GlobalAmbient::GlobalAmbient(const Color& color):
    color(color)
{}

GlobalAmbient GlobalAmbient::with_color(const Color& color) const {
    return GlobalAmbient(color); 
}

Color GlobalAmbient::get_color() const {
     return color;
}







