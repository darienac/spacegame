//
// Created by dacma on 5/14/2024.
//

#ifndef SPACEGAME_STATERENDERCACHE_H
#define SPACEGAME_STATERENDERCACHE_H


#include <map>
#include "boost/uuid/uuid.hpp"
#include "shader/UniformBlock.h"
#include "../game/state/GameState.h"
#include "model/Model.h"
#include "model/Cubemap.h"
#include "shader/IPerlinRenderer.h"

class StateRenderCache {
private:
    IPerlinRenderer *perlinRenderer;
public:
    struct PlanetData {
        Material *surfaceMat;
        Material *liquidMat;
        UniformBlock *matBlock;
        Cubemap *planetSurfaceMap;
    };

    std::map<boost::uuids::uuid, PlanetData*> planetResources;

    Cubemap *cameraCubemap;
    Model *blueOrb;
    Model *skybox;

    StateRenderCache(IPerlinRenderer *perlinRenderer);

    void syncToState(GameState *state);

    ~StateRenderCache();
};


#endif //SPACEGAME_STATERENDERCACHE_H
