//
// Created by dacma on 5/12/2024.
//

#ifndef SPACEGAME_SHADERPERLIN_H
#define SPACEGAME_SHADERPERLIN_H


#include "Shader2D.h"
#include "../../game/state/GameState.h"
#include "glm/mat4x4.hpp"

class ShaderPerlin: public Shader2D {
private:
    GLuint ubPerlinConfig;

    // uniforms
    GLint uTexCoordTransform;
public:
    ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void loadPerlinConfig(const PerlinNoise &config, const glm::mat4 &transform);
    void drawToCubemap(const PerlinNoise *noise, Cubemap *cubemap);
    void drawToMesh(const PerlinNoise *noise, const glm::mat4 &texCoordTransform, Mesh2D *mesh);
};


#endif //SPACEGAME_SHADERPERLIN_H
