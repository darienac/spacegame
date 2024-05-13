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
    float fovy;
    float zNear;
    float zFar;
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
    GlWindow* window;
public:
    explicit Camera(GlWindow* window);
    void shiftPos(glm::vec3 value);

    glm::vec3 getPos();
    glm::mat4 getViewProjectionMatrix();
    glm::mat4 getViewProjectionMatrix(float aspect);

    void setPos(glm::vec3 value);
    void setTarget(glm::vec3 value);
    void setUp(glm::vec3 value);
};


#endif //CS455GAME_CAMERA_H
