//
// Created by dacma on 2/21/2024.
//

#include "ShaderProgram.h"

GLuint ShaderProgram::createShader(const std::vector<std::string> &code, GLenum shaderType) const {
    GLuint shaderId = glCreateShader(shaderType);
    if (shaderId == 0) {
        std::cerr << "Error creating shader, type: " << shaderType;
    }

    const char** strings = new const char*[code.size()];
    for (size_t i = 0; i < code.size(); i++) {
        strings[i] = code[i].c_str();
    }
    glShaderSource(shaderId, code.size(), strings, nullptr);
    delete[] strings;
    glCompileShader(shaderId);

    GLint paramValue;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &paramValue);
    if (paramValue == 0) {
        char log[1024];
        glGetShaderInfoLog(shaderId, 1024, nullptr, log);
        std::cerr << "Error compiling shader code:" << std::endl << log;
    }

    glAttachShader(programId, shaderId);
    return shaderId;
}

GLint ShaderProgram::attribute(const std::string &name) const {
    GLint out = glGetAttribLocation(programId, name.c_str());
    glEnableVertexAttribArray(out);
    return out;
}

GLint ShaderProgram::uniform(const std::string &name) const {
    return glGetUniformLocation(programId, name.c_str());
}

ShaderProgram::ShaderProgram() {
    programId = glCreateProgram();
    if (programId == 0) {
        std::cerr << "Could not create shader";
    }
}

ShaderProgram::ShaderProgram(const std::vector<std::string> &vertexShader,
                             const std::vector<std::string> &fragmentShader): ShaderProgram() {
    createShaderFromPaths(vertexShader, GL_VERTEX_SHADER);
    createShaderFromPaths(fragmentShader, GL_FRAGMENT_SHADER);
}

void ShaderProgram::createShaderFromPaths(const std::vector<std::string> &paths, GLenum shaderType) {
    std::vector<std::string> code;
    code.reserve(paths.size());
    for (const std::string &path : paths) {
        code.push_back(ResourceReader::readResource(ResourceReader::Shader, path));
    }
    GLuint shaderId = createShader(code, shaderType);
    switch (shaderType) {
        case GL_VERTEX_SHADER:
            vertexShaderId = shaderId;
            return;
        case GL_FRAGMENT_SHADER:
            fragmentShaderId = shaderId;
            return;
        default:
            throw std::runtime_error("Unsupported shader type");
    }
}

void ShaderProgram::link() {
    glLinkProgram(programId);

    GLint paramValue;
    glGetProgramiv(programId, GL_LINK_STATUS, &paramValue);
    if (paramValue == 0) {
        GLsizei length;
        GLchar infoLog[1024];
        glGetProgramInfoLog(programId, 1024, &length, infoLog);
        std::cerr << "Error linking shader code:\n" << std::string(infoLog, length);
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
}

void ShaderProgram::validate() const {
    GLint paramValue;
    glValidateProgram(programId);
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &paramValue);
    if (paramValue == 0) {
        GLsizei length;
        GLchar infoLog[1024];
        glGetProgramInfoLog(programId, 1024, &length, infoLog);
        std::cerr << "Error validating shader code:\n" << std::string(infoLog, length);
    }
}

void ShaderProgram::bind() {
    glUseProgram(programId);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

void ShaderProgram::bindTexture(GLenum textureUnit, const Texture &texture) {
    glActiveTexture(textureUnit);
    glBindTexture(texture.getTextureType(), texture.getTextureId());
}

GLuint ShaderProgram::getProgramId() const {
    return programId;
}

ShaderProgram::~ShaderProgram() {
    unbind();
    if (getProgramId() != 0) {
        glDeleteProgram(getProgramId());
    }
}