#pragma once 
#include "../math/Vector3.hpp"

class DataCamera {
    public:
        DataCamera(Vector3 eye = Vector3(0, 0, 1), Vector3 look_at = Vector3(0 , 0, -1), Vector3 up = Vector3(0, 1, 0));

        void compute_uvw();

        Vector3 eye, look_at, up;
        Vector3 u, v, w;          //othonormal basis (u,v,w)
};
