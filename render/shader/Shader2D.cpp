//
// Created by dacma on 4/3/2024.
//

#include "Shader2D.h"

void Shader2D::initBuffers() {
    VERTICES_BUFFER = new GlBuffer(std::vector<GLfloat>{
            -1.0f, -1.0f,
            1.0f, -1.0f,
            -1.0f, 1.0f,
            1.0f, 1.0f
    });
    TEX_BUFFER = new GlBuffer(std::vector<GLfloat>{
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
    });
    TEX_POSX_BUFFER = new GlBuffer(std::vector<GLfloat>{
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
    });
    TEX_NEGX_BUFFER = new GlBuffer(std::vector<GLfloat>{
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
    });
    TEX_POSY_BUFFER = new GlBuffer(std::vector<GLfloat>{
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
    });
    TEX_NEGY_BUFFER = new GlBuffer(std::vector<GLfloat>{
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
    });
    TEX_POSZ_BUFFER = new GlBuffer(std::vector<GLfloat>{
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
    });
    TEX_NEGZ_BUFFER = new GlBuffer(std::vector<GLfloat>{
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
    });
    FACES_BUFFER = new GlBuffer(std::vector<GLint>{
            0, 1, 2,
            2, 1, 3
    });
}

Shader2D::Shader2D(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader) : ShaderProgram(vertexShader, fragmentShader) {
    Shader2D::link();
}

void Shader2D::link() {
    ShaderProgram::link();

    aVertex = attribute("aVertex");
    aTexCoord = attribute("aTexCoord");

    uTexture = uniform("uTexture");

    // bind one time stuff
    ShaderProgram::bind();
    glUniform1i(uTexture, 0);
}

void Shader2D::draw() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    FACES_BUFFER->bind(GL_ELEMENT_ARRAY_BUFFER);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // 6 for a quad
}

void Shader2D::bind(GlBuffer *texCoords) {
    ShaderProgram::bind();

    VERTICES_BUFFER->bindToAttribute(aVertex, 2);
    texCoords->bindToAttribute(aTexCoord, 3);
}

void Shader2D::bind() {
    bind(TEX_BUFFER);
}

void Shader2D::loadTexture(Texture *texture) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
}

Shader2D::~Shader2D() {
//    delete VERTICES_BUFFER;
//    delete TEX_BUFFER;
//    delete FACES_BUFFER;
}

void Shader2D::draw(Cubemap *cubemap) {
    GlBuffer *buffers[] = {TEX_POSX_BUFFER, TEX_NEGX_BUFFER, TEX_POSY_BUFFER, TEX_NEGY_BUFFER, TEX_POSZ_BUFFER, TEX_NEGZ_BUFFER};
    for (uint8_t i = 0; i < 6; i++) {
        cubemap->fbs[i]->bind();
        bind(buffers[i]);
        draw();
    }
}
