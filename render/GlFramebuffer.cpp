//
// Created by dacma on 4/2/2024.
//

#include "GlFramebuffer.h"
#include "../GlobalFlags.h"

GlFramebuffer* GlFramebuffer::currentFramebuffer = nullptr;

GlFramebuffer *GlFramebuffer::getCurrentFramebuffer() {
    return currentFramebuffer;
}

GlFramebuffer::GlFramebuffer(std::vector<Texture *> textures, bool useDepthBuffer): textures(textures) {
    this->useDepthBuffer = useDepthBuffer;

    width = textures[0]->getWidth();
    height = textures[0]->getHeight();

    glGenFramebuffers(1, &framebufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

    if (useDepthBuffer) {
        glGenRenderbuffers(1, &depthBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
        if (textures[0]->usesMultisampling()) {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, width, height);
        } else {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        }
//        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
    }

    auto drawBuffers = new GLenum[textures.size()];
    for (int i = 0; i < textures.size(); i++) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textures[i]->usesMultisampling() ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, textures[i]->getTextureId(), 0);
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers(textures.size(), drawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Unable to create framebuffer");
    }
}

GlFramebuffer::GlFramebuffer(GLsizei width, GLsizei height) {
    framebufferId = 0;
    useDepthBuffer = false;
    this->width = width;
    this->height = height;
}

GlFramebuffer::GlFramebuffer(): GlFramebuffer(0, 0) {}

void GlFramebuffer::resize(GLsizei width, GLsizei height) {
    if (this->width == width && this->height == height) {
        return;
    }
    std::cout << "Framebuffer resize" << std::endl;
    this->width = width;
    this->height = height;
    bind();

    if (useDepthBuffer) {
        glDeleteRenderbuffers(1, &depthBufferId);
        glGenRenderbuffers(1, &depthBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
        if (textures[0]->usesMultisampling()) {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, width, height);
        } else {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        }
//        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
    }

    for (auto & texture : textures) {
        texture->resize(width, height);
    }
}

void GlFramebuffer::bind(GLenum target) {
    glBindFramebuffer(target, framebufferId);
    glViewport(0, 0, getWidth(), getHeight());
    if (target == GL_FRAMEBUFFER) {
        currentFramebuffer = this;
    }
}

void GlFramebuffer::bind() {
    bind(GL_FRAMEBUFFER);
}

GLuint GlFramebuffer::getFramebufferId() const {
    return framebufferId;
}

GLsizei GlFramebuffer::getWidth() const {
    return width;
}

GLsizei GlFramebuffer::getHeight() const {
    return height;
}

std::vector<Texture *> &GlFramebuffer::getTextures() {
    return textures;
}

void GlFramebuffer::copyToFramebuffer(GlFramebuffer *fbCopy) {
    fbCopy->bind();
    bind(GL_READ_FRAMEBUFFER);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

GlFramebuffer::~GlFramebuffer() {
    if (GlobalFlags::DEBUG) {
        std::cout << "Framebuffer destroyed" << std::endl;
    }

    glDeleteFramebuffers(1, &framebufferId);
    if (useDepthBuffer) {
        glDeleteRenderbuffers(1, &depthBufferId);
    }
}

