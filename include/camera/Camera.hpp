#pragma once 
#include "../math/Vector3.hpp"

class DataCamera {
    public:
        DataCamera(Vector3 eye = Vector3(0, 0, 1), Vector3 direction = Vector3(0 , 0, -1), Vector3 up = Vector3(0, 1, 0));

        /**
          The lookAt matrix transforms points from the world space to the camera’s local space , aligning the 
          camera’s axes with the target and up vectors. On the other hand, the model lookAt matrix transforms 
          points from the world space to the object’s local space, aligning the object’s axes with the target and up vectors.
         **/
        void look_at();
        /**
          Calculate the forward, left, and up axes based on the object’s position, target, and up direction,
         **/
        void compute_uvw();

        Vector3 eye, direction, up;
        Vector3 u, v, w;            //othonormal basis (u,v,w)
};
