//
// Created by dacma on 5/12/2024.
//

#ifndef SPACEGAME_SHADERPERLIN_H
#define SPACEGAME_SHADERPERLIN_H


#include "Shader2D.h"
#include "../../game/state/GameState.h"

class ShaderPerlin: public Shader2D {
private:
    GLuint ubPerlinConfig;
public:
    ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void loadPerlinConfig(const PerlinNoise &config);
    void drawToCubemap(PerlinNoise *noise, Cubemap *cubemap);
    void drawToMesh(PerlinNoise *noise, Mesh2D *mesh);
};


#endif //SPACEGAME_SHADERPERLIN_H
