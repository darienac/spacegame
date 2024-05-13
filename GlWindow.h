//
// Created by dacma on 2/20/2024.
//

#ifndef CS455GAME_GLWINDOW_H
#define CS455GAME_GLWINDOW_H


#include <string>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

class GlWindow {
private:
    GLFWwindow* window;
    bool fullscreen;
    int oldWindowX, oldWindowY, oldWindowW, oldWindowH;
    bool resized;
    int width, height;
public:
    GlWindow(const std::string& name, int width, int height);
    void exitWindow();
    void enableFullscreen();
    void disableFullscreen();
    void setResized(bool value);

    bool isFullscreen() const;
    GLFWwindow* getWindow() const;

    int getWidth() const;
    int getHeight() const;
    bool isResized() const;

    ~GlWindow();
};


#endif //CS455GAME_GLWINDOW_H
