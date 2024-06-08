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
    // Generic
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool arrowLeft = false;
    bool arrowRight = false;
    bool arrowUp = false;
    bool arrowDown = false;

    bool fullscreenPressed = false;
    bool enableDebugEngine = false;

    // Debug Engine
    bool debugRiseButtonDown = false;
    bool debugFallButtonDown = false;
    bool debugApproachButtonDown = false;
    bool debugDivergeButtonDown = false;

    glm::vec2 debugFlyXZDir = {0.0f, 0.0f};
    glm::vec2 debugPanCameraDir = {0.0f, 0.0f};

    // Main Engine
    glm::vec2 cameraPanDir = {0.0f, 0.0f};

    GLFWgamepadstate lastGamepadState;

    Controls(GlWindow* window);

    void pollGamepadInputs(int jid);
};


#endif //CS455GAME_CONTROLS_H
