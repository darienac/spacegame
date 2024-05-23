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
        std::unique_ptr<Material> surfaceMat;
        std::unique_ptr<Material> liquidMat;
        std::unique_ptr<UniformBlock> matBlock;
        std::unique_ptr<UniformBlock> planetDataBlock;
        std::unique_ptr<Cubemap> planetSurfaceMap;
    };
    struct StarData {
        GameState::Planet_LOD lod;
        glm::mat4 modelTransform;
        std::unique_ptr<Material> material;
        std::unique_ptr<UniformBlock> matBlock;
    };

    std::map<boost::uuids::uuid, std::unique_ptr<PlanetData>> planetResources;
    std::map<boost::uuids::uuid, std::unique_ptr<StarData>> starResources;
    std::unique_ptr<UniformBlock> lightBlock;

    std::unique_ptr<Cubemap> cameraCubemap;
    std::unique_ptr<Model> orb_2;
    std::unique_ptr<Model> orb_3;
    std::unique_ptr<Model> orb_4;
    std::unique_ptr<Model> orb_5;
    std::unique_ptr<Model> skybox;

    explicit StateRenderCache(IPerlinRenderer *perlinRenderer);

    void syncToState(GameState *state);
};


#endif //SPACEGAME_STATERENDERCACHE_H
