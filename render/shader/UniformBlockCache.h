//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCKCACHE_H
#define SPACEGAME_UNIFORMBLOCKCACHE_H


#include <map>
#include "UniformBlock.h"
#include "../model/Material.h"

class UniformBlockCache {
private:
    static inline std::map<const Material*, UniformBlock*> materials;
    static inline std::map<const std::vector<const Material*>*, UniformBlock*> materialLists;
    static inline std::map<boost::uuids::uuid, UniformBlock*> perlinNoises;
public:
    static UniformBlock *getMaterialBlock(const Material &material);
    static UniformBlock *getMaterialBlock(const std::vector<const Material*> &materialList);
    static UniformBlock *getPerlinNoiseBlock(const PerlinNoise &perlinNoise);
    static void updateMaterialBlock(const Material &material);
    static void freeMaterialBlock(const Material &material);
    static void freeMaterialBlock(const std::vector<const Material*> &materialList);
    static void freePerlinNoiseBlock(const PerlinNoise &perlinNoise);
};


#endif //SPACEGAME_UNIFORMBLOCKCACHE_H
