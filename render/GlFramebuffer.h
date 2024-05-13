//
// Created by dacma on 4/2/2024.
//

#ifndef CS455GAME_GLFRAMEBUFFER_H
#define CS455GAME_GLFRAMEBUFFER_H


#include <vector>
#include "GL/glew.h"
#include "model/Texture.h"

class GlFramebuffer {
protected:
    static GlFramebuffer* currentFramebuffer;

    bool useDepthBuffer;
    GLsizei width;
    GLsizei height;
    GLuint depthBufferId;
    GLuint framebufferId;
    std::vector<Texture*> textures;

public:
    static GlFramebuffer* getCurrentFramebuffer();

    GlFramebuffer(std::vector<Texture*> textures, bool useDepthBuffer);
    GlFramebuffer(GLsizei width, GLsizei height);
    GlFramebuffer();

    void resize(GLsizei width, GLsizei height);

    void bind(GLenum target);
    virtual void bind();

    GLuint getFramebufferId() const;
    GLsizei getWidth() const;
    GLsizei getHeight() const;
    std::vector<Texture*>& getTextures();
    void copyToFramebuffer(GlFramebuffer* fbCopy);

    virtual ~GlFramebuffer();
};


#endif //CS455GAME_GLFRAMEBUFFER_H
