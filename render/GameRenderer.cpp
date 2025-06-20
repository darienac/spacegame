//
// Created by dacma on 3/29/2024.
//

#include <queue>
#include "GameRenderer.h"
#include "../GlobalFlags.h"
#include "shader/UniformBlockCache.h"
#include "model/TextureCache.h"

glm::dmat4 GameRenderer::getModelTransform(const GameState::ModelState &modelState) {
    return glm::translate(glm::dmat4(1.0), modelState.pos) * glm::inverse(glm::lookAt({0.0, 0.0, 0.0}, modelState.dir, modelState.up)) * glm::scale(glm::dmat4(1.0), modelState.scale);
}

void GameRenderer::updateCamera() {
    camera.setPos(state->camera.pos);
    camera.setFOV(45.0);
    camera.setFacingDir(state->camera.dir);
    camera.setUp(state->camera.up);
    camera.setAspectRatio(cache->window->getAspectRatio());
}

void GameRenderer::drawPlanet(GameState::Planet &planet, Camera &renderCamera) {
    if (planet.lod >= GameState::GROUND) {
        return;
    }
    StateRenderCache::PlanetData *planetData = cache->stateRenderCache->planetResources[planet.id].get();
    cache->planetShader->bind();
    cache->planetShader->loadCamera(&renderCamera, planetData->modelTransform);
    cache->planetShader->loadMesh(planetData->mesh);
    cache->planetShader->bindTexture(Shader3D::CUBEMAP_TEX_UNIT, *planetData->planetSurfaceMap->texture);
    planetData->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    planetData->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    planetData->mesh->draw();
}

void GameRenderer::drawPlanetAtmosphere(GameState::Planet &planet, Camera &renderCamera) {
    StateRenderCache::PlanetData *data = cache->stateRenderCache->planetResources[planet.id].get();
    cache->atmosphereShader->bind();
    cache->atmosphereShader->loadCamera(&renderCamera, data->atmosphereModelTransform);
    cache->atmosphereShader->loadMesh(data->mesh);
    data->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    data->mesh->draw();
}

void GameRenderer::drawPlanetHeightmap(GameState::Planet &planet, Camera &renderCamera) {
    StateRenderCache::PlanetData *data = cache->stateRenderCache->planetResources[planet.id].get();
    cache->heightmapShader->bind();
    cache->heightmapShader->loadCamera(&renderCamera, data->heightmapModelTransform * *data->planetHeightmap->getRotation());
    cache->heightmapShader->loadMesh(data->planetHeightmap->getMesh());
    cache->heightmapShader->bindDiffuseTexture(*data->planetHeightmap->getNoiseTexture());
    data->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    data->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    glDepthFunc(GL_LEQUAL);
    data->planetHeightmap->getMesh()->draw();
    glDepthFunc(GL_LESS);
}

void GameRenderer::drawStar(GameState::Star &star, Camera &renderCamera) {
    StateRenderCache::StarData *starData = cache->stateRenderCache->starResources[star.id].get();
    cache->sceneShader->bind();
    cache->sceneShader->loadCamera(&renderCamera, starData->modelTransform);
    cache->sceneShader->loadMesh(starData->mesh);
    cache->sceneShader->bindCubemap(*cache->stateRenderCache->blackCubemap);
    Shader3D::loadMaterialBlock(*cache->stateRenderCache->starResources[star.id]->matBlock);
    starData->mesh->draw();
}

void GameRenderer::drawModel(GameRenderer::ModelRenderData &renderData, Camera &renderCamera) {
    glm::dmat4 modelTransform = getModelTransform(*renderData.modelState);
    cache->sceneShader->bind();
    cache->sceneShader->loadCamera(&renderCamera, modelTransform);
    if (renderData.cubemap) {
        cache->sceneShader->bindCubemap(*renderData.cubemap);
    } else {
        cache->sceneShader->bindCubemap(*cache->stateRenderCache->blackCubemap);
    }
    if (renderData.matBlock) {
        cache->sceneShader->bindDiffuseTexture(*TextureCache::getTexture(TextureCache::DEFAULT_WHITE));
        cache->sceneShader->drawModel(renderData.model, *renderData.matBlock);
    } else {
        cache->sceneShader->drawModel(renderData.model);
    }
}

void GameRenderer::drawSkybox(Cubemap &cubemap, Camera &renderCamera) {
    cache->skyboxShader->bind();
    cache->skyboxShader->bindCubemap(cubemap);
    cache->skyboxShader->loadCamera(&renderCamera, glm::translate<double>(glm::dmat4(1.0), renderCamera.getPos()));
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    cache->skyboxShader->drawModel(cache->stateRenderCache->skybox.get());
    glEnable(GL_DEPTH_TEST);
}

void GameRenderer::addTestSphereTask(GameState::ModelState &modelState, bool useHighlight) {
    renderTasks.emplace_back(RenderTask{
        .type = BASIC_MODEL,
        .usesTransparency = true,
        .pos = modelState.pos,
        .modelRenderData = {
            .modelState = &modelState,
            .model = cache->stateRenderCache->orb_3.get(),
            .matBlock = useHighlight ? cache->stateRenderCache->debugMatBlock2.get() : cache->stateRenderCache->debugMatBlock1.get(),
            .cubemap = cache->stateRenderCache->shipReflectionMap.get()
        }
    });
}

void GameRenderer::addTestBoxTask(GameState::ModelState &modelState, bool useHighlight) {
    renderTasks.emplace_back(RenderTask{
            .type = BASIC_MODEL,
            .usesTransparency = true,
            .pos = modelState.pos,
            .modelRenderData = {
                .modelState = &modelState,
                .model = cache->stateRenderCache->testBox.get(),
                .matBlock = useHighlight ? cache->stateRenderCache->debugMatBlock2.get() : cache->stateRenderCache->debugMatBlock1.get(),
                .cubemap = cache->stateRenderCache->shipReflectionMap.get()
            }
    });
}

void GameRenderer::runRenderTasks(Camera &renderCamera) {
    std::size_t numTransparent = 0;
    std::size_t numOpaque = 0;
    for (auto &task : renderTasks) {
        if (task.type == SKYBOX) {
            runRenderTask(task, renderCamera);
            continue;
        }
        if (task.usesTransparency) {
            numTransparent++;
        } else {
            numOpaque++;
        }
    }
    std::vector<RenderTask*> sortedTransparent;
    std::vector<RenderTask*> sortedOpaque;
    sortedTransparent.reserve(numTransparent);
    sortedOpaque.reserve(numOpaque);
    for (auto &task : renderTasks) {
        if (task.type == SKYBOX) {
            continue;
        }
        if (task.usesTransparency) {
            sortedTransparent.push_back(&task);
        } else {
            sortedOpaque.push_back(&task);
        }
    }

    std::sort(sortedTransparent.begin(), sortedTransparent.end(), [this, &renderCamera](RenderTask* a, RenderTask* b) {
        return glm::distance(renderCamera.getPos(), a->pos) > glm::distance(renderCamera.getPos(), b->pos);
    });
    std::sort(sortedOpaque.begin(), sortedOpaque.end(), [this, &renderCamera](RenderTask* a, RenderTask* b) {
        return glm::distance(renderCamera.getPos(), a->pos) < glm::distance(renderCamera.getPos(), b->pos);
    });
    for (auto &task : sortedOpaque) {
        runRenderTask(*task, renderCamera);
    }
    for (auto &task : sortedTransparent) {
        runRenderTask(*task, renderCamera);
    }
}

void GameRenderer::runRenderTask(GameRenderer::RenderTask &task, Camera &renderCamera) {
    if (!task.enabled) {
        return;
    }
    switch (task.type) {
        case SKYBOX:
            drawSkybox(*task.skybox, renderCamera);
            break;
        case STAR:
            drawStar(*task.star, renderCamera);
            break;
        case PLANET:
            drawPlanet(*task.planet, renderCamera);
            break;
        case PLANET_ATMOSPHERE:
            drawPlanetAtmosphere(*task.planet, renderCamera);
            break;
        case PLANET_HEIGHTMAP:
            drawPlanetHeightmap(*task.planet, renderCamera);
            break;
        case BASIC_MODEL:
            drawModel(task.modelRenderData, renderCamera);
            break;
    }
}

void GameRenderer::runRenderTasksOnCubemap(Cubemap &cubemap, glm::dvec3 &pos) {
    Camera cubemapCamera;
    for (uint8_t i = 0; i < 6; i++) {
        cubemap.bindToSide(i, pos, cubemapCamera);
        runRenderTasks(cubemapCamera);
    }
}

GameRenderer::GameRenderer(GameState *state, ResourceCache* cache): state(state), cache(cache) {
    cache->spaceShader->bind();
    cache->spaceShader->loadPerlinConfig(state->spaceNoise, glm::mat4(1.0f));
    cache->spaceShader->draw(cache->stateRenderCache->cameraCubemap.get());
    renderTasks.reserve(16384);
}

void GameRenderer::drawScene() {
    if (cache->window->getWidth() == 0 || cache->window->getHeight() == 0) {
        return;
    }
    updateCamera();
    cache->stateRenderCache->syncToState(state);

    cache->screenBuffer->bind();

    renderTasks.emplace_back(RenderTask{
        .enabled = true,
        .type = SKYBOX,
        .skybox = cache->stateRenderCache->cameraCubemap.get()
    });

    // Setup Ship Render
    Material *boosterMat = cache->shipModel->getMaterials()[3];
    if (state->ship.boosterState == GameState::BOOSTER_OFF) {
        boosterMat->load(cache->shipMaterials[0]);
    } else {
        Material *baseMat = &cache->shipMaterials[0];
        Material *blendMat = &cache->shipMaterials[state->ship.boosterState];
        boosterMat->load(Material::blend(*blendMat, *baseMat, state->ship.boosterStrength));
    }
    UniformBlockCache::updateMaterialBlock(*boosterMat);
    auto &shipTask = renderTasks.emplace_back(RenderTask{
        .type = BASIC_MODEL,
        .usesTransparency = false,
        .pos = state->ship.modelState.pos,
        .modelRenderData = {
            .modelState = &state->ship.modelState,
            .model = cache->shipModel.get(),
            .cubemap = cache->stateRenderCache->shipReflectionMap.get()
        }
    });

//    renderTasks.emplace_back(RenderTask{
//        .type = BASIC_MODEL,
//        .usesTransparency = false,
//        .pos = {0.0f, 0.0f, 0.0f},
//        .modelRenderData = {
//                .modelState = &state->island,
//                .model = cache->islandModel.get()
//        }
//    });

    GameState::ModelState debug1 {
        .pos = state->ship.modelState.pos,
        .dir = state->ship.modelState.dir,
        .up = state->ship.modelState.up,
        .scale = state->ship.modelState.scale * (state->debug.shipMesh->getBoundingBox().max - state->debug.shipMesh->getBoundingBox().min)
    };
//    addTestBoxTask(debug1, state->debug.objectsCollide);
    std::queue<const MeshCollider*> meshes;
    meshes.push(state->debug.islandMesh);
    uint32_t nodesOnLayer = 1;
    uint32_t layer = 0;
    uint32_t numOnLayer = 0;
    std::vector<GameState::ModelState> modelStates;
    modelStates.reserve(16384);
    while (!meshes.empty()) {
        const MeshCollider *mesh = meshes.front();
        meshes.pop();
        nodesOnLayer--;
        if (mesh->getTris().empty()) {
            meshes.push(&mesh->getLeft());
            meshes.push(&mesh->getRight());
        }
        if (layer == state->debug.layer) {
//        if (!mesh->getTris().empty()) {
            numOnLayer++;
//            std::cout << "min: " << mesh->getBoundingBox().min.x << " " << mesh->getBoundingBox().min.y << " " << mesh->getBoundingBox().min.z << std::endl;
//            std::cout << "max: " << mesh->getBoundingBox().max.x << " " << mesh->getBoundingBox().max.y << " " << mesh->getBoundingBox().max.z << std::endl;
            modelStates.emplace_back(GameState::ModelState{
                .pos = state->island.pos + (mesh->getBoundingBox().max + mesh->getBoundingBox().min) * 0.5 * state->island.scale,
                .dir = state->island.dir,
                .up = state->island.up,
                .scale = state->island.scale * (mesh->getBoundingBox().max - mesh->getBoundingBox().min)
            });
            if (renderTasks.size() >= 16000) {
                break;
            }
//            addTestBoxTask(modelStates.back(), state->debug.objectsCollide);
        }
        if (nodesOnLayer == 0) {
            nodesOnLayer = meshes.size();
            layer++;
        }
    }
//    std::cout << "Num on layer: " << numOnLayer << std::endl;

    for (auto &pair : state->planets) {
        renderTasks.emplace_back(RenderTask{
            .type = PLANET,
            .usesTransparency = false,
            .pos = pair.second->position,
            .planet = pair.second
        });
        renderTasks.emplace_back(RenderTask{
            .type = PLANET_ATMOSPHERE,
            .usesTransparency = true,
            .pos = pair.second->position,
            .planet = pair.second
        });
        if (pair.second->lod >= GameState::ATMOSPHERE) {
            renderTasks.emplace_back(RenderTask{
                .type = PLANET_HEIGHTMAP,
                .usesTransparency = false,
                .pos = {0.0f, 0.0f, 0.0f},
                .planet = pair.second
            });
        }
    }
    for (auto &pair : state->stars) {
        renderTasks.emplace_back(RenderTask{
            .type = STAR,
            .usesTransparency = false,
            .pos = pair.second->position,
            .star = pair.second
        });
    }

    shipTask.enabled = false;
    runRenderTasksOnCubemap(*cache->stateRenderCache->shipReflectionMap, shipTask.pos);
    cache->screenBuffer->bind();
    shipTask.enabled = true;
    runRenderTasks(camera);
    renderTasks.clear();
}

void GameRenderer::debugViewTexture(const Texture &texture) {
    cache->screenBuffer->bind();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    updateCamera();
    cache->stateRenderCache->syncToState(state);
    cache->shader2D->draw(texture);
}
