//
// Created by dacma on 4/9/2024.
//

#ifndef CS455GAME_SHADERENV_H
#define CS455GAME_SHADERENV_H

#include "ShaderProgram.h"
#include "../Environment.h"
#include "../Camera.h"

class ShaderEnv: public ShaderProgram {
private:
    GLuint verticesBuffer, facesBuffer;

    // attributes
    GLint aVertex;

    // uniforms
    GLint envMap;

    GLint uInverseViewProjectionMatrix;

    GLint uColorChannel;
    GLint uLightPosition;
    GLint uViewPosition;
    GLint uLightColor;
public:
    ShaderEnv(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void loadEnvMap(Texture* t);
    void setSceneProps(Environment* env, uint8_t colorChannel);
    void loadCamera(Camera* camera);

    void draw();

    void link() override;
    void bind() override;
};


#endif //CS455GAME_SHADERENV_H
