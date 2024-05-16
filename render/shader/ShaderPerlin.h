//
// Created by dacma on 5/12/2024.
//

#ifndef SPACEGAME_SHADERPERLIN_H
#define SPACEGAME_SHADERPERLIN_H


#include "Shader2D.h"
#include "../../game/GameState.h"
#include "../StateRenderCache.h"
#include "IPerlinRenderer.h"

class ShaderPerlin: public Shader2D, public IPerlinRenderer {
private:
    GLuint ubPerlinConfig;
public:
    ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void loadPerlinConfig(const GameState::PerlinNoise &config);
    void drawToCubemap(GameState::PerlinNoise *noise, Cubemap *cubemap) override;
};


#endif //SPACEGAME_SHADERPERLIN_H
