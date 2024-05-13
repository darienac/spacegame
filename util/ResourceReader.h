//
// Created by dacma on 2/21/2024.
//

#ifndef CS455GAME_RESOURCEREADER_H
#define CS455GAME_RESOURCEREADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class ResourceReader {
public:
    enum ResourceType {
        Shader,
        Model,
        Texture,
        World,
        UI,
        Audio
    };

    static std::string readResource(ResourceType type, const std::string& path);
    static bool resourceExists(ResourceType type, const std::string& path);
    static std::string getFullPath(ResourceType type, std::string path);
};


#endif //CS455GAME_RESOURCEREADER_H
