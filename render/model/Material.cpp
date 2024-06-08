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

Material::Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                   const glm::vec3 &emissive, float opacity): ambient(ambient), diffuse(diffuse),
                   specular(specular), emissive(emissive), opacity(opacity),
                   texture(TextureCache::getTexture("")) {}

void Material::load(const Material &material) {
    ambient = material.ambient;
    diffuse = material.diffuse;
    specular = material.specular;
    emissive = material.emissive;
    opacity = material.opacity;
    texture = material.texture;
}

Material Material::blend(Material &mat1, Material &mat2, float bias) {
    float bias2 = (1.0f - bias);
    glm::vec3 ambient = mat1.ambient * bias + mat2.ambient * bias2;
    glm::vec3 diffuse = mat1.diffuse * bias + mat2.diffuse * bias2;
    glm::vec3 specular = mat1.specular * bias + mat2.specular * bias2;
    glm::vec3 emissive = mat1.emissive * bias + mat2.emissive * bias2;
    float opacity = mat1.opacity * bias + mat2.opacity * bias2;
    return {ambient, diffuse, specular, emissive, opacity};
}
