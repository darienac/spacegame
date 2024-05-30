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
#include "shader/ShaderPerlin.h"
#include "model/Heightmap.h"

class StateRenderCache {
private:
    static inline const float HMAP_UPDATE_THRESHOLD = 0.999f;

    ShaderPerlin *perlinShader;

    static glm::mat4 getModelTransformMatrix(glm::vec3 pos, float scale);

    void syncPlanetsToState(GameState *state);
    void syncStarsToState(GameState *state);

    Mesh* getPlanetMesh(GameState::Planet &planet);
public:
    struct PlanetData {
        GameState::Planet_LOD lod;
        glm::mat4 modelTransform;
        glm::mat4 atmosphereModelTransform;
        glm::mat4 heightmapModelTransform;
        std::unique_ptr<Material> surfaceMat;
        std::unique_ptr<Material> liquidMat;
        std::unique_ptr<UniformBlock> matBlock;
        std::unique_ptr<UniformBlock> planetDataBlock;
        std::unique_ptr<Cubemap> planetSurfaceMap;
        std::unique_ptr<Heightmap> planetHeightmap;
        Mesh* mesh;
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

    explicit StateRenderCache(ShaderPerlin *perlinShader);

    void syncToState(GameState *state);
};


#endif //SPACEGAME_STATERENDERCACHE_H
