//
// Created by dacma on 5/1/2024.
//

#include "FreeFlyGameEngine.h"

void FreeFlyGameEngine::tick() {
    // logic for a free flying camera, no game logic happening otherwise
    glm::vec3 camZ = -state->camera.dir;
    glm::vec3 camX = glm::normalize(glm::cross(state->camera.up, camZ));
    glm::vec3 camY = glm::cross(camZ, camX);
    state->camera.pos += camSpeed * controls->lStick.x * camX;
    state->camera.pos -= camSpeed * controls->lStick.y * camZ;
    if (controls->button1Down) {
        state->camera.pos += camSpeed * state->camera.up;
    }
    if (controls->button2Down) {
        state->camera.pos -= camSpeed * state->camera.up;
    }
    if (controls->button3Down) {
        float adjustedCenterDist = (glm::length(state->camera.pos - SCALE_POS) - SCALE_BORDER_RADIUS) / SCALE_MULT + SCALE_BORDER_RADIUS;
        state->camera.pos = glm::normalize(state->camera.pos - SCALE_POS) * adjustedCenterDist + SCALE_POS;
        camSpeed /= SCALE_MULT;
    }
    if (controls->button4Down) {
        float adjustedCenterDist = (glm::length(state->camera.pos - SCALE_POS) - SCALE_BORDER_RADIUS) * SCALE_MULT + SCALE_BORDER_RADIUS;
        state->camera.pos = glm::normalize(state->camera.pos - SCALE_POS) * adjustedCenterDist + SCALE_POS;
        camSpeed *= SCALE_MULT;
    }
    state->camera.dir = glm::rotate(glm::mat4(1.0f), -camRotSpeed * controls->rStick.x, camY) * glm::vec4(state->camera.dir, 0.0f);
    state->camera.dir = glm::rotate(glm::mat4(1.0f), camRotSpeed * controls->rStick.y, camX) * glm::vec4(state->camera.dir, 0.0f);
    if (ORIENT_TO_PLANET) {
        state->camera.up = glm::normalize(state->camera.pos - SCALE_POS);
    }
}

FreeFlyGameEngine::FreeFlyGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {
    camSpeed = 0.01f;
    camRotSpeed = 0.002f;
}
