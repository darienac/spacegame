//
// Created by dacma on 4/2/2024.
//

#include "GlScreenBuffer.h"

GlScreenBuffer::GlScreenBuffer(GLFWwindow *window): window(window) {
    glfwGetFramebufferSize(window, &width, &height);
    framebufferId = 0;
}

void GlScreenBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    currentFramebuffer = this;
}
