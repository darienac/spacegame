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
    static Material blend(Material &mat1, Material &mat2, float bias);

    Material(aiMaterial* material);
    Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const glm::vec3 &emissive, float opacity, float glossiness);

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    float opacity;
    float glossiness;
    Texture* texture;

    void load(const Material &material);
};


#endif //CS455GAME_MATERIAL_H
