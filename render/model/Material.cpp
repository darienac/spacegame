//
// Created by dacma on 3/20/2024.
//

#include "Material.h"
#include "TextureCache.h"

Material::Material(aiMaterial *material) {
//    aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, )
    aiString texPath;
    material->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), texPath);
    if (texPath.length > 0) {
        texture = TextureCache::getTexture(texPath.C_Str());
    } else {
        texture = TextureCache::getTexture("");
    }

    aiColor3D color;
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    ambient = {color.r, color.g, color.b};
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    diffuse = {color.r, color.g, color.b};
    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    specular = {color.r, color.g, color.b};
    material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
    emissive = {color.r, color.g, color.b};
    material->Get(AI_MATKEY_OPACITY, opacity);
}
