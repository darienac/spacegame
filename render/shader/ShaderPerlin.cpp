//
// Created by dacma on 5/12/2024.
//

#include "ShaderPerlin.h"
#include "UniformBlock.h"
#include "UniformBlockCache.h"

ShaderPerlin::ShaderPerlin(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader)
        : Shader2D(vertexShader, fragmentShader) {
    ubPerlinConfig = uniformBlock("ubPerlinConfig", UniformBlock::PERLIN_CONFIG);
    uTexCoordTransform = uniform("uTexCoordTransform");
}

void ShaderPerlin::loadPerlinConfig(const PerlinNoise &config, const glm::mat4 &transform) {
    bind();
    glUniformMatrix4fv(uTexCoordTransform, 1, GL_FALSE, &transform[0][0]);
    UniformBlockCache::getPerlinNoiseBlock(config)->setBindingPoint(UniformBlock::PERLIN_CONFIG);
}

void ShaderPerlin::drawToCubemap(const PerlinNoise *noise, Cubemap *cubemap) {
    loadPerlinConfig(*noise, glm::mat4(1.0f));
    draw(cubemap);
}

void ShaderPerlin::drawToMesh(const PerlinNoise *noise, const glm::mat4 &texCoordTransform, Mesh2D *mesh) {
    loadPerlinConfig(*noise, texCoordTransform);
    draw(mesh);
}
