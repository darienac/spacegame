//
// Created by dacma on 4/9/2024.
//

#include "ShaderEnv.h"

ShaderEnv::ShaderEnv(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader) : ShaderProgram(vertexShader, fragmentShader) {}

void ShaderEnv::link() {
    ShaderProgram::link();

    const GLfloat quadVertices[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            -1.0f, 1.0f,
            1.0f, 1.0f
    };
    const GLint quadFaces[] = {
            0, 1, 2,
            2, 1, 3
    };
    glGenBuffers(1, &verticesBuffer);
    glGenBuffers(1, &facesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadFaces), quadFaces, GL_STATIC_DRAW);

    aVertex = glGetAttribLocation(getProgramId(), "aVertex");
    glEnableVertexAttribArray(aVertex);

    // Setup uniforms
    envMap = glGetUniformLocation(getProgramId(), "envMap");
    uInverseViewProjectionMatrix = glGetUniformLocation(getProgramId(), "uInverseViewProjectionMatrix");
    uColorChannel = glGetUniformLocation(getProgramId(), "uColorChannel");
    uLightPosition = glGetUniformLocation(getProgramId(), "uLightPosition");
    uViewPosition = glGetUniformLocation(getProgramId(), "uViewPosition");
    uLightColor = glGetUniformLocation(getProgramId(), "uLightColor");

    // bind one time stuff
    ShaderProgram::bind();
    glUniform1i(envMap, 0);
}

void ShaderEnv::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(aVertex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    ShaderProgram::bind();
}

void ShaderEnv::loadEnvMap(Texture *t) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t->getTextureId());
}

void ShaderEnv::setSceneProps(Environment* env, uint8_t colorChannel) {
    glUniform1ui(uColorChannel, colorChannel);
    glUniform3fv(uLightColor, 1, &env->lightColor[0]);
    glUniform3fv(uLightPosition, 1, &env->lightPos[0]);
}

void ShaderEnv::draw() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // 6 for a quad
}

void ShaderEnv::loadCamera(Camera *camera) {
    glUniform3fv(uViewPosition, 1, &camera->getPos()[0]);
    glUniformMatrix4fv(uInverseViewProjectionMatrix, 1, GL_FALSE, &glm::inverse(camera->getViewProjectionMatrix())[0][0]);
}
