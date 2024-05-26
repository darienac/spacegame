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
    GameState* state;
    Shader3D* shader3D;
    Shader2D* shader2D;
    ResourceCache* cache;
    Camera camera;

    void updateCamera();

    void drawPlanet(GameState::Planet &planet);
    void drawPlanetAtmosphere(GameState::Planet &planet);
    void drawStar(GameState::Star &star);
public:
    GameRenderer(GameState* state, ResourceCache* cache);

    void drawScene();
};


#endif //CS455GAME_GAMERENDERER_H
