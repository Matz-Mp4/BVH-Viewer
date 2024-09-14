#include "../../include/math/Transforamation.hpp"
#include <cmath>
/*
    float data [] = {
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
    };
 */

Matrix4 Transformation::translation(float x, float y, float z) {
    float data [] = {
        1.0, 0.0, 0.0, x,
        0.0, 1.0, 0.0, y,
        0.0, 0.0, 1.0, z,
        0.0, 0.0, 0.0, 1.0,
    };
    return Matrix4(data);
}


Matrix4 Transformation::scaling(float x, float y, float z) {
    float data [] = {
          x, 0.0, 0.0, 0.0,
        0.0,   y, 0.0, 0.0,
        0.0, 0.0,   z, 0.0,
        0.0, 0.0, 0.0, 1.0,
    };
    return Matrix4(data);
}


Matrix4 Transformation::rotation_x(float angle) {
    float angle_cos = cos(angle);
    float angle_sin=  sin(angle);
    float data [] = {
          1.0,       0.0,        0.0, 0.0,
          0.0, angle_cos, -angle_sin, 0.0,
          0.0, angle_sin,  angle_cos, 0.0,
          0.0,       0.0,        0.0, 1.0,
      };
      return Matrix4(data);
}

Matrix4 Transformation::rotation_y(float angle) {

 float angle_cos = cos(angle);
  float angle_sin=  sin(angle);
  
  float data [] = {
         angle_cos, 0.0, angle_sin, 0.0,
               0.0, 1.0,       0.0, 0.0,
        -angle_sin, 0.0, angle_cos, 0.0,
               0.0, 0.0,       0.0, 1.0
    };
    return Matrix4(data);
}

Matrix4 Transformation::rotation_z(float angle) {
 float angle_cos = cos(angle);
  float angle_sin=  sin(angle);
  
  float data [] = {
        angle_cos, -angle_sin, 0.0, 0.0,
        angle_sin,  angle_sin, 0.0, 0.0,
              0.0,        0.0, 1.0, 0.0,
              0.0,        0.0, 0.0, 1.0,
    };
    return Matrix4(data);
}
