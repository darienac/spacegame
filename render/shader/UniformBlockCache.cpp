//
// Created by dacma on 5/13/2024.
//

#include "UniformBlockCache.h"

UniformBlock *UniformBlockCache::getMaterialBlock(Material *material) {
    if (!materials.count(material)) {
        materials[material] = new UniformBlock(material);
    }
    return materials[material];
}

UniformBlock *UniformBlockCache::getMaterialBlock(std::vector<Material *> *materialList) {
    if (!materialLists.count(materialList)) {
        materialLists[materialList] = new UniformBlock(*materialList);
    }
    return materialLists[materialList];
}

UniformBlock *UniformBlockCache::getPerlinNoiseBlock(const PerlinNoise &perlinNoise) {
    if (!perlinNoises.count(perlinNoise.id)) {
        perlinNoises[perlinNoise.id] = new UniformBlock(perlinNoise);
    }
    return perlinNoises[perlinNoise.id];
}

void UniformBlockCache::updateMaterialBlock(Material *material) {
    UniformBlock *block = getMaterialBlock(material);
    block->loadMaterial(material);
}

void UniformBlockCache::freeMaterialBlock(Material *material) {
    if (materials.count(material)) {
        delete materials[material];
        materials.erase(material);
    }
}

void UniformBlockCache::freeMaterialBlock(std::vector<Material *> *materialList) {
    if (materialLists.count(materialList)) {
        delete materialLists[materialList];
        materialLists.erase(materialList);
    }
}

void UniformBlockCache::freePerlinNoiseBlock(const PerlinNoise &perlinNoise) {
    if (perlinNoises.count(perlinNoise.id)) {
        delete perlinNoises[perlinNoise.id];
        perlinNoises.erase(perlinNoise.id);
    }
}
