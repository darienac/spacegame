//
// Created by dacma on 6/19/2024.
//

#ifndef SPACEGAME_PHYSICSSIMULATOR_H
#define SPACEGAME_PHYSICSSIMULATOR_H


#include <memory>
#include "../../state/GameState.h"
#include "../../collision/GameMesh.h"

class PhysicsSimulator {
private:
    GameState *state;

    std::unique_ptr<MeshCollider> shipMesh;
    std::unique_ptr<MeshCollider> islandMesh;

    static glm::dmat4 getModelTransform(const GameState::ModelState &modelState);
public:
    explicit PhysicsSimulator(GameState* state);

    void tick();
};


#endif //SPACEGAME_PHYSICSSIMULATOR_H
