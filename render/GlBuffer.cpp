//
// Created by dacma on 5/11/2024.
//

#include <iostream>
#include "GlBuffer.h"
#include "../GlobalFlags.h"

GlBuffer::GlBuffer() {
    glGenBuffers(1, &id);
    if (GlobalFlags::DEBUG && GlobalFlags::SHOW_RES_ALLOC) {
        std::cout << "Buffer Created" << std::endl;
    }
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

void GlBuffer::bufferData(GLsizeiptr size, const void *data, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void GlBuffer::bufferData(GLsizeiptr size, const void *data) {
    bufferData(size, data, GL_STATIC_DRAW);
}

void GlBuffer::subData(GLintptr offset, GLsizeiptr size, const void *data) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void GlBuffer::subData(GLsizeiptr size, const void *data) {
    subData(0, size, data);
}

GlBuffer::~GlBuffer() {
    glDeleteBuffers(1, &id);
}
