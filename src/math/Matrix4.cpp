
#include "../../include/math/Matrix4.hpp"

Matrix4::Matrix4(const Vector4& arg1, const Vector4& arg2, const Vector4& arg3, const Vector4& arg4) {
    this->data[0] = arg1;
    this->data[1] = arg2;
    this->data[2] = arg3;
    this->data[3] = arg4;
}


Matrix4::Matrix4(const float value) {
    data[0].x = value; 
    data[0].y = value; 
    data[0].z = value; 
    data[0].w = value; 

    data[1].x = value; 
    data[1].y = value; 
    data[1].z = value; 
    data[1].w = value; 

    data[2].x = value; 
    data[2].y = value; 
    data[2].z = value;
    data[2].w = value;

    data[3].x = value;
    data[3].y = value;
    data[3].z = value;
    data[3].w = value;

}

Matrix4::Matrix4(const float mtx[16]) {
    this->data[0].x = mtx[0];
    this->data[0].y = mtx[1];
    this->data[0].z = mtx[2];
    this->data[0].w = mtx[3];

    this->data[1].x = mtx[4];
    this->data[1].y = mtx[5];
    this->data[1].z = mtx[6];
    this->data[1].w = mtx[7];

    this->data[2].x = mtx[8];
    this->data[2].y = mtx[9];
    this->data[2].z = mtx[10];
    this->data[2].w = mtx[11];

    this->data[3].x = mtx[12];
    this->data[3].y = mtx[13];
    this->data[3].z = mtx[14];
    this->data[3].w = mtx[15];
}
Matrix4& Matrix4::operator+(const Matrix4& arg) {
   this->data[0] =this->data[0] + arg.data[0];
   this->data[1] =this->data[1] + arg.data[1];
   this->data[2] =this->data[2] + arg.data[2];
   this->data[3] =this->data[3] + arg.data[3];
   return *this;
}

Matrix4& Matrix4::operator*(const Matrix4& arg) {
    Matrix4 res;
    for (int i = 0; i < 4; i++) {
         res.data[i].x = this->data[i].x * arg.data[0].x +  
                         this->data[i].y * arg.data[1].x +
                         this->data[i].z * arg.data[2].x +
                         this->data[i].w * arg.data[3].x;

         res.data[i].y = this->data[i].x * arg.data[0].y +  
                         this->data[i].y * arg.data[1].y +
                         this->data[i].z * arg.data[2].y +
                         this->data[i].w * arg.data[3].y;
 
         res.data[i].z = this->data[i].x * arg.data[0].z +  
                         this->data[i].y * arg.data[1].z +
                         this->data[i].z * arg.data[2].z +
                         this->data[i].w * arg.data[3].z;
 
         res.data[i].w = this->data[i].x * arg.data[0].w +  
                         this->data[i].y * arg.data[1].w +
                         this->data[i].z * arg.data[2].w +
                         this->data[i].w * arg.data[3].w;
    }
    *this = res;    
    return *this;
}

Matrix4& Matrix4::operator*(const float rhs) {
   this->data[0] =  this->data[0] * rhs;
   this->data[1] =  this->data[1] * rhs;
   this->data[2] =  this->data[2] * rhs;
   this->data[3] =  this->data[3] * rhs;
   return *this;
}

bool Matrix4::operator==(const Matrix4& arg) const {
    return this->data[0] == arg.data[0] && 
           this->data[1] == arg.data[1] && 
           this->data[2] == arg.data[2] &&
           this->data[3] == arg.data[3];
}


std::ostream& operator<<(std::ostream& stream, const Matrix4& mtx){
     stream << '[';
     stream << mtx.data[0]<< ",\n";
     stream << mtx.data[1]<< ",\n";
     stream << mtx.data[2]<< ",\n";
     stream << mtx.data[3]<< "]";
     return stream;
}
