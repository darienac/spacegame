//
// Created by dacma on 5/1/2024.
//

#include <iostream>
#include "FreeFlyGameEngine.h"
#include "../GlobalFlags.h"

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

//    for (auto &pair : state->planets) {
//        updatePlanetLOD(*state, *pair.second);
//    }
    updatePlanetLOD(*state, state->planet);
}

FreeFlyGameEngine::FreeFlyGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {
    camSpeed = 0.01f;
    camRotSpeed = 0.002f;
}

void FreeFlyGameEngine::updatePlanetLOD(GameState &state, GameState::Planet &planet) {
    float radius = planet.radius;
    float closeness = glm::distance(state.camera.pos, planet.position) / radius;
    if (GlobalFlags::DEBUG && GlobalFlags::TRACK_LOD) {
        std::cout << "LOD: " << planet.lod << " CLOSENESS: " << closeness << std::endl;
    }
    if (closeness > 50.0f) {
        planet.lod = GameState::BILLBOARD;
        return;
    }
    if (closeness > 10.0f) {
        planet.lod = GameState::DISTANT;
        return;
    }
    if (closeness > 3.0f) {
        planet.lod = GameState::NEAR;
        return;
    }
    if (closeness > 1.14f) {
        planet.lod = GameState::ATMOSPHERE;
        return;
    }
    if (closeness > 1.015f) {
        planet.lod = GameState::GROUND;
        return;
    }
    planet.lod = GameState::GROUND2;
}
