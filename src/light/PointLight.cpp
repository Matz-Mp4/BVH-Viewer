#include "../../include/light/PointLight.hpp"

PointLight::PointLight(const Color& color, const Vector4& position):
    color(color),
    position(position)
{}
 
PointLight PointLight::with_color(const Color& color) const {
    return PointLight(color, this->position); 
}
PointLight  PointLight::with_position(const Vector4& position) const {
    return PointLight(this->color, position);
}
 Color PointLight::get_color() const {
     return color;

 }
 Vector4 PointLight::get_position() const {
     return position;
 }


