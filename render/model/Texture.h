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
    bool useMultisampling;

public:
    Texture(const std::string& fileName);
    Texture(int width, int height, GLint internalformat, GLenum format, bool useMultisampling);
    Texture(int width, int height);

    void resize(int width, int height);
    void load(const std::string& fileName);

    void bind();

    GLuint getTextureId() const;
    int getWidth() const;
    int getHeight() const;
    bool usesMultisampling() const;

    ~Texture();
};


#endif //CS455GAME_TEXTURE_H
