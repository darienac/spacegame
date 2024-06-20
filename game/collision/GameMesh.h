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
#include "TriangleCollider.h"

class GameMesh {
private:
    static inline double INF = std::numeric_limits<double>::infinity();

    std::vector<TriangleCollider> tris;
    BoxCollider boundingBox = {glm::dvec3{INF, INF, INF}, glm::dvec3{-INF, -INF, -INF}};
public:
    GameMesh();
    explicit GameMesh(const std::string& modelPath);
    explicit GameMesh(const std::vector<TriangleCollider> &tris);

    [[nodiscard]] const std::vector<TriangleCollider> &getTris() const;

    void addTri(const TriangleCollider &tri);

    void addTris(const std::string& modelPath);
    void addTris(aiMesh *mesh);
    void addTris(const std::vector<TriangleCollider> &tris);

    [[nodiscard]] const BoxCollider &getBoundingBox() const;
};


#endif //SPACEGAME_GAMEMESH_H
