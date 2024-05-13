//
// Created by dacma on 5/12/2024.
//

#include "ShaderPerlin.h"

ShaderPerlin::ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader)
        : Shader2D(vertexShader, fragmentShader) {
    ShaderPerlin::link();
}

void ShaderPerlin::link() {

}
