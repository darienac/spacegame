//
// Created by dacma on 5/12/2024.
//

#ifndef SPACEGAME_SHADERPERLIN_H
#define SPACEGAME_SHADERPERLIN_H


#include "Shader2D.h"
#include "../../game/GameState.h"
#include "../StateRenderCache.h"

class ShaderPerlin: public Shader2D {
private:
    GLuint ubPerlinConfig;
public:
    ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void loadPerlinConfig(const GameState::PerlinNoise &config);
};


#endif //SPACEGAME_SHADERPERLIN_H
