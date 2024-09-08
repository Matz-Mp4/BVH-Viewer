#pragma once 
#include "../math/Vector4.hpp"
#include "../math/Matrix4.hpp"

class Camera {
    public:
        Camera(Vector4 eye = Vector4(0, 0, 1), Vector4 direction = Vector4(0 , 0, -1), Vector4 up = Vector4(0, 1, 0));

        /**
          The lookAt matrix transforms points from the world space to the camera’s local space , aligning the 
          camera’s axes with the target and up vectors. On the other hand, the model lookAt matrix transforms 
          points from the world space to the object’s local space, aligning the object’s axes with the target and up vectors.
         **/
        Matrix4 look_at();

        /**
          Calculate the forward, left, and up axes based on the object’s position, target, and up direction,
         **/
        void compute_uvw();

        Vector4 eye, direction, up;
        Vector4 u, v, w;            //othonormal basis (u,v,w)
};
