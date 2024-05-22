//
// Created by dacma on 4/30/2024.
//

#include "ResourceCache.h"
#include "../GlobalFlags.h"

ResourceCache::ResourceCache(GlWindow *window): window(window) {
    controls = std::make_unique<Controls>(window);

    Shader2D::initBuffers();
    skyboxShader = std::make_unique<Shader3D>("v3D.glsl", "fSkybox3D.glsl");
    sceneShader = std::make_unique<Shader3D>(std::vector<std::string>{"v3D.glsl"}, std::vector<std::string>{Shader3D::GLSL_PHONG_SHADING, "f3D.glsl"});
    planetShader = std::make_unique<ShaderPlanet>(std::vector<std::string>{"v3D.glsl"}, std::vector<std::string>{Shader3D::GLSL_PHONG_SHADING, "fPlanet3D.glsl"});
    shader2D = std::make_unique<Shader2D>(std::vector<std::string>{"v2D.glsl"}, std::vector<std::string>{"f2D.glsl"});
    perlinShader = std::make_unique<ShaderPerlin>(std::vector<std::string>{"v2D.glsl"}, std::vector<std::string>{"shared/perlin.glsl", "fPerlin.glsl"});
    spaceShader = std::make_unique<ShaderPerlin>(std::vector<std::string>{"v2D.glsl"}, std::vector<std::string>{"shared/perlin.glsl", "fEmptySpace.glsl"});

    if (GlobalFlags::DEBUG) {
        skyboxShader->validate();
        sceneShader->validate();
        planetShader->validate();
        shader2D->validate();
        perlinShader->validate();
        spaceShader->validate();
    }

    screenBuffer = std::make_unique<GlScreenBuffer>(window->getWindow());

    stateRenderCache = std::make_unique<StateRenderCache>(perlinShader.get());
}