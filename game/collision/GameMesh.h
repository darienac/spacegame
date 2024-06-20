//
// Created by dacma on 6/19/2024.
//

#ifndef SPACEGAME_GAMEMESH_H
#define SPACEGAME_GAMEMESH_H


#include <vector>
#include <string>
#include <limits>
#include "glm/vec3.hpp"
#include <assimp/scene.h>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/mesh.h"
#include "BoxCollider.h"

class GameMesh {
private:
    static inline double INF = std::numeric_limits<double>::infinity();

    struct Triangle {
        glm::dvec3 points[3];
    };
    std::vector<Triangle> tris;
    BoxCollider boundingBox = {glm::dvec3{INF, INF, INF}, glm::dvec3{-INF, -INF, -INF}};
public:
    GameMesh();
    GameMesh(const std::string& modelPath);

    void addTri(const Triangle &tri);

    void addTris(const std::string& modelPath);
    void addTris(aiMesh *mesh);

    [[nodiscard]] const BoxCollider &getBoundingBox() const;
};


#endif //SPACEGAME_GAMEMESH_H
