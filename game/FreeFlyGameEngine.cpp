//
// Created by dacma on 5/1/2024.
//

#include "FreeFlyGameEngine.h"

float FreeFlyGameEngine::camSpeed = 0.01f;
float FreeFlyGameEngine::camRotSpeed = 0.002f;

void FreeFlyGameEngine::tick() {
    // logic for a free flying camera, no game logic happening otherwise
    glm::vec3 camZ = -state->camera.dir;
    glm::vec3 camX = glm::normalize(glm::cross(state->camera.up, camZ));
    glm::vec3 camY = glm::cross(camZ, camX);
    state->camera.pos += camSpeed * controls->lStick.x * camX;
    state->camera.pos -= camSpeed * controls->lStick.y * camZ;
    if (controls->spaceDown) {
        state->camera.pos += camSpeed * state->camera.up;
    }
    if (controls->lShiftDown) {
        state->camera.pos -= camSpeed * state->camera.up;
    }
    state->camera.dir = glm::rotate(glm::mat4(1.0f), -camRotSpeed * controls->rStick.x, camY) * glm::vec4(state->camera.dir, 0.0f);
    state->camera.dir = glm::rotate(glm::mat4(1.0f), camRotSpeed * controls->rStick.y, camX) * glm::vec4(state->camera.dir, 0.0f);
}

FreeFlyGameEngine::FreeFlyGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {

}
