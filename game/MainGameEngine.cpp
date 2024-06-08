//
// Created by dacma on 6/7/2024.
//

#include "MainGameEngine.h"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"

MainGameEngine::MainGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {

}

void MainGameEngine::tick() {
    fixCamera(state->camera, *controls, state->ship);
    updateLODs(*state);
}

void MainGameEngine::fixCamera(GameState::CameraState &camera, Controls &controls, GameState::ShipState &ship) {
    auto pi = glm::pi<float>();

    glm::vec3 desiredDir = ship.modelState.dir;
    desiredDir = glm::rotate(glm::mat4(1.0f), controls.cameraPanDir.x * (pi * 0.5f), ship.modelState.up) * glm::vec4(desiredDir, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(desiredDir, camera.up));
    desiredDir = glm::rotate(glm::mat4(1.0f), controls.cameraPanDir.y * (pi * -0.5f), right) * glm::vec4(desiredDir, 0.0f);

    camera.dir = glm::normalize(glm::normalize(desiredDir) * 0.02f + camera.dir);
    camera.pos = ship.modelState.pos + ship.modelState.up * 1.5f - 8.0f * camera.dir;
}
