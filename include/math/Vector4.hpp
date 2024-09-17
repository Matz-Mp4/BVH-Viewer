#pragma once 

#include <ostream>
class Vector4 {
    public:
        union {
            struct {
                float x, y, z, w;
            };
            float data[4];
        };

        Vector4() = default;
       ~Vector4() = default;

       
        Vector4(float x, float y, float z);
        Vector4(float x, float y, float z, float w);
        
        Vector4    operator+(const Vector4& rhs) const;
        Vector4    operator-(const Vector4& rhs) const;
        Vector4    operator-() const;
        Vector4    operator*(float t) const;
        float      operator*(const Vector4& rhs) const; //dot product
        Vector4    operator/(float t) const;
        Vector4    operator|(const Vector4&   v) const;
        bool      operator==(const Vector4&   v) const;
        float         length() const;
        Vector4    normalize()const;
       
        friend std::ostream& operator<<(std::ostream& stream, const Vector4& mtx); //print Matrix4 


};


Vector4 operator*(float, const Vector4& rhs);
Vector4 operator/(float, const Vector4& rhs);
 
