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
    static inline std::map<Material*, UniformBlock*> materials;
    static inline std::map<std::vector<Material*>*, UniformBlock*> materialLists;
    static inline std::map<boost::uuids::uuid, UniformBlock*> perlinNoises;
public:
    static UniformBlock *getMaterialBlock(Material *material);
    static UniformBlock *getMaterialBlock(std::vector<Material *> *materialList);
    static UniformBlock *getPerlinNoiseBlock(const PerlinNoise &perlinNoise);
    static void freeMaterialBlock(Material *material);
    static void freeMaterialBlock(std::vector<Material *> *materials);
    static void freePerlinNoiseBlock(const PerlinNoise &perlinNoise);
};


#endif //SPACEGAME_UNIFORMBLOCKCACHE_H
