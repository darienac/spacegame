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

void Cubemap::bindToSide(uint8_t side, glm::dvec3 &pos, Camera &camera) {
    fbs[side]->bind();
    camera.setPos(pos);
    camera.setFOV(90.0);
    switch (side + GL_TEXTURE_CUBE_MAP_POSITIVE_X) {
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
            camera.setFacingDir({1.0, 0.0, 0.0});
            camera.setUp({0.0, -1.0, 0.0});
            break;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
            camera.setFacingDir({-1.0, 0.0, 0.0});
            camera.setUp({0.0, -1.0, 0.0});
            break;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
            camera.setFacingDir({0.0, 1.0, 0.0});
            camera.setUp({0.0, 0.0, 1.0});
            break;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
            camera.setFacingDir({0.0, -1.0, 0.0});
            camera.setUp({0.0, 0.0, -1.0});
            break;
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            camera.setFacingDir({0.0, 0.0, 1.0});
            camera.setUp({0.0, -1.0, 0.0});
            break;
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
            camera.setFacingDir({0.0, 0.0, -1.0});
            camera.setUp({0.0, -1.0, 0.0});
            break;
        default:
            throw std::runtime_error("Not possible!");
    }
}
