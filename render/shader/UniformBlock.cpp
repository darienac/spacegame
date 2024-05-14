//
// Created by dacma on 5/13/2024.
//

#include "UniformBlock.h"

void UniformBlock::loadVec3(GLfloat *buffer, const glm::vec3 &data) {
    buffer[0] = data.x;
    buffer[1] = data.y;
    buffer[2] = data.z;
    buffer[3] = 0.0f;
}

UniformBlock::UniformBlock(Material *material): GlBuffer() {
    GLfloat buffer[16];
    loadVec3(buffer, material->ambient);
    loadVec3(buffer + 4, material->diffuse);
    loadVec3(buffer + 8, material->specular);
    loadVec3(buffer + 12, material->emissive);
    buffer[15] = material->opacity;

    bufferData(sizeof(buffer), buffer);
}

void UniformBlock::setBindingPoint(GLuint index) {
    bind(GL_UNIFORM_BUFFER);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}
