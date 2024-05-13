//
// Created by dacma on 3/21/2024.
//

#ifndef CS455GAME_TEXTURECACHE_H
#define CS455GAME_TEXTURECACHE_H


#include <string>
#include <map>
#include "Texture.h"

class TextureCache {
private:
    static std::map<std::string, Texture> cache;
public:
    static std::string DEFAULT_WHITE;
    static std::string DEFAULT_BLACK;

    static Texture* getTexture(std::string path);
};


#endif //CS455GAME_TEXTURECACHE_H
