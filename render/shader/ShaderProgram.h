//
// Created by dacma on 2/21/2024.
//

#ifndef CS455GAME_SHADERPROGRAM_H
#define CS455GAME_SHADERPROGRAM_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../util/ResourceReader.h"
#include "../model/Texture.h"


class ShaderProgram {
private:
    GLuint programId;
    GLuint vertexShaderId;
    GLuint fragmentShaderId;

    [[nodiscard]] GLuint createShader(const std::vector<std::string> &code, GLenum shaderType) const;
protected:
    [[nodiscard]] GLint attribute(const std::string &name) const;
    [[nodiscard]] GLint uniform(const std::string &name) const;
    GLuint uniformBlock(const std::string &name, GLuint blockBinding) const;
public:
    ShaderProgram();
    ShaderProgram(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void createShaderFromPaths(const std::vector<std::string> &paths, GLenum shaderType);
    virtual void link();
    void validate() const;

    virtual void bind();
    static void unbind();

    void bindTexture(GLenum textureUnit, const Texture& texture);

    GLuint getProgramId() const;

    virtual ~ShaderProgram();
};




#endif //CS455GAME_SHADERPROGRAM_H
