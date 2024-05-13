//
// Created by dacma on 3/29/2024.
//

#ifndef CS455GAME_ENVIRONMENT_H
#define CS455GAME_ENVIRONMENT_H


#include "glm/vec3.hpp"

class Environment {
public:
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    glm::vec3 ambientLightColor;
};


#endif //CS455GAME_ENVIRONMENT_H
