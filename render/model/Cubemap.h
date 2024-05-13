//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_CUBEMAP_H
#define SPACEGAME_CUBEMAP_H


#include "GL/glew.h"
#include "../GlFramebuffer.h"

class Cubemap {
public:
    Texture *texture;
    GlFramebuffer *fbs[6];

    Cubemap(int width, int height, bool useDepthBuffer, GLint internalformat, GLenum format);
    Cubemap(int width, int height, bool useDepthBuffer);

    ~Cubemap();
};


#endif //SPACEGAME_CUBEMAP_H
