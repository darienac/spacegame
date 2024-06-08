//
// Created by dacma on 3/19/2024.
//

#include <iostream>
#include "Controls.h"
#include "glm/geometric.hpp"

static Controls* controlsRef;
const float Controls::STICK_DEADZONE = 0.15f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    bool value = (action == GLFW_PRESS);
    if (action == GLFW_REPEAT) {
        return;
    }
    switch(key) {
        case GLFW_KEY_A:
            controlsRef->left = value;
            break;
        case GLFW_KEY_D:
            controlsRef->right = value;
            break;
        case GLFW_KEY_W:
            controlsRef->up = value;
            break;
        case GLFW_KEY_S:
            controlsRef->down = value;
            break;
        case GLFW_KEY_LEFT:
            controlsRef->arrowLeft = value;
            break;
        case GLFW_KEY_RIGHT:
            controlsRef->arrowRight = value;
            break;
        case GLFW_KEY_UP:
            controlsRef->arrowUp = value;
            break;
        case GLFW_KEY_DOWN:
            controlsRef->arrowDown = value;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            controlsRef->debugFallButtonDown = value;
            controlsRef->engageTurbo = value;
            break;
        case GLFW_KEY_SPACE:
            controlsRef->debugRiseButtonDown = value;
            controlsRef->boosterPower = value ? 1.0f : 0.0f;
            break;
        case GLFW_KEY_F11:
            if (value) {
                controlsRef->fullscreenPressed = true;
            }
            break;
        case GLFW_KEY_Q:
            controlsRef->debugApproachButtonDown = value;
            break;
        case GLFW_KEY_E:
            controlsRef->debugDivergeButtonDown = value;
            break;
        case GLFW_KEY_R:
            controlsRef->engageRoll = value;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            controlsRef->backBoosterPower = value ? 1.0f : 0.0f;
        case GLFW_KEY_GRAVE_ACCENT:
            controlsRef->enableDebugEngine = value ^ controlsRef->enableDebugEngine;
        default:
            break;
    }
    controlsRef->debugFlyXZDir = {controlsRef->right - controlsRef->left, controlsRef->up - controlsRef->down};
    controlsRef->debugPanCameraDir = {controlsRef->arrowRight - controlsRef->arrowLeft, controlsRef->arrowUp - controlsRef->arrowDown};
    if (glm::length(controlsRef->debugFlyXZDir) > 1.0f) {
        controlsRef->debugFlyXZDir = glm::normalize(controlsRef->debugFlyXZDir);
    }
    if (glm::length(controlsRef->debugPanCameraDir) > 1.0f) {
        controlsRef->debugPanCameraDir = glm::normalize(controlsRef->debugPanCameraDir);
    }
    controlsRef->cameraPanDir = controlsRef->debugPanCameraDir;
}

bool Controls::isGamepadButtonUpdated(const GLFWgamepadstate &state, int button) {
    return state.buttons[button] != lastGamepadState.buttons[button];
}

bool Controls::isGamepadButtonPressed(const GLFWgamepadstate &state, int button) {
    return state.buttons[button] == GLFW_PRESS;
}

bool Controls::isGamepadAxisUpdated(const GLFWgamepadstate &state, int axis) {
    return state.axes[axis] != lastGamepadState.axes[axis];
}

Controls::Controls(GlWindow *window) {
    controlsRef = this;
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwGetGamepadState(0, &lastGamepadState);
}

void Controls::pollGamepadInputs(int jid) {
    GLFWgamepadstate state;
    if (!glfwJoystickIsGamepad(jid) || !glfwGetGamepadState(jid, &state)) {
        return;
    }

    if (isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_LEFT_X) || isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_LEFT_Y)) {
        glm::vec2 stickPos = {state.axes[GLFW_GAMEPAD_AXIS_LEFT_X], -state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]};
        if (!(glm::length(stickPos) < STICK_DEADZONE && glm::length(debugFlyXZDir) < STICK_DEADZONE)) {
            debugFlyXZDir = stickPos;
            if (glm::length(debugFlyXZDir) > 1.0f) {
                debugFlyXZDir = glm::normalize(debugFlyXZDir);
            } else if (glm::length(debugFlyXZDir) < STICK_DEADZONE) {
                debugFlyXZDir = {0.0f, 0.0f};
            }
        }
    }
    if (isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_RIGHT_X) || isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_RIGHT_Y)) {
        glm::vec2 stickPos = {state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]};
        if (!(glm::length(stickPos) < STICK_DEADZONE && glm::length(debugPanCameraDir) < STICK_DEADZONE)) {
            debugPanCameraDir = stickPos;
            if (glm::length(debugPanCameraDir) > 1.0f) {
                debugPanCameraDir = glm::normalize(debugPanCameraDir);
            } else if (glm::length(debugPanCameraDir) < STICK_DEADZONE) {
                debugPanCameraDir = {0.0f, 0.0f};
            }
        }
    }
    if (isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER)) {
        boosterPower = (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] + 1.0f) * 0.5f;
    }
    if (isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_LEFT_TRIGGER)) {
        backBoosterPower = (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] + 1.0f) * 0.5f;
    }
    cameraPanDir = debugPanCameraDir;
    shipTurnDir = debugFlyXZDir;
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_A)) {
        debugRiseButtonDown = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_A);
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_B)) {
        debugFallButtonDown = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_B);
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_X)) {
        debugApproachButtonDown = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_X);
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_Y)) {
        debugDivergeButtonDown = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_Y);
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER)) {
        engageTurbo = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER);
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER)) {
        engageRoll = isGamepadButtonPressed(state, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER);
    }

    lastGamepadState = state;
}
