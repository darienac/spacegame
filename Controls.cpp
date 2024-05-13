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
            controlsRef->lShiftDown = value;
            break;
        case GLFW_KEY_SPACE:
            controlsRef->spaceDown = value;
            break;
        case GLFW_KEY_F11:
            if (value) {
                controlsRef->fullscreenPressed = true;
            }
            break;
        default:
            break;
    }
    controlsRef->lStick = {controlsRef->right - controlsRef->left, controlsRef->up - controlsRef->down};
    controlsRef->rStick = {controlsRef->arrowRight - controlsRef->arrowLeft, controlsRef->arrowUp - controlsRef->arrowDown};
    if (glm::length(controlsRef->lStick) > 1.0f) {
        controlsRef->lStick = glm::normalize(controlsRef->lStick);
    }
    if (glm::length(controlsRef->rStick) > 1.0f) {
        controlsRef->rStick = glm::normalize(controlsRef->rStick);
    }
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
        if (!(glm::length(stickPos) < STICK_DEADZONE && glm::length(lStick) < STICK_DEADZONE)) {
            lStick = stickPos;
            if (glm::length(lStick) > 1.0f) {
                lStick = glm::normalize(lStick);
            } else if (glm::length(lStick) < STICK_DEADZONE) {
                lStick = {0.0f, 0.0f};
            }
        }
    }
    if (isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_RIGHT_X) || isGamepadAxisUpdated(state, GLFW_GAMEPAD_AXIS_RIGHT_Y)) {
        glm::vec2 stickPos = {state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], -state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]};
        if (!(glm::length(stickPos) < STICK_DEADZONE && glm::length(rStick) < STICK_DEADZONE)) {
            rStick = stickPos;
            if (glm::length(rStick) > 1.0f) {
                rStick = glm::normalize(rStick);
            } else if (glm::length(rStick) < STICK_DEADZONE) {
                rStick = {0.0f, 0.0f};
            }
        }
    }
    if (isGamepadButtonUpdated(state, GLFW_GAMEPAD_BUTTON_A)) {

    }

    lastGamepadState = state;
}
