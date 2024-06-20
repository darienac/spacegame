//
// Created by dacma on 6/19/2024.
//

#include <iostream>
#include "PhysicsSimulator.h"
#include "glm/ext/matrix_transform.hpp"

glm::dmat4 PhysicsSimulator::getModelTransform(const GameState::ModelState &modelState) {
    return glm::translate(glm::dmat4(1.0), modelState.pos) * glm::inverse(glm::lookAt({0.0, 0.0, 0.0}, modelState.dir, modelState.up)) * glm::scale(glm::dmat4(1.0), modelState.scale);
}

PhysicsSimulator::PhysicsSimulator(GameState *state): state(state) {
    shipMesh = std::make_unique<GameMesh>("spaceship.obj");
    islandMesh = std::make_unique<GameMesh>("wuhu.obj");
    state->debug.shipMesh = shipMesh.get();
    state->debug.islandMesh = islandMesh.get();
}

void PhysicsSimulator::tick() {
    state->debug.objectsCollide = AbstractCollider::collide(shipMesh->getBoundingBox(), getModelTransform(state->ship.modelState), islandMesh->getBoundingBox(), getModelTransform(state->island));
}
