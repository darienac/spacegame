//
// Created by dacma on 5/13/2024.
//

#include "Cubemap.h"

Cubemap::Cubemap(int width, bool useDepthBuffer, GLint internalformat, GLenum format) {
    texture = std::make_unique<Texture>(width, width, internalformat, format, GL_TEXTURE_CUBE_MAP);
    for (uint8_t i = 0; i < 6; i++) {
        fbs[i] = std::make_unique<GlFramebuffer>(std::vector<Texture*>{texture.get()}, useDepthBuffer, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }
}

Cubemap::Cubemap(int width, bool useDepthBuffer): Cubemap(width, useDepthBuffer, GL_RGBA, GL_RGBA) {}
