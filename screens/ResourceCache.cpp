//
// Created by dacma on 4/30/2024.
//

#include "ResourceCache.h"
#include "../GlobalFlags.h"

ResourceCache::ResourceCache(GlWindow *window): window(window) {
    controls = std::make_unique<Controls>(window);

    Shader2D::initBuffers();
    skyboxShader = std::make_unique<Shader3D>("v3D.glsl", "fSkybox3D.glsl");
    sceneShader = std::make_unique<Shader3D>(srcs{"v3D.glsl"}, srcs{Shader3D::GLSL_PHONG_SHADING, "f3D.glsl"});
    atmosphereShader = std::make_unique<Shader3D>(srcs{"v3D.glsl"}, srcs{Shader3D::GLSL_PHONG_SHADING, "shared/planetUB.glsl", "fAtmosphere3D.glsl"});
    heightmapShader = std::make_unique<Shader3D>(srcs{"shared/planetUB.glsl", "vHeightmap.glsl"}, srcs{Shader3D::GLSL_PHONG_SHADING, "shared/planetUB.glsl", "fHeightmap.glsl"});
    planetShader = std::make_unique<ShaderPlanet>(srcs{"v3D.glsl"}, srcs{Shader3D::GLSL_PHONG_SHADING, "shared/planetUB.glsl", "fPlanet3D.glsl"});
    shader2D = std::make_unique<Shader2D>(srcs{"v2D.glsl"}, srcs{"f2D.glsl"});
    perlinShader = std::make_unique<ShaderPerlin>(srcs{"vPerlin.glsl"}, srcs{Shader3D::GLSL_PERLIN, "fPerlin.glsl"});
    spaceShader = std::make_unique<ShaderPerlin>(srcs{"v2D.glsl"}, srcs{Shader3D::GLSL_PERLIN, "fEmptySpace.glsl"});

    if (GlobalFlags::DEBUG) {
        skyboxShader->validate();
        sceneShader->validate();
        atmosphereShader->validate();
        heightmapShader->validate();
        planetShader->validate();
        shader2D->validate();
        perlinShader->validate();
        spaceShader->validate();
    }

    testTexture = std::make_unique<Texture>("my_character_texturemap.png");
    screenBuffer = std::make_unique<GlScreenBuffer>(window->getWindow());
    stateRenderCache = std::make_unique<StateRenderCache>(perlinShader.get());
}