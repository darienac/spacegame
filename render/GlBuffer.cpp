//
// Created by dacma on 5/11/2024.
//

#include <iostream>
#include "GlBuffer.h"

GlBuffer::GlBuffer() {
    glGenBuffers(1, &id);
    std::cout << "Buffer Created" << std::endl;
}

GlBuffer::GlBuffer(GLsizeiptr size, const GLfloat *data): GlBuffer() {
    bufferData(size, data);
}

GlBuffer::GlBuffer(GLsizeiptr size, const GLint *data): GlBuffer() {
    bufferData(size, data);
}

GlBuffer::GlBuffer(const std::vector<GLfloat> &data): GlBuffer(data.size() * sizeof(GLfloat), data.data()) {

}

GlBuffer::GlBuffer(const std::vector<GLint> &data): GlBuffer(data.size() * sizeof(GLint), data.data()) {

}

void GlBuffer::bind(GLenum target) {
    glBindBuffer(target, id);
}

void GlBuffer::bind() {
    bind(GL_ARRAY_BUFFER);
}

void GlBuffer::bindToAttribute(GLint attribute, GLint size) {
    bind();
    glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GlBuffer::bufferData(GLsizeiptr size, const GLfloat *data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void GlBuffer::bufferData(GLsizeiptr size, const GLint *data) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

GlBuffer::~GlBuffer() {
    glDeleteBuffers(1, &id);
}
