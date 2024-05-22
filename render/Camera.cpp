//
// Created by dacma on 3/17/2024.
//

#include "Camera.h"

Camera::Camera(GlWindow* window) {
    this->window = window;
    fovy = 45 * (M_PI / 180);
    zNear = 0.001f;
    zFar = 10000.0f;
    pos = {0.0f, 0.0f, 10.0f};
    target = {0.0f, 0.0f, 0.0f};
    up = {0.0f, 1.0f, 0.0f};
}

void Camera::shiftPos(glm::vec3 value) {
    pos += value;
//    target += value;
}

glm::vec3 Camera::getPos() {
    return pos;
}

glm::mat4 Camera::getViewProjectionMatrix(float aspect) {
    glm::mat4 project = glm::infinitePerspective(fovy, aspect, zNear);
    glm::mat4 view = glm::lookAt(pos, target, up);

    return project * view;
}

glm::mat4 Camera::getViewProjectionMatrix() {
    return getViewProjectionMatrix((float) window->getWidth() / window->getHeight());
}

void Camera::setPos(glm::vec3 value) {
    pos = value;
}

void Camera::setTarget(glm::vec3 value) {
    target = value;
}

void Camera::setUp(glm::vec3 value) {
    up = value;
}
