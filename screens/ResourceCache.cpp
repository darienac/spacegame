//
// Created by dacma on 4/30/2024.
//

#include "ResourceCache.h"

ResourceCache::ResourceCache(GlWindow *window): window(window) {
    controls = new Controls(window);

    Shader2D::initBuffers();
    sceneShader = new Shader3D({"v3D.glsl"}, {Shader3D::GLSL_PHONG_SHADING, "f3D.glsl"});
    planetShader = new Shader3D({"v3D.glsl"}, {Shader3D::GLSL_PHONG_SHADING, "fPlanet3D.glsl"});
    shader2D = new Shader2D({"v2D.glsl"}, {"f2D.glsl"});
    perlinShader = new ShaderPerlin({"v2D.glsl"}, {"fPerlin.glsl"});

    blueOrb = new Model("blue_orb.obj");

    basicEnv = {
            .lightPos = {0.0f, 100.0f, 0.0f},
            .lightColor = {3.0f, 3.0f, 3.0f},
            .ambientLightColor = {0.01f, 0.01f, 0.01f}
    };
}

ResourceCache::~ResourceCache() {
    delete sceneShader;
    delete planetShader;
    delete shader2D;
    delete perlinShader;

    delete blueOrb;
}