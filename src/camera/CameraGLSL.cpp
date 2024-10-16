#include <glm/trigonometric.hpp>
#include "../../include/math/Transforamation.hpp"
#include "../../include/camera/CameraGLSL.hpp"
#include "../../include/GLSL/export-data/export-camera/ExportProjection.hpp"

CameraGLSL::CameraGLSL(size_t id, const Camera& cam, TypeCamera* type_cam, const char* uniform_proj):
    cam(cam),
    type_cam_ptr(type_cam),
    uniform_proj(uniform_proj),
    first_click(false),
    sensitivity(5.0),
    speed(0.01)
{
    data_manager = new ExportProjection(id );

}

CameraGLSL::CameraGLSL(ExportCamera* export_camera, const Camera& cam, TypeCamera* type_cam, const char* uniform_proj):
    data_manager(export_camera),
    cam(cam),
    type_cam_ptr(type_cam),
    uniform_proj(uniform_proj),
    first_click(false),
    sensitivity(5.0),
    speed(0.01)
{}

CameraGLSL::~CameraGLSL() {
    //TODO: destructor of TypeCamera
    if( type_cam_ptr != nullptr) {
        delete type_cam_ptr;
    }

    if( data_manager != nullptr) {
        delete data_manager;
    }
    
}

void CameraGLSL::export_projection(){
    data_manager->export_projection(cam, type_cam_ptr);
}
void CameraGLSL::delete_projection(){
    data_manager->delete_projection(cam, type_cam_ptr);
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
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
        // Prevent camera jump on first click
        if (first_click) {
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
            first_click = false;
        }
        // Get cursor position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        // Calculate rotation based on cursor movement
        float rotX = sensitivity * (float)(mouseY - (height / 2.0)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2.0)) / width;
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
        // Show cursor when the camera is not rotating
        /* glfwSetCursorPos(window, width / 2.0, height / 2.0); */
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        first_click = true;
        
    }

}
