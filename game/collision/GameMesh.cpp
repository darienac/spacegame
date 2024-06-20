//
// Created by dacma on 6/19/2024.
//

#include "GameMesh.h"
#include "TriangleCollider.h"
#include "../../util/ResourceReader.h"
#include "glm/common.hpp"

GameMesh::GameMesh() = default;

GameMesh::GameMesh(const std::string &modelPath) {
    addTris(modelPath);
}

GameMesh::GameMesh(const std::vector<TriangleCollider> &tris) {
    addTris(tris);
}

const std::vector<TriangleCollider> &GameMesh::getTris() const {
    return tris;
}

void GameMesh::addTri(const TriangleCollider &tri) {
    tris.push_back(tri);
    for (auto &point : tri.points) {
        boundingBox.min = glm::min(boundingBox.min, point);
        boundingBox.max = glm::max(boundingBox.max, point);
    }
}

void GameMesh::addTris(const std::string &modelPath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(ResourceReader::getFullPath(ResourceReader::Model, modelPath), aiProcess_Triangulate);
    if (!scene) {
        throw std::runtime_error("Unable to load model");
    }

    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        addTris(scene->mMeshes[i]);
    }
}

void GameMesh::addTris(aiMesh *mesh) {
    aiVector3D *vertices = mesh->mVertices;
    aiFace *faces = mesh->mFaces;

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace &face = faces[i];
        if (face.mNumIndices != 3) {
            throw std::runtime_error("AIFace.mNumIndices != 3");
        }
        TriangleCollider tri;
        tri.points[0] = {vertices[face.mIndices[0]].x, vertices[face.mIndices[0]].y, vertices[face.mIndices[0]].z};
        tri.points[1] = {vertices[face.mIndices[1]].x, vertices[face.mIndices[1]].y, vertices[face.mIndices[1]].z};
        tri.points[2] = {vertices[face.mIndices[2]].x, vertices[face.mIndices[2]].y, vertices[face.mIndices[2]].z};
        addTri(tri);
    }
}

void GameMesh::addTris(const std::vector<TriangleCollider> &tris) {
    for (auto &tri : tris) {
        addTri(tri);
    }
}

const BoxCollider &GameMesh::getBoundingBox() const {
    return boundingBox;
}
