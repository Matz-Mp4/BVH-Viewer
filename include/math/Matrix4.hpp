#pragma once

#include "Vector4.hpp"
#include <ostream>

class Matrix4 {
public:

     Matrix4() = default;
    ~Matrix4() = default;

    Matrix4(const Vector4& arg1, const Vector4& arg2, const Vector4& arg3, const Vector4& arg4);
    Matrix4(const float mtx[16]);
    Matrix4(float value);

    Matrix4  operator+ (const Matrix4& rhs);
    Vector4  operator* (const Vector4& rhs);
    Matrix4  operator* (const Matrix4& rhs);
    Matrix4  operator* (const float   rhs);
    bool     operator==(const Matrix4& rhs) const;

    Matrix4  transpose() const;
    
    friend std::ostream& operator<<(std::ostream& stream, const Matrix4& mtx); //print Matrix4 
    
    union {
        struct {
            float mtx_data[16];
        };
        Vector4 data[4];
    };

};
