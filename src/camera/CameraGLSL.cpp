#include "../../include/math/Transforamation.hpp"
#include "../../third-party/glm/glm/trigonometric.hpp"
#include "../../include/camera/CameraGLSL.hpp"
#include "../../include/GLSL/export-data/export-camera/ExportVP.hpp"

CameraGLSL::CameraGLSL(size_t shader_id, const Camera& cam, TypeCamera* type_cam):
    shader_id (shader_id),
    cam(cam),
    type_cam_ptr(type_cam),
    first_click(false),
    sensitivity(0.3),
    speed(0.01),
    x_pos(0.0),
    y_pos(0.0),
    x_prev(0.0),
    y_prev(0.0)
{
    export_camera = new ExportVP();

}

CameraGLSL::CameraGLSL(size_t shader_id, ExportCamera* export_camera, const Camera& cam, TypeCamera* type_cam):
    shader_id(shader_id),
    export_camera(export_camera),
    cam(cam),
    type_cam_ptr(type_cam),
    first_click(false),
    sensitivity(0.3),
    speed(0.01),
    x_pos(0.0),
    y_pos(0.0),
    x_prev(0.0),
    y_prev(0.0)
{}

CameraGLSL::~CameraGLSL() {
    //TODO: destructor of TypeCamera
    if( type_cam_ptr != nullptr) {
        delete type_cam_ptr;
    }

    if( export_camera != nullptr) {
        delete export_camera;
    }
    
}

void CameraGLSL::export_projection(){
    export_camera->export_projection(shader_id, cam, type_cam_ptr);
}


void CameraGLSL::change_export(ExportCamera* _export_camera) {
    this->export_camera = _export_camera;
}

void CameraGLSL::change_shader(const size_t& _shader_id) {
    shader_id = _shader_id;
}

void CameraGLSL::handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height){
    // Handles key inputs for world-space movement (Up, Back, Left, Right, Front)
    // Move up (along the global Y axis)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.eye  = cam.eye - speed * cam.forward ; // Up
        /* cam.eye  = Transformation::translation(0.0, 0.0, -0.1) *  cam.eye; // Up  */
    }
    // Move back (along the global -Z axis)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.eye  =   cam.eye + cam.forward * speed  ; // Back
        /* cam.eye  = Transformation::translation(0.0, 0.0,  0.1) *  cam.eye; // */
    }
    // Move left (along the global -X axis)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.eye  =  cam.eye - speed * (cam.direction | cam.up).normalize(); // Left
        /* cam.eye  = -speed * camera.right + cam.eye; // Right */
        /* cam.eye  = Transformation::translation( -0.1,  0.0,  0.0) *  cam.eye; //  */
    }
    // Move right (along the global X axis)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam.eye  =  cam.eye + speed * (cam.direction | cam.up).normalize(); // Left
        /* cam.eye  = speed * camera.right + cam.eye; // Right */
        /* cam.eye  = Transformation::translation( 0.1,  0.0,  0.0) *  cam.eye; //  */
    }
    // Move front (along the global Z axis)
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cam.eye  =  speed * cam.new_up + cam.eye; // Front
        /* cam.eye  = Transformation::translation( 0.0 ,  0.1,  0.0) *  cam.eye; // */
    }
    // Move down (along the global -Y axis)
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        /* cam.eye  = Transformation::translation( 0.0,   -0.1,  0.0) *  cam.eye;  */
        cam.eye  =   cam.eye - speed * cam.new_up  ; // Front
    }
    
    // Speed boost with shift
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = 0.4f; // Increase speed
    } else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        speed = 0.1f; // Reset speed
    }
    // Handles mouse inputs for rotation (camera orientation)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
        // Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(window, width / 2.0, height / 2.0);
        // Prevent camera jump on first click
        if (first_click) {
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
            /* x_pos = width / 2.0; */
            /* y_pos = height / 2.0; */
            first_click = false;
        }
        // Get cursor position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        x_pos = mouseX;
        y_pos = mouseY;
        // Calculate rotation based on cursor movement
        /* float rotX = sensitivity * (float)(mouseY - (height / 2.0)) / height; */
        float rotY = sensitivity * (x_pos - x_prev);
        /* float rotY = sensitivity * (float)(mouseX - (width / 2.0)) / width; */
        float rotX = sensitivity * (y_pos - y_prev);
        x_prev = x_pos;
        y_prev = y_pos;
        // Vertical rotation (rotate around global X axis)j
        Vector4 newDirection = Transformation::rotation(glm::radians( -rotX) , (cam.direction | cam.up).normalize() ) * cam.direction;
        if (fabs(acos(newDirection.y) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
            cam.direction = newDirection;
        }
        cam.direction = Transformation::rotation(glm::radians( -rotY) , cam.up) * cam.direction;
        // Horizontal rotation (rotate around global Y axis)
        // Reset the cursor to the center of the screen
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        x_prev = x_pos;
        y_prev = y_pos;
        glfwSetCursorPos(window, width / 2.0, height / 2.0);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        first_click = true;

        
    }

}

