//
// Created by dacma on 5/14/2024.
//

#ifndef SPACEGAME_STATERENDERCACHE_H
#define SPACEGAME_STATERENDERCACHE_H


#include <map>
#include "boost/uuid/uuid.hpp"
#include "shader/UniformBlock.h"
#include "../game/GameState.h"
#include "model/Model.h"
#include "model/Cubemap.h"

class StateRenderCache {
public:
    struct PlanetData {
        Material *surfaceMat;
        Material *liquidMat;
        UniformBlock *matBlock;
    };

    std::map<boost::uuids::uuid, PlanetData*> planetResources;

    Model *blueOrb;
    Model *skybox;
    Cubemap *cubemap;

    StateRenderCache();

    void syncToState(GameState *state);

    ~StateRenderCache();
};


#endif //SPACEGAME_STATERENDERCACHE_H
