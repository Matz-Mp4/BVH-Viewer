#pragma once 
#include "../math/Matrix4.hpp"
#include "TypeCamera.hpp"

class Camera {
    public:
        Camera(Vector4 eye = Vector4(0, 0, -1), Vector4 direction = Vector4(0 , 0, -1), Vector4 up = Vector4(0, 1, 0));
        /**
          The lookAt matrix transforms points from the world space to the camera’s local space , aligning the 
          camera’s axes with the target and up vectors. On the other hand, the model lookAt matrix transforms 
          points from the world space to the object’s local space, aligning the object’s axes with the target and up vectors.
         **/
        Matrix4 look_at(CoordSystem coord_system);

        /**
          Calculate the forward, right, and up axes based on the object’s eye, direction, and up direction
         **/
        void compute_othor_bases(CoordSystem coord_system);

        /** 
          Construct view-projection matrix
         **/        
        Matrix4 compute_view_projection(TypeCamera* type_cam, CoordSystem coord_system);

        /**
                  eye: the position of the camera in the world space.
            direction: the point the camera is looking at.
                   up: the upward direction from the camera, which defines 
                       the orientation of the camera
         */
        Vector4 eye, direction, up;
        /**
           forward vector: pointing in the direction camera is looking
             right vector: is perpendicular to both the forward  and the up vector. 
                           It represents the direction to the camera's right.
            new_up vector: perpendicular to both right and forward.
        **/
        Vector4 forward, right, new_up;            
};
