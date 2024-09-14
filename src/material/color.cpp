#include "../../include/material/Color.hpp"
#include <cmath>

Color::Color(const float c)
    : r(c),g(c),b(c) {}

Color::Color(const float red, const float green, const float blue)
    : r(red),g(green),b(blue) {} 


Color Color::operator+(const Color& rhs) {
    return Color(this->r + rhs.r, this->g + rhs.g, this->b + rhs.b);
}

Color& Color::operator+=(const Color& rhs) {
    this->r+=rhs.r;
    this->g+=rhs.g;
    this->b+=rhs.b;
    return *this;
}

Color  Color::operator-(const Color& rhs) {
    return Color(this->r - rhs.r, this->g - rhs.g, this->b - rhs.b);
}

Color Color::operator*(const Color& rhs) const{
    /* this->r*=rhs.r; */
    /* this->g*=rhs.g; */
    /* this->b*=rhs.b; */
    return Color(this->r * rhs.r, this->g * rhs.g, this->b * rhs.b);
}

Color Color::operator*(const float rhs) const {
    /* this->r *= rhs; */
    /* this->g *= rhs; */
    /* this->b *= rhs; */
    return Color(this->r * rhs, this->g * rhs, this->b * rhs);
}

Color operator*(const float a, const Color& c){
    /* this->r *= rhs; */
    /* this->g *= rhs; */
    /* this->b *= rhs; */
    return (c * a);
}

Color Color::operator/(const float rhs) const {
    /* this->r *= rhs; */
    /* this->g *= rhs; */
    /* this->b *= rhs; */
    return Color(this->r / rhs, this->g / rhs, this->b / rhs);
}

bool Color::operator==(const Color& rhs) {
    return this->r == rhs.r &&
           this->g == rhs.g &&
           this->b == rhs.b;
}


Color Color::powc(float p) const {
    return Color(powf(r, p), powf(g, p), powf(b, p));
}

