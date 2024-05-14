//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCKCACHE_H
#define SPACEGAME_UNIFORMBLOCKCACHE_H


#include <map>
#include "../model/Material.h"
#include "UniformBlock.h"

class UniformBlockCache {
private:
    static inline std::map<Material*, UniformBlock*> materials;
public:
    static UniformBlock *getMaterialBlock(Material *material);
};


#endif //SPACEGAME_UNIFORMBLOCKCACHE_H
