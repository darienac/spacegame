//
// Created by dacma on 5/13/2024.
//

#include "UniformBlock.h"

UniformBlock::UniformBlock(Material *material): GlBuffer() {
    GLSL_Material buffer = {
        .ambient = material->ambient,
        .diffuse = material->diffuse,
        .specular = material->specular,
        .emissive = material->emissive,
        .opacity = material->opacity
    };

    bufferData(sizeof(buffer), &buffer);
}

void UniformBlock::setBindingPoint(GLuint index) {
    bind(GL_UNIFORM_BUFFER);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}
