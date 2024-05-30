//
// Created by dacma on 4/3/2024.
//

#include "Shader2D.h"

std::string Shader2D::GLSL_HEADER = "shared/f2D_header.glsl";

void Shader2D::initBuffers() {
    STANDARD_MESH = std::make_unique<Mesh2D>(
        std::vector<GLfloat>{
            -1.0f, -1.0f,
            1.0f, -1.0f,
            -1.0f, 1.0f,
            1.0f, 1.0f
        }, std::vector<GLfloat>{
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
        }, std::vector<GLint>{
            0, 1, 2,
            2, 1, 3
    });

    TEX_POSX_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
    });
    TEX_NEGX_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
    });
    TEX_POSY_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
    });
    TEX_NEGY_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
    });
    TEX_POSZ_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
    });
    TEX_NEGZ_BUFFER = std::make_unique<GlBuffer>(std::vector<GLfloat>{
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
    });
}

Shader2D::Shader2D(const std::vector<std::string> &vertexShader, std::vector<std::string> fragmentShader) : ShaderProgram() {
    fragmentShader.insert(fragmentShader.begin(), GLSL_HEADER);
    createShaderFromPaths(vertexShader, GL_VERTEX_SHADER);
    createShaderFromPaths(fragmentShader, GL_FRAGMENT_SHADER);
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
    STANDARD_MESH->facesBuffer->bind(GL_ELEMENT_ARRAY_BUFFER);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // 6 for a quad
}

void Shader2D::bind(GlBuffer *texCoords) {
    ShaderProgram::bind();

    STANDARD_MESH->verticesBuffer->bindToAttribute(aVertex, 2);
    texCoords->bindToAttribute(aTexCoord, 3);
}

void Shader2D::bind() {
    bind(STANDARD_MESH->texCoordBuffer.get());

}

void Shader2D::loadTexture(Texture *texture) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
}

void Shader2D::draw(Cubemap *cubemap) {
    GlBuffer *buffers[] = {TEX_POSX_BUFFER.get(), TEX_NEGX_BUFFER.get(), TEX_POSY_BUFFER.get(), TEX_NEGY_BUFFER.get(), TEX_POSZ_BUFFER.get(), TEX_NEGZ_BUFFER.get()};
    for (uint8_t i = 0; i < 6; i++) {
        cubemap->fbs[i]->bind();
        bind(buffers[i]);
        draw();
    }
}

void Shader2D::draw(Mesh2D *mesh) {
    bind(mesh->texCoordBuffer.get());
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh->facesBuffer->bind(GL_ELEMENT_ARRAY_BUFFER);
    glDrawElements(GL_TRIANGLES, mesh->numFaceElements, GL_UNSIGNED_INT, nullptr); // 6 for a quad
}
