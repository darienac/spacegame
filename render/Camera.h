//
// Created by dacma on 3/17/2024.
//

#ifndef CS455GAME_CAMERA_H
#define CS455GAME_CAMERA_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../GlWindow.h"

class Camera {
private:
    double fovy;
    double zNear;
    double zFar;
    glm::dvec3 pos;
    glm::dvec3 target;
    glm::dvec3 up;
    GlWindow* window;
public:
    explicit Camera(GlWindow* window);

    glm::dvec3 getPos();
    glm::dmat4 getViewProjectionMatrix();
    glm::dmat4 getViewProjectionMatrix(double aspect);

    void setPos(glm::dvec3 value);
    void setTarget(glm::dvec3 value);
    void setUp(glm::dvec3 value);
};


#endif //CS455GAME_CAMERA_H
