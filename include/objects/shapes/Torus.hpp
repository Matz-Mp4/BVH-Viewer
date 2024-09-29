#pragma once

#include "../IShape.hpp"
#include "../../math/Vector4.hpp"

class Torus : public IShape {
    public:
        Torus() = default;
       ~Torus() = default;
        Torus(const Vector4 &center, const float _r_torus, float _r_tube,unsigned int u = 20, unsigned int v  = 20); // latitude

        Mesh generate_mesh() const override;



    private:
        static Vector4 position(float r_torus, float r_tube, float theta, float phi);
        unsigned int u; // latitude
        unsigned int v; // longitude

        Vector4 center;
        float   r_tube;
        float  r_torus;


};
 
