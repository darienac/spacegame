//
// Created by dacma on 5/15/2024.
//

#ifndef SPACEGAME_PERLINNOISE_H
#define SPACEGAME_PERLINNOISE_H


#include "boost/uuid/uuid.hpp"

class PerlinNoise {
public:
    boost::uuids::uuid id;
    int perm[256];
    int numOctaves;
    float amplitude;
    float frequency;
    float amplitudeMult;
    float frequencyMult;
};


#endif //SPACEGAME_PERLINNOISE_H
