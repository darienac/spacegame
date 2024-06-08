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
        BASIC_MODEL
    };

    struct ModelRenderData {
        GameState::ModelState *modelState;
        Model *model;
    };

    struct RenderTask {
        RenderTaskType type;
        bool usesTransparency;
        glm::dvec3 pos;
        union {
            GameState::Planet *planet;
            GameState::Star *star;
            ModelRenderData modelRenderData;
        };
    };

    GameState* state;
    ResourceCache* cache;
    Camera camera;
    std::vector<RenderTask> renderTasks;

    void updateCamera();

    void drawPlanet(GameState::Planet &planet);
    void drawPlanetAtmosphere(GameState::Planet &planet);
    void drawPlanetHeightmap(GameState::Planet &planet);
    void drawStar(GameState::Star &star);
    void drawModel(ModelRenderData &renderData);

    void doRenderTasks();
    void runRenderTask(RenderTask &task);
public:
    GameRenderer(GameState* state, ResourceCache* cache);

    void drawScene();
    void debugViewTexture(const Texture &texture);
};


#endif //CS455GAME_GAMERENDERER_H
