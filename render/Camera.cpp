//
// Created by dacma on 3/17/2024.
//

#include "Camera.h"

Camera::Camera(GlWindow* window) {
    this->window = window;
    fovy = 45 * (M_PI / 180);
    zNear = 0.1;
    zFar = 100000.0;
    pos = {0.0, 0.0, 10.0};
    target = {0.0, 0.0, 0.0};
    up = {0.0, 1.0, 0.0};
}

glm::dvec3 Camera::getPos() {
    return pos;
}

glm::dmat4 Camera::getViewProjectionMatrix(double aspect) {
    glm::dmat4 project = glm::infinitePerspective(fovy, aspect, zNear);
    glm::dmat4 view = glm::lookAt(pos, target, up);

    return project * view;
}

glm::dmat4 Camera::getViewProjectionMatrix() {
    return getViewProjectionMatrix((double) window->getWidth() / window->getHeight());
}

void Camera::setPos(glm::dvec3 value) {
    pos = value;
}

void Camera::setTarget(glm::dvec3 value) {
    target = value;
}

void Camera::setUp(glm::dvec3 value) {
    up = value;
}
