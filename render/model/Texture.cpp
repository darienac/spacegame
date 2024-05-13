//
// Created by dacma on 2/21/2024.
//

#include <stb_image.h>
#include "Texture.h"

Texture::Texture(const std::string &fileName) {
    textureId = -1;
    useMultisampling = false;

    load(fileName);
}

Texture::Texture(int width, int height, GLint internalformat, GLenum format, bool useMultisampling): internalformat(internalformat), format(format), useMultisampling(useMultisampling) {
    glGenTextures(1, &textureId);
    if ((int) textureId < 0) {
        throw "Unable to create texture";
    }

    resize(width, height);
}

Texture::Texture(int width, int height): Texture(width, height, GL_RGBA, GL_RGBA, false) {}

void Texture::resize(int width, int height) {
    std::cout << "Texture resize" << std::endl;
    this->width = width;
    this->height = height;

    bind();
    if (useMultisampling) {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, internalformat, width, height, GL_TRUE);

//        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

void Texture::load(const std::string &fileName) {
    if (textureId != (GLuint) -1) {
        throw "Texture already loaded";
    }

    stbi_set_flip_vertically_on_load(true);

    int avChannels;
    stbi_uc *decodedImage = stbi_load(ResourceReader::getFullPath(ResourceReader::Texture, fileName).c_str(), &width, &height, &avChannels, 4);

    glGenTextures(1, &textureId);
    if (textureId < 0) {
        throw "Unable to create texture";
    }

    bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, decodedImage);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(decodedImage);
}

void Texture::bind() {
    if (useMultisampling) {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureId);
    } else {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
}

GLuint Texture::getTextureId() const {
    return textureId;
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

bool Texture::usesMultisampling() const {
    return useMultisampling;
}

Texture::~Texture() {
    if (getTextureId() == (GLuint) -1) {
        std::printf("Fake texture %d deleted\n", getTextureId());
        return;
    }
    std::printf("Texture %d deleted\n", getTextureId());
    glDeleteTextures(1, &textureId);
}
