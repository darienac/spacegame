//
// Created by dacma on 5/14/2024.
//

#ifndef SPACEGAME_SHADERPLANET_H
#define SPACEGAME_SHADERPLANET_H


#include "Shader3D.h"
#include "../../game/state/GameState.h"
#include "../StateRenderCache.h"

class ShaderPlanet: public Shader3D {
private:
    GLuint ubPlanetProps;
public:
    ShaderPlanet(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader);

    void drawPlanet(GameState::Planet &planet, StateRenderCache *cache);
};


#endif //SPACEGAME_SHADERPLANET_H
