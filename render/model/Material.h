//
// Created by dacma on 3/20/2024.
//

#ifndef CS455GAME_MATERIAL_H
#define CS455GAME_MATERIAL_H


#include <assimp/material.h>
#include <glm/vec3.hpp>
#include "Texture.h"

class Material {
public:
    Material(aiMaterial* material);

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
//    float reflectance;
    float opacity;
    Texture* texture;
};


#endif //CS455GAME_MATERIAL_H
