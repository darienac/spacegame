//
// Created by dacma on 3/20/2024.
//

#include <assimp/Importer.hpp>
#include "Model.h"
#include "../../util/ResourceReader.h"

Model::Model(const std::string &fileName) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(ResourceReader::getFullPath(ResourceReader::Model, fileName), aiProcess_Triangulate);
    if (!scene) {
        throw std::runtime_error("Unable to load model");
    }

    unsigned int materialCount = scene->mNumMaterials;
    materials.reserve(materialCount);
    for (unsigned int i = 0; i < materialCount; i++) {
        materials.push_back(new Material(scene->mMaterials[i]));
    }

    unsigned int meshCount = scene->mNumMeshes;
    meshes.reserve(meshCount);
    for (unsigned int i = 0; i < meshCount; i++) {
        meshes.push_back(new Mesh(scene->mMeshes[i], getMeshMaterial(scene->mMeshes[i])));
    }
}

Material *Model::getMeshMaterial(aiMesh *mesh) {
    unsigned int matIdx = mesh->mMaterialIndex;
    if (matIdx < materials.size()) {
        return materials[matIdx];
    } else {
        throw std::runtime_error("No valid material id provided");
    }
}

std::vector<Mesh *> &Model::getMeshes() {
    return meshes;
}

std::vector<Material *> &Model::getMaterials() {
    return materials;
}

Model::~Model() {
    for (auto p : meshes) {
        delete p;
    }
    for (auto p : materials) {
        delete p;
    }
}

