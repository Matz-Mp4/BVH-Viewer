#pragma once 

#include <ostream>
class Vector4 {
    public:
        union {
            struct {
                double x, y, z, w;
            };
            double data[4];
        };

        Vector4() = default;
       ~Vector4() = default;

       
        Vector4(double x, double y, double z);
        Vector4(double x, double y, double z, double w);
        
        Vector4    operator+(const Vector4& rhs) const;
        Vector4    operator-(const Vector4& rhs) const;
        Vector4    operator-() const;
        Vector4    operator*(double t) const;
        double     operator*(const Vector4& rhs) const; //dot product
        Vector4    operator/(double t) const;
        Vector4    operator|(const Vector4&   v) const;
        bool      operator==(const Vector4&   v) const;
        double        length() const;
        void       normalize();
       
        friend std::ostream& operator<<(std::ostream& stream, const Vector4& mtx); //print Matrix4 


};


Vector4 operator*(double, const Vector4& rhs);
Vector4 operator/(double, const Vector4& rhs);
 
