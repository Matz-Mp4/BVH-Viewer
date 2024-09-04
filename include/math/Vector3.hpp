#pragma once 


class Vector3  {
    public:
        Vector3() = default;
       
        Vector3(double x, double y, double z);
        
        Vector3    operator+(const Vector3& rhs) const;
        Vector3    operator-(const Vector3& rhs) const;
        Vector3    operator-() const;
        Vector3    operator*(double t) const;
        double  operator*(const Vector3& rhs) const; //dot product
        Vector3    operator/(double t) const;
        Vector3    operator|(const Vector3&   v) const;
        double  length() const;
        void    normalize();
        
        double x, y, z;

};

Vector3 operator*(double, const Vector3& rhs);
Vector3 operator/(double, const Vector3& rhs);
 
