//
// Created by dacma on 5/12/2024.
//

#include "ShaderPerlin.h"
#include "UniformBlock.h"
#include "UniformBlockCache.h"

ShaderPerlin::ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader)
        : Shader2D(vertexShader, fragmentShader) {
    ubPerlinConfig = uniformBlock("ubPerlinConfig", UniformBlock::PERLIN_CONFIG);
}

void ShaderPerlin::loadPerlinConfig(const PerlinNoise &config) {
    UniformBlockCache::getPerlinNoiseBlock(config)->setBindingPoint(UniformBlock::PERLIN_CONFIG);
}

void ShaderPerlin::drawToCubemap(PerlinNoise *noise, Cubemap *cubemap) {
    loadPerlinConfig(*noise);
    draw(cubemap);
}
