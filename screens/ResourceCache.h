//
// Created by dacma on 4/30/2024.
//

#ifndef SPACEGAME_RESOURCECACHE_H
#define SPACEGAME_RESOURCECACHE_H


#include "../Controls.h"
#include "../render/shader/Shader3D.h"
#include "../render/shader/Shader2D.h"
#include "../render/shader/ShaderPerlin.h"

class ResourceCache {
public:
    Shader3D *sceneShader;
    Shader3D *planetShader;
    Shader2D *shader2D;
    ShaderPerlin *perlinShader;

    Model *blueOrb;
    Environment basicEnv;

    Controls* controls;
    GlWindow* window;

    explicit ResourceCache(GlWindow* window);

    ~ResourceCache();
};


#endif //SPACEGAME_RESOURCECACHE_H
