//
// Created by dacma on 4/30/2024.
//

#include "ResourceCache.h"
#include "../GlobalFlags.h"

ResourceCache::ResourceCache(GlWindow *window): window(window) {
    controls = new Controls(window);

    Shader2D::initBuffers();
    skyboxShader = new Shader3D({"v3D.glsl"}, {"fSkybox3D.glsl"});
    sceneShader = new Shader3D({"v3D.glsl"}, {Shader3D::GLSL_PHONG_SHADING, "f3D.glsl"});
    planetShader = new ShaderPlanet({"v3D.glsl"}, {Shader3D::GLSL_PHONG_SHADING, "fPlanet3D.glsl"});
    shader2D = new Shader2D({"v2D.glsl"}, {"f2D.glsl"});
    perlinShader = new ShaderPerlin({"v2D.glsl"}, {"shared/perlin.glsl", "fPerlin.glsl"});
    spaceShader = new ShaderPerlin({"v2D.glsl"}, {"shared/perlin.glsl", "fEmptySpace.glsl"});

    if (GlobalFlags::DEBUG) {
        skyboxShader->validate();
        sceneShader->validate();
        planetShader->validate();
        shader2D->validate();
        perlinShader->validate();
        spaceShader->validate();
    }

    screenBuffer = new GlScreenBuffer(window->getWindow());

    stateRenderCache = new StateRenderCache(perlinShader);
}

ResourceCache::~ResourceCache() {
    delete skyboxShader;
    delete sceneShader;
    delete planetShader;
    delete shader2D;
    delete perlinShader;
    delete spaceShader;

    delete screenBuffer;

    delete stateRenderCache;
}
