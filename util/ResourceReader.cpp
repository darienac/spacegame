//
// Created by dacma on 2/21/2024.
//

#include "ResourceReader.h"

std::string ResourceReader::readResource(ResourceReader::ResourceType type, const std::string &path) {
    std::string fullPath = getFullPath(type, path);
    std::ifstream file(fullPath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool ResourceReader::resourceExists(ResourceReader::ResourceType type, const std::string &path) {
    return std::filesystem::exists(getFullPath(type, path));
}

std::string ResourceReader::getFullPath(ResourceReader::ResourceType type, std::string path) {
    switch (type) {
        case Shader:
            path = "res/shaders/" + path;
            break;
        case Model:
            path = "res/models/" + path;
            break;
        case Texture:
            path = "res/textures/" + path;
            break;
        case World:
            path = "worlds/" + path;
            break;
        case UI:
            path = "res/ui/" + path;
            break;
        case Audio:
            path = "res/audio/" + path;
            break;
    }

    return path;
}
