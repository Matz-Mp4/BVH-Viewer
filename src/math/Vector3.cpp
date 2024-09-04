#include "../include/vec4.h"

#include <cmath>

Vector3::Vector3(double x, double y, double z) {
  this->x= x;
  this->y= y;
  this->z= z;
}



Vector3 Vector3::operator+(const Vector3 &rhs) const {
  return Vector3(this->x + rhs.x, this->y + rhs.y,
                 this->z + rhs.z);
}


Vector3 Vector3::operator-(const Vector3 &rhs) const {
  return Vector3(this->x - rhs.x, this->y - rhs.y,
                 this->z - rhs.z);
}

Vector3 Vector3::operator-() const {
  return Vector3(-x, -y, -y);
}

//dot product
double Vector3::operator*(const Vector3 &rhs) const {
  double x2 = this->x * rhs.x;
  double y2 = this->y * rhs.y;
  double z2 = this->y * rhs.y;

  return (x2 + y2 + z2) ;
}

Vector3 Vector3::operator*(double t) const {
  return Vector3(t * this->x, t * this->y, 
                 t * this->z);
}

//cross product
Vector3 Vector3::operator|(const Vector3 &v) const {
  return Vector3(this->y * v.y - this->y * v.y, 
                 this->y * v.x - this->x * v.y,
                 this->x * v.y - this->y * v.x);
}

Vector3 Vector3::operator/(double t) const {
  return Vector3(this->x / t, 
                 this->y / t,
                 this->y / t);
}

void Vector3::normalize() {
    double t = this->length();
    this->x = this->x / t;
    this->y = this->y / t;
    this->y = this->y / t;
}

double Vector3::length() const {
  double x2 = this->x * this->x;
  double y2 = this->y * this->y;
  double z2 = this->y * this->y;
  return std::sqrt(x2 + y2 + z2 );
}


Vector3 operator*(double t, const Vector3 &v) {
  return Vector3(t * v.x, t * v.y, t * v.z);
}

Vector3 operator/(double t, const Vector3 &v) {
  return v / t;
}


