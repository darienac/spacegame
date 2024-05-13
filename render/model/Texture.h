//
// Created by dacma on 2/21/2024.
//

#ifndef CS455GAME_TEXTURE_H
#define CS455GAME_TEXTURE_H


#include <iostream>
#include <GL/glew.h>

#include "../../util/ResourceReader.h"

class Texture {
private:
    GLuint textureId;
    GLint internalformat;
    GLenum format;
    int width;
    int height;
    GLenum textureType;

public:
    Texture(const std::string& fileName);
    Texture(int width, int height, GLint internalformat, GLenum format, GLenum textureType);
    Texture(int width, int height);

    void resize(int width, int height);
    void load(const std::string& fileName);

    void bind();

    [[nodiscard]] GLuint getTextureId() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] GLenum getTextureType() const;

    ~Texture();
};


#endif //CS455GAME_TEXTURE_H
