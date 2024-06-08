//
// Created by dacma on 6/7/2024.
//

#include <iostream>
#include "MainGameEngine.h"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"

MainGameEngine::MainGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {

}

void MainGameEngine::tick() {
    updateShip(*controls, state->ship);
    fixCamera(state->camera, *controls, state->ship);
    updateLODs(*state);
}

void MainGameEngine::fixCamera(GameState::CameraState &camera, Controls &controls, GameState::ShipState &ship) {
    auto pi = glm::pi<float>();

    glm::vec3 desiredDir = ship.modelState.dir;
    desiredDir = glm::rotate(glm::mat4(1.0f), controls.cameraPanDir.x * (pi * 0.5f), ship.modelState.up) * glm::vec4(desiredDir, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(desiredDir, camera.up));
    desiredDir = glm::rotate(glm::mat4(1.0f), controls.cameraPanDir.y * (pi * -0.25f), right) * glm::vec4(desiredDir, 0.0f);

    camera.dir = glm::normalize(glm::normalize(desiredDir) * 0.02f + camera.dir);
    camera.pos = ship.modelState.pos + ship.modelState.up * 1.5f - 8.0f * camera.dir;
    camera.up = ship.modelState.up;
}

void MainGameEngine::updateShip(Controls &controls, GameState::ShipState &ship) {
    // Dampen Rotate Velocities
    ship.turnVel *= 0.95f;
    ship.rollVel *= 0.99f;

    // Update direction
    if (controls.engageRoll) {
        ship.rollVel += controls.shipTurnDir.x * 0.0001f;
    } else {
        ship.turnVel += controls.shipTurnDir * -0.00015f;
    }
    // Roll
    glm::vec3 newUp = ship.modelState.up;
    newUp = glm::rotate(glm::mat4(1.0f), ship.rollVel, ship.modelState.dir) * glm::vec4(newUp, 0.0f);
    ship.modelState.up = newUp;

    // Turn
    glm::vec3 newDir = ship.modelState.dir;
    newDir = glm::rotate(glm::mat4(1.0f), -ship.turnVel.x, ship.modelState.up) * glm::vec4(newDir, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(newDir, ship.modelState.up));
    newDir = glm::rotate(glm::mat4(1.0f), ship.turnVel.y, right) * glm::vec4(newDir, 0.0f);
    ship.modelState.dir = glm::normalize(newDir);
    ship.modelState.up = glm::normalize(glm::cross(right, newDir));


    // Update position
    if (controls.boosterPower > 0.0f) {
        ship.boosterState = controls.engageTurbo ? GameState::BOOSTER_TURBO : GameState::BOOSTER_ON;
        ship.boosterStrength = controls.boosterPower;
    } else {
        ship.boosterState = GameState::BOOSTER_OFF;
        ship.boosterStrength = 0.0f;
    }
    if (ship.boosterState != GameState::BOOSTER_OFF) {
        float moveSpeed = ship.boosterStrength * ((ship.boosterState == GameState::BOOSTER_TURBO) ? 0.01f : 0.0001f);
        ship.vel += ship.modelState.dir * moveSpeed;
    }
    if (controls.backBoosterPower > 0.0f) {
        ship.vel *= 1.0f - controls.backBoosterPower * 0.005f;
    }
    ship.modelState.pos += ship.vel;
}
