//
// Created by dacma on 2/21/2024.
//

#include <stb_image.h>
#include "Texture.h"
#include "../../GlobalFlags.h"

Texture::Texture(const std::string &fileName) {
    textureId = -1;
    textureType = GL_TEXTURE_2D;

    load(fileName);
}

Texture::Texture(int width, int height, GLint internalformat, GLenum format, GLenum textureType): internalformat(internalformat), format(format), textureType(textureType) {
    glGenTextures(1, &textureId);
    if ((int) textureId < 0) {
        throw std::runtime_error("Unable to create texture");
    }

    resize(width, height);
}

Texture::Texture(int width, int height): Texture(width, height, GL_RGBA, GL_RGBA, GL_TEXTURE_2D) {}

void Texture::resize(int width, int height) {
    if (GlobalFlags::DEBUG && GlobalFlags::SHOW_RES_ALLOC) {
        std::cout << "Texture resize" << std::endl;
    }
    this->width = width;
    this->height = height;

    bind();
    switch (textureType) {
        case GL_TEXTURE_2D_MULTISAMPLE:
            glTexImage2DMultisample(textureType, 4, internalformat, width, height, GL_TRUE);

//            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case GL_TEXTURE_2D:
            glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case GL_TEXTURE_CUBE_MAP:
            for (uint8_t i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            break;
        default:
            throw std::runtime_error("Unsupported texture type");
    }
}

void Texture::load(const std::string &fileName) { // only works for GL_TEXTURE_2D
    if (textureId != (GLuint) -1) {
        throw std::runtime_error("Texture already loaded");
    }

    stbi_set_flip_vertically_on_load(true);

    int avChannels;
    stbi_uc *decodedImage = stbi_load(ResourceReader::getFullPath(ResourceReader::Texture, fileName).c_str(), &width, &height, &avChannels, 4);

    glGenTextures(1, &textureId);
    if (textureId < 0) {
        throw std::runtime_error("Unable to create texture");
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
    glBindTexture(textureType, textureId);
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

GLenum Texture::getTextureType() const {
    return textureType;
}

Texture::~Texture() {
    if (getTextureId() == (GLuint) -1) {
        if (GlobalFlags::DEBUG && GlobalFlags::SHOW_RES_ALLOC) {
            std::printf("Fake texture %d deleted\n", getTextureId());
        }
        return;
    }
    if (GlobalFlags::DEBUG && GlobalFlags::SHOW_RES_ALLOC) {
        std::printf("Texture %d deleted\n", getTextureId());
    }
    glDeleteTextures(1, &textureId);
}
