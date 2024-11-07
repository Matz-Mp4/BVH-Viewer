#include "../../include/objects/GeometricObjectGLSL.hpp"
#include "../../include/GLSL/export-data/export-object/ExportMMT.hpp"
#include "../../include/math/Transforamation.hpp"
#include "../../third-party/glm/glm/trigonometric.hpp"

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, const GeometricObject& object) :
    object(object),
    shader_id(shader_id)
{
    export_object = new ExportMMT();
}

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, const GeometricObject& object):
    export_object(export_object),
    shader_id(shader_id),
    object(object)
{}

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, IShape* shape) :
    export_object(export_object),
    shader_id(shader_id)
{
    object = object.with_shape(shape);
}

void GeometricObjectGLSL::export_mesh() {
    export_object->export_mesh(object.get_mesh(), vao, vbo, ebo);
}

void GeometricObjectGLSL::delete_mesh() {
    export_object->delete_mesh(vao, vbo, ebo);
    
}

void GeometricObjectGLSL::export_material() {
    export_object->export_material(shader_id, object.get_material());
}

void GeometricObjectGLSL::export_transformation() {
    export_object->export_transformation(shader_id, object.get_transformation());
}



void GeometricObjectGLSL::change_export(ExportObject* _export_object) {
    this->export_object = _export_object;
}

 void GeometricObjectGLSL::change_shader(const size_t& _shader_id) {
     shader_id = _shader_id;
 }

void GeometricObjectGLSL::draw() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, object.get_indices().size(), GL_UNSIGNED_INT, 0);
       
}

void GeometricObjectGLSL::handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height) {
    // Get the current mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseY, &mouseX);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!is_dragging) {
            // Start dragging
            is_dragging = true;
            last_x = mouseX;
            last_y = mouseY;
        } else {
            float deltaX = mouseX - last_x;
            float deltaY = mouseY - last_y;

            last_x = mouseX;
            last_y = mouseY;

            float sensitivity = 0.2f;
            float angle = sqrt(deltaX * deltaX + deltaY * deltaY) * sensitivity;
            Matrix4 rotate_x = Transformation::rotation_x(glm::radians(deltaX * sensitivity));
            Matrix4 rotate_y = Transformation::rotation_y(glm::radians(deltaY * sensitivity));

            Matrix4 rotationMatrix = rotate_x * rotate_y;
            object.transform(rotationMatrix);
        }
    } else {
        is_dragging = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        Matrix4 scaling = Transformation::scaling(1.2, 1.2, 1.2);
        object.transform(scaling);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        Matrix4 scaling = Transformation::scaling(0.8, 0.8, 0.8);
        object.transform(scaling);
    }
}

