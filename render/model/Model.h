//
// Created by dacma on 3/20/2024.
//

#ifndef CS455GAME_MODEL_H
#define CS455GAME_MODEL_H

#include <string>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"
#include "Material.h"

class Model {
private:
    std::vector<Mesh*> meshes;
    std::vector<Material*> materials;

    Material* getMeshMaterial(aiMesh* mesh);
public:
    Model(const std::string& fileName);

    std::vector<Mesh*>& getMeshes();
    std::vector<Material*>& getMaterials();

    ~Model();
};


#endif //CS455GAME_MODEL_H
