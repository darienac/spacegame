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
private:ShaderPerlin *perlinShader;

    static glm::mat4 getModelTransformMatrix(glm::vec3 pos, float scale);

    void updatePlanetToLOD(GameState *state, GameState::Planet *planet);
    void updateStarToLOD(GameState *state, GameState::Star *star);
    void syncPlanetsToState(GameState *state);
    void syncStarsToState(GameState *state);

    Mesh* getPlanetLODMesh(GameState::Planet_LOD lod);
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
        Heightmap *planetHeightmap;
        std::unique_ptr<Heightmap> heightmapAtmosphere;
        std::unique_ptr<Heightmap> heightmapGround;
        std::unique_ptr<Heightmap> heightmapGround2;
        Mesh* mesh;
    };
    struct StarData {
        GameState::Planet_LOD lod;
        glm::mat4 modelTransform;
        std::unique_ptr<Material> material;
        std::unique_ptr<UniformBlock> matBlock;
        Mesh* mesh;
    };

    std::map<boost::uuids::uuid, std::unique_ptr<PlanetData>> planetResources;
    std::map<boost::uuids::uuid, std::unique_ptr<StarData>> starResources;
    std::unique_ptr<UniformBlock> lightBlock;

    std::unique_ptr<UniformBlock> debugMatBlock1;
    std::unique_ptr<UniformBlock> debugMatBlock2;

    std::unique_ptr<Cubemap> cameraCubemap;
    std::unique_ptr<Cubemap> blackCubemap;
    std::unique_ptr<Cubemap> shipReflectionMap;
    std::unique_ptr<Model> orb_2;
    std::unique_ptr<Model> orb_3;
    std::unique_ptr<Model> orb_4;
    std::unique_ptr<Model> orb_5;
    std::unique_ptr<Model> skybox;
    std::unique_ptr<Model> testBox;

    explicit StateRenderCache(ShaderPerlin *perlinShader);

    void syncToState(GameState *state);
};


#endif //SPACEGAME_STATERENDERCACHE_H
