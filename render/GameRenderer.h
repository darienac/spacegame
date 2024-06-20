//
// Created by dacma on 3/29/2024.
//

#ifndef CS455GAME_GAMERENDERER_H
#define CS455GAME_GAMERENDERER_H


#include "../game/state/GameState.h"
#include "Camera.h"
#include "shader/Shader3D.h"
#include "shader/Shader2D.h"
#include "../screens/ResourceCache.h"

class GameRenderer {
private:
    enum RenderTaskType {
        STAR,
        PLANET,
        PLANET_ATMOSPHERE,
        PLANET_HEIGHTMAP,
        BASIC_MODEL,
        SKYBOX
    };

    struct ModelRenderData {
        GameState::ModelState *modelState;
        Model *model;
        UniformBlock *matBlock = nullptr;
        Cubemap *cubemap = nullptr;
    };

    struct RenderTask {
        bool enabled = true;
        RenderTaskType type;
        bool usesTransparency = true;
        glm::dvec3 pos = {0.0, 0.0, 0.0};
        union {
            GameState::Planet *planet;
            GameState::Star *star;
            ModelRenderData modelRenderData;
            Cubemap *skybox;
        };
    };

    GameState* state;
    ResourceCache* cache;
    Camera camera;
    std::vector<RenderTask> renderTasks;

    static glm::dmat4 getModelTransform(const GameState::ModelState &modelState);

    void updateCamera();

    void drawPlanet(GameState::Planet &planet, Camera &renderCamera);
    void drawPlanetAtmosphere(GameState::Planet &planet, Camera &renderCamera);
    void drawPlanetHeightmap(GameState::Planet &planet, Camera &renderCamera);
    void drawStar(GameState::Star &star, Camera &renderCamera);
    void drawModel(ModelRenderData &renderData, Camera &renderCamera);
    void drawSkybox(Cubemap &cubemap, Camera &renderCamera);

    void addTestSphereTask(GameState::ModelState &modelState, bool useHighlight);
    void addTestBoxTask(GameState::ModelState &modelState, bool useHighlight);

    void runRenderTasks(Camera &renderCamera);
    void runRenderTask(RenderTask &task, Camera &renderCamera);
    void runRenderTasksOnCubemap(Cubemap &cubemap, glm::dvec3 &pos);
public:
    GameRenderer(GameState* state, ResourceCache* cache);

    void drawScene();
    void debugViewTexture(const Texture &texture);
};


#endif //CS455GAME_GAMERENDERER_H
