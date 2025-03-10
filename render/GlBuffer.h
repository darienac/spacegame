//
// Created by dacma on 5/11/2024.
//

#ifndef SPACEGAME_GLBUFFER_H
#define SPACEGAME_GLBUFFER_H


#include <vector>
#include "GL/glew.h"

class GlBuffer {
protected:
    GLuint id;
public:
    GlBuffer();
    GlBuffer(GLsizeiptr size, const GLfloat *data);
    GlBuffer(GLsizeiptr size, const GLint *data);
    GlBuffer(const std::vector<GLfloat>& data);
    GlBuffer(const std::vector<GLint>& data);

    void bind(GLenum target);
    void bind();
    void bindToAttribute(GLint attribute, GLint size);
    void bufferData(GLsizeiptr size, const void *data, GLenum usage);
    void bufferData(GLsizeiptr size, const void *data);
    void subData(GLintptr offset, GLsizeiptr size, const void *data);
    void subData(GLsizeiptr size, const void *data);
    ~GlBuffer();
};


#endif //SPACEGAME_GLBUFFER_H
