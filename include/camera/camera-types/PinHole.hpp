#pragma once
#include "../DataCamera.hpp"
/* #include "CameraRender.hpp" */

class PinHole {
    public:
        PinHole(Vector3 eye, Vector3 look_at, Vector3 up, double dis, double zoom);
        
        PinHole&    with_eye(Vector3 eye);
        PinHole& with_lookAt(Vector3 look_at);
        PinHole&     with_up(Vector3 eye);
        PinHole&   with_zoom(double zoom);
        PinHole&    with_dis(double dis);
            
        
    private:
        double             dis;
        double            zoom;
        DataCamera    cam_data;
};
