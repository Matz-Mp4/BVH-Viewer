#include "../../include/math/Vector4.hpp"
#include <cmath>

Vector4::Vector4(float t) {
  this->data[0] = t;
  this->data[1] = t;
  this->data[2] = t;
  this->data[3] = 0.0;
}

Vector4::Vector4(float x, float y, float z) {
  this->data[0] = x;
  this->data[1] = y;
  this->data[2] = z;
  this->data[3] = 0.0;
}

Vector4::Vector4(float x, float y, float z, float w) {
  this->data[0] = x;
  this->data[1] = y;
  this->data[2] = z;
  this->data[3] = w;
}

Vector4 Vector4::operator+(const Vector4 &rhs) const {
  return Vector4(this->data[0] + rhs.data[0], this->data[1] + rhs.data[1],
                 this->data[2] + rhs.data[2], this->data[3] + rhs.data[3]);
}


Vector4 Vector4::operator-(const Vector4 &rhs) const {
  return Vector4(this->data[0] - rhs.data[0], this->data[1] - rhs.data[1],
                 this->data[2] - rhs.data[2], this->data[3] - rhs.data[3]);
}

Vector4 Vector4::operator-() const {
  return Vector4(-data[0], -data[1], -data[2], -data[3]);
}

//dot product
float Vector4::operator*(const Vector4 &rhs) const {
  float x2 = this->data[0] * rhs.data[0];
  float y2 = this->data[1] * rhs.data[1];
  float z2 = this->data[2] * rhs.data[2];
  float w2 = this->data[3] * rhs.data[3];

  return (x2 + y2 + z2) ;
}

Vector4 Vector4::operator*(float t) const {
  return Vector4(t * this->data[0], t * this->data[1], 
                 t * this->data[2], t * this->data[3]);
}

//cross product
Vector4 Vector4::operator|(const Vector4 &v) const {
  return Vector4(this->data[1] * v.data[2] - this->data[2] * v.data[1], 
                 this->data[2] * v.data[0] - this->data[0] * v.data[2],
                 this->data[0] * v.data[1] - this->data[1] * v.data[0]);
}

Vector4 Vector4::operator/(float t) const {
  return Vector4(this->data[0] / t, 
                 this->data[1] / t,
                 this->data[2] / t,
                 this->data[3] / t);
}

Vector4 Vector4::normalize() const{
    Vector4 res;
    float t = this->length();
    res.data[0] = this->data[0] / t;
    res.data[1] = this->data[1] / t;
    res.data[2] = this->data[2] / t;
    res.data[3] = this->data[3] / t;
    
    return res;
}

float Vector4::length() const {
  float x2 = this->data[0] * this->data[0];
  float y2 = this->data[1] * this->data[1];
  float z2 = this->data[2] * this->data[2];
  float w2 = this->data[3] * this->data[3];
  return std::sqrt(x2 + y2 + z2 + w2);
}


Vector4 operator*(float t, const Vector4 &v) {
  return Vector4(t * v.x, t * v.y, t * v.z, t * v.w);
}

Vector4 operator/(float t, const Vector4 &v) {
  return v / t;
}

float Vector4::operator[](unsigned int idx) const {
    int i = idx % 4;
    return data[i];
}
bool  Vector4::operator==(const Vector4&   v) const {
    return this->x == v.x && 
           this->y == v.y && 
           this->z == v.z && 
           this->w  == v.w;
}

std::ostream& operator<<(std::ostream &stream, const Vector4 &tup) {
  stream << '(';
  for (int i = 0; i < 4; i++) {
    stream << tup.data[i] << ",";
  }
  stream << "\b\b) ";
  return stream;
}
