//
// Created by dacma on 4/2/2024.
//

#ifndef CS455GAME_GLSCREENBUFFER_H
#define CS455GAME_GLSCREENBUFFER_H


#include "GlFramebuffer.h"
#include "GLFW/glfw3.h"

class GlScreenBuffer: public GlFramebuffer {
private:
    GLFWwindow* window;
public:
    GlScreenBuffer(GLFWwindow* window);

    void bind() override;
};


#endif //CS455GAME_GLSCREENBUFFER_H
