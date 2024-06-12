//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_CUBEMAP_H
#define SPACEGAME_CUBEMAP_H


#include "GL/glew.h"
#include "../GlFramebuffer.h"
#include "../Camera.h"

class Cubemap {
public:
    std::unique_ptr<Texture> texture;
    std::unique_ptr<GlFramebuffer> fbs[6];

    Cubemap(int width, bool useDepthBuffer, GLint internalformat, GLenum format);
    Cubemap(int width, bool useDepthBuffer);

    void bindToSide(uint8_t side, glm::dvec3 &pos, Camera &camera);
};


#endif //SPACEGAME_CUBEMAP_H
