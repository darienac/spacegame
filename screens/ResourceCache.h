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
#include "boost/uuid/uuid.hpp"
#include "../game/state/GameState.h"
#include "../render/shader/UniformBlock.h"
#include "../render/StateRenderCache.h"

class ResourceCache {
private:
    typedef std::vector<std::string> srcs;
public:
    std::unique_ptr<Shader3D> skyboxShader;
    std::unique_ptr<Shader3D> sceneShader;
    std::unique_ptr<Shader3D> atmosphereShader;
    std::unique_ptr<Shader3D> heightmapShader;
    std::unique_ptr<Shader3D> planetShader;
    std::unique_ptr<Shader2D> shader2D;
    std::unique_ptr<ShaderPerlin> perlinShader;
    std::unique_ptr<ShaderPerlin> spaceShader;

    std::unique_ptr<Model> shipModel;

    std::unique_ptr<Texture> testTexture;

    GlWindow *window;
    std::unique_ptr<Controls> controls;
    std::unique_ptr<GlScreenBuffer> screenBuffer;

    std::unique_ptr<StateRenderCache> stateRenderCache;

    explicit ResourceCache(GlWindow* window);
};


#endif //SPACEGAME_RESOURCECACHE_H
