//
// Created by dacma on 3/17/2024.
//

#include "Camera.h"

Camera::Camera() {
    fovy = 90.0 * (M_PI / 180);
    zNear = 0.1;
    zFar = 100000.0;
    pos = {0.0, 0.0, 10.0};
    target = {0.0, 0.0, 0.0};
    up = {0.0, 1.0, 0.0};
    aspect = 1.0;
}

glm::dvec3 Camera::getPos() {
    return pos;
}

glm::dmat4 Camera::getViewProjectionMatrix() {
    glm::dmat4 project = glm::perspective(fovy, aspect, zNear, zFar);
    glm::dmat4 view = glm::lookAt(pos, target, up);

    return project * view;
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

void Camera::setFOV(double value) {
    fovy = value * (M_PI / 180);
}

void Camera::setAspectRatio(double aspect) {
    this->aspect = aspect;
}

void Camera::setFacingDir(glm::dvec3 value) {
    target = pos + value;
}
