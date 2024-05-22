//
// Created by dacma on 3/19/2024.
//

#ifndef CS455GAME_CONTROLS_H
#define CS455GAME_CONTROLS_H


#include "GlWindow.h"
#include "glm/vec2.hpp"

class Controls {
private:
    static const float STICK_DEADZONE;

    bool isGamepadButtonUpdated(const GLFWgamepadstate& state, int button);
    bool isGamepadButtonPressed(const GLFWgamepadstate& state, int button);
    bool isGamepadAxisUpdated(const GLFWgamepadstate& state, int axis);
public:
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool arrowLeft = false;
    bool arrowRight = false;
    bool arrowUp = false;
    bool arrowDown = false;
    bool button1Down = false;
    bool button2Down = false;
    bool button3Down = false;
    bool button4Down = false;
    bool fullscreenPressed = false;

    GLFWgamepadstate lastGamepadState;
    glm::vec2 lStick = {0.0f, 0.0f};
    glm::vec2 rStick = {0.0f, 0.0f};

    Controls(GlWindow* window);

    void pollGamepadInputs(int jid);
};


#endif //CS455GAME_CONTROLS_H
