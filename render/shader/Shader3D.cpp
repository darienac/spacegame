//
// Created by dacma on 3/18/2024.
//

#include "Shader3D.h"
#include "UniformBlock.h"
#include "UniformBlockCache.h"

std::string Shader3D::GLSL_HEADER = "shared/f3D_header.glsl";
std::string Shader3D::GLSL_PHONG_SHADING = "shared/fPhong.glsl";
GLenum Shader3D::DIFFUSE_TEX_UNIT = GL_TEXTURE0;
GLenum Shader3D::CUBEMAP_TEX_UNIT = GL_TEXTURE1;

Shader3D::Shader3D(std::vector<std::string> vertexShader, std::vector<std::string> fragmentShader): ShaderProgram() {
    fragmentShader.insert(fragmentShader.begin(), GLSL_HEADER);
    createShaderFromPaths(vertexShader, GL_VERTEX_SHADER);
    createShaderFromPaths(fragmentShader, GL_FRAGMENT_SHADER);
    Shader3D::link();
}

Shader3D::Shader3D(const std::string &vertexShader, const std::string &fragmentShader): Shader3D(std::vector<std::string>{vertexShader}, std::vector<std::string>{fragmentShader}) {}

void Shader3D::link() {
    ShaderProgram::link();

    aVertex = attribute("aVertex");
    aTexCoord = attribute("aTexCoord");
    aNormal = attribute("aNormal");

    textureDiffuse = uniform("textureDiffuse");
    textureCubemap = uniform("textureCubemap");

    uViewProjectionMatrix = uniform("uViewProjectionMatrix");
    uModelMatrix = uniform("uModelMatrix");
    uNormalMatrix = uniform("uNormalMatrix");

    uViewPosition = uniform("uViewPosition");

    ubMaterial = uniformBlock("ubMaterial", UniformBlock::MATERIAL);
    ubLight = uniformBlock("ubLight", UniformBlock::LIGHT);

    ShaderProgram::bind();
    glUniform1i(textureDiffuse, 0);
    glUniform1i(textureCubemap, 1);
}

void Shader3D::bind() {
    ShaderProgram::bind();
}

void Shader3D::loadCamera(Camera* camera, const glm::mat4& modelMatrix) const {
    glm::mat4 viewProjectionMatrix = camera->getViewProjectionMatrix() * modelMatrix;
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    glUniformMatrix4fv(uViewProjectionMatrix, 1, GL_FALSE, &viewProjectionMatrix[0][0]);
    glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, &normalMatrix[0][0]);
    glUniform3fv(uViewPosition, 1, &camera->getPos()[0]);
}

void Shader3D::loadMesh(Mesh *mesh) {
    mesh->bind(aVertex, aTexCoord, aNormal);
    if (mesh->getMaterial() != nullptr) {
        loadMaterial(mesh->getMaterial());
    }
}

void Shader3D::loadMaterial(Material *material) {
    // Setup uniform values
    loadMaterialBlock(UniformBlockCache::getMaterialBlock(material));

    bindTexture(DIFFUSE_TEX_UNIT, *material->texture);
}

void Shader3D::loadMaterialBlock(UniformBlock *matBlock) {
    matBlock->setBindingPoint(UniformBlock::MATERIAL);
}

void Shader3D::drawModel(Model *model) {
    for (Mesh* mesh : model->getMeshes()) {
        loadMesh(mesh);
        mesh->draw();
    }
}
