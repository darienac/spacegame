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
