//
// Created by dacma on 5/14/2024.
//

#ifndef SPACEGAME_STATERENDERCACHE_H
#define SPACEGAME_STATERENDERCACHE_H


#include <map>
#include "glm/ext/matrix_float4x4.hpp"
#include "boost/uuid/uuid.hpp"
#include "shader/UniformBlock.h"
#include "../game/state/GameState.h"
#include "model/Model.h"
#include "model/Cubemap.h"
#include "shader/IPerlinRenderer.h"

class StateRenderCache {
private:
    IPerlinRenderer *perlinRenderer;

    static glm::mat4 getModelTransformMatrix(glm::vec3 pos, float scale);

    void syncPlanetsToState(GameState *state);
    void syncStarsToState(GameState *state);
public:
    struct PlanetData {
        GameState::Planet_LOD lod;
        glm::mat4 modelTransform;
        Material *surfaceMat;
        Material *liquidMat;
        UniformBlock *matBlock;
        UniformBlock *planetDataBlock;
        Cubemap *planetSurfaceMap;
    };
    struct StarData {
        GameState::Planet_LOD lod;
        glm::mat4 modelTransform;
        Material *material;
        UniformBlock *matBlock;
    };

    std::map<boost::uuids::uuid, PlanetData*> planetResources;
    std::map<boost::uuids::uuid, StarData*> starResources;
    UniformBlock *lightBlock;

    Cubemap *cameraCubemap;
    Model *blueOrb;
    Model *skybox;

    StateRenderCache(IPerlinRenderer *perlinRenderer);

    void syncToState(GameState *state);

    ~StateRenderCache();
};


#endif //SPACEGAME_STATERENDERCACHE_H
