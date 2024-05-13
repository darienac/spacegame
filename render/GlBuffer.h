//
// Created by dacma on 5/11/2024.
//

#ifndef SPACEGAME_GLBUFFER_H
#define SPACEGAME_GLBUFFER_H


#include <vector>
#include "GL/glew.h"

class GlBuffer {
private:
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
    void bufferData(GLsizeiptr size, const GLfloat *data);
    void bufferData(GLsizeiptr size, const GLint *data);

    ~GlBuffer();
};


#endif //SPACEGAME_GLBUFFER_H
