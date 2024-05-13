//
// Created by dacma on 5/12/2024.
//

#ifndef SPACEGAME_SHADERPERLIN_H
#define SPACEGAME_SHADERPERLIN_H


#include "Shader2D.h"

class ShaderPerlin: public Shader2D {
private:
public:
    ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void link() override;
};


#endif //SPACEGAME_SHADERPERLIN_H
