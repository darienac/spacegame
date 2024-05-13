//
// Created by dacma on 3/21/2024.
//

#include "TextureCache.h"

std::string TextureCache::DEFAULT_BLACK = "defaultBlack.png";
std::string TextureCache::DEFAULT_WHITE = "defaultWhite.png";

std::map<std::string, Texture> TextureCache::cache;

Texture *TextureCache::getTexture(std::string path) {
    if (path.empty()) {
        return getTexture(DEFAULT_WHITE);
    }
    if (!cache.count(path)) {
        cache.emplace(path, path);
    }
    return &cache.at(path);
}

