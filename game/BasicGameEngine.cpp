//
// Created by dacma on 6/7/2024.
//

#include <iostream>
#include "BasicGameEngine.h"
#include "glm/geometric.hpp"
#include "../GlobalFlags.h"

void BasicGameEngine::updatePlanetLOD(GameState &state, GameState::Planet &planet) {
    double radius = planet.radius;
    double closeness = glm::distance(state.camera.pos, planet.position) / radius;
    if (GlobalFlags::DEBUG && GlobalFlags::TRACK_LOD && &planet == &state.planet) {
        std::cout << "LOD: " << planet.lod << " CLOSENESS: " << closeness << std::endl;
    }
    if (closeness > 50.0f) {
        planet.lod = GameState::DISTANT2;
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

void BasicGameEngine::updateStarLOD(GameState &state, GameState::Star &star) {
    float radius = star.radius;
    float closeness = glm::distance(state.camera.pos, star.position) / radius;
    if (closeness > 50.0f) {
        star.lod = GameState::DISTANT2;
        return;
    }
    if (closeness > 10.0f) {
        star.lod = GameState::DISTANT;
        return;
    }
    star.lod = GameState::NEAR;
}

void BasicGameEngine::updateLODs(GameState &state) {
    for (auto &pair : state.planets) {
        updatePlanetLOD(state, *pair.second);
    }
    for (auto &pair : state.stars) {
        updateStarLOD(state, *pair.second);
    }
}
