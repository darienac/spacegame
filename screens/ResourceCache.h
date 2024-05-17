//
// Created by dacma on 4/30/2024.
//

#ifndef SPACEGAME_RESOURCECACHE_H
#define SPACEGAME_RESOURCECACHE_H


#include <map>
#include "../Controls.h"
#include "../render/shader/Shader3D.h"
#include "../render/shader/Shader2D.h"
#include "../render/shader/ShaderPerlin.h"
#include "../render/GlScreenBuffer.h"
#include "../render/shader/ShaderPlanet.h"
#include "boost/uuid/uuid.hpp"
#include "../game/state/GameState.h"
#include "../render/shader/UniformBlock.h"
#include "../render/StateRenderCache.h"

class ResourceCache {
public:
    Shader3D *skyboxShader;
    Shader3D *sceneShader;
    ShaderPlanet *planetShader;
    Shader2D *shader2D;
    ShaderPerlin *perlinShader;
    ShaderPerlin *spaceShader;

    Controls *controls;
    GlWindow *window;
    GlScreenBuffer *screenBuffer;

    StateRenderCache *stateRenderCache;

    explicit ResourceCache(GlWindow* window);

    ~ResourceCache();
};


#endif //SPACEGAME_RESOURCECACHE_H
