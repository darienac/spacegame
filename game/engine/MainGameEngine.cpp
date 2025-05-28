//
// Created by dacma on 6/7/2024.
//

#include <iostream>
#include "MainGameEngine.h"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"

MainGameEngine::MainGameEngine(GameState *state, Controls *controls): state(state), controls(controls),
                                                                      physicsSimulator(state) {}

void MainGameEngine::tick() {
    if (controls->arrowLeftPressed && state->debug.layer > 0) {
        state->debug.layer--;
    }
    if (controls->arrowRightPressed) {
        state->debug.layer++;
    }
    updateShip(*controls, state->ship);
    fixCamera(state->camera, *controls, state->ship);
    updateLODs(*state);
    if (tickNum % 1 == 0) {
//        physicsSimulator.tick();
    }
    tickNum++;
}

void MainGameEngine::fixCamera(GameState::CameraState &camera, Controls &controls, GameState::ShipState &ship) {
    auto pi = glm::pi<double>();

    glm::dvec3 desiredDir = ship.modelState.dir;
    desiredDir = glm::rotate(glm::dmat4(1.0), controls.cameraPanDir.x * (pi * 0.5), ship.modelState.up) * glm::dvec4(desiredDir, 0.0);
    glm::dvec3 right = glm::normalize(glm::cross(desiredDir, camera.up));
    desiredDir = glm::rotate(glm::dmat4(1.0), controls.cameraPanDir.y * (pi * -0.25f), right) * glm::dvec4(desiredDir, 0.0);
    if (controls.reverseCamera) {
        desiredDir = glm::reflect(desiredDir, ship.modelState.dir);
    }

    if (glm::dot(desiredDir, camera.dir) < 0.2) {
        camera.dir = desiredDir;
    } else {
        camera.dir = glm::normalize(glm::normalize(desiredDir) * 0.02 + camera.dir);
    }
    camera.pos = ship.modelState.pos + ship.modelState.up * 1.5 - 8.0 * camera.dir;
    camera.up = ship.modelState.up;
}

void MainGameEngine::updateShip(Controls &controls, GameState::ShipState &ship) {
    // Dampen Rotate Velocities
    ship.turnVel *= 0.95;
    ship.rollVel *= 0.99;

    // Update direction
    if (controls.engageRoll) {
        ship.rollVel += controls.shipTurnDir.x * 0.0001f;
    } else {
        ship.turnVel += controls.shipTurnDir * 0.00015f;
    }
    // Roll
    glm::dvec3 newUp = ship.modelState.up;
    newUp = glm::rotate(glm::dmat4(1.0), ship.rollVel, ship.modelState.dir) * glm::dvec4(newUp, 0.0);
    ship.modelState.up = newUp;

    // Turn
    glm::dvec3 newDir = ship.modelState.dir;
    newDir = glm::rotate(glm::dmat4(1.0), -ship.turnVel.x, ship.modelState.up) * glm::dvec4(newDir, 0.0);
    glm::dvec3 right = glm::normalize(glm::cross(newDir, ship.modelState.up));
    newDir = glm::rotate(glm::dmat4(1.0), ship.turnVel.y, right) * glm::dvec4(newDir, 0.0);

    // update velocity into turn
    newDir = glm::normalize(newDir);
    double speedRedirected = glm::clamp(glm::dot(ship.modelState.dir, ship.vel), 0.0, 2.0);
    ship.vel -= ship.modelState.dir * speedRedirected;
    ship.vel += newDir * speedRedirected;
    ship.modelState.dir = newDir;
    ship.modelState.up = glm::normalize(glm::cross(right, newDir));
//    std::cout << "Velocity: " << glm::length(ship.vel) << std::endl;


    // Update position
    if (controls.boosterPower > 0.0f) {
        ship.boosterState = controls.engageTurbo ? GameState::BOOSTER_TURBO : GameState::BOOSTER_ON;
        ship.boosterStrength = controls.boosterPower;
    } else {
        ship.boosterState = GameState::BOOSTER_OFF;
        ship.boosterStrength = 0.0;
    }
    if (ship.boosterState != GameState::BOOSTER_OFF) {
        double moveSpeed = ship.boosterStrength * ((ship.boosterState == GameState::BOOSTER_TURBO) ? 0.001 : 0.0001);
        ship.vel += ship.modelState.dir * moveSpeed;
    }
    if (controls.backBoosterPower > 0.0f) {
        ship.vel *= 1.0 - controls.backBoosterPower * 0.005f;
    }
    ship.modelState.pos += ship.vel;
}
