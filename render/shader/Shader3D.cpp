//
// Created by dacma on 3/18/2024.
//

#include "Shader3D.h"

std::string Shader3D::GLSL_HEADER = "shared/f3D_header.glsl";
std::string Shader3D::GLSL_PHONG_SHADING = "shared/fPhong.glsl";

Shader3D::Shader3D(std::vector<std::string> vertexShader, std::vector<std::string> fragmentShader): ShaderProgram() {
    fragmentShader.insert(fragmentShader.begin(), Shader3D::GLSL_HEADER);
    createShaderFromPaths(vertexShader, GL_VERTEX_SHADER);
    createShaderFromPaths(fragmentShader, GL_FRAGMENT_SHADER);
    Shader3D::link();
}

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

    uLightPosition = uniform("uLightPosition");
    uLightColor = uniform("uLightColor");
    uAmbientLightColor = uniform("uAmbientLightColor");
    uViewPosition = uniform("uViewPosition");

    uAmbientColor = uniform("uAmbientColor");
    uDiffuseColor = uniform("uDiffuseColor");
    uSpecularColor = uniform("uSpecularColor");
    uEmissiveColor = uniform("uEmissiveColor");

    uOpacity = uniform("uOpacity");

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
    if (material->opacity < 1.0f) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
    }

    // Setup uniform values
    glUniform3fv(uAmbientColor, 1, &material->ambient[0]);
    glUniform3fv(uDiffuseColor, 1, &material->diffuse[0]);
    glUniform3fv(uDiffuseColor, 1, &material->diffuse[0]);
    glUniform3fv(uSpecularColor, 1, &material->specular[0]);
    glUniform3fv(uEmissiveColor, 1, &material->emissive[0]);

    glUniform1f(uOpacity, material->opacity);

    bindTexture(GL_TEXTURE0, *material->texture);
}

void Shader3D::loadEnvironment(Environment *env) {
    glUniform3fv(uLightPosition, 1, &env->lightPos[0]);
    glUniform3fv(uLightColor, 1, &env->lightColor[0]);
    glUniform3fv(uAmbientLightColor, 1, &env->ambientLightColor[0]);
}

void Shader3D::drawModel(Model *model) {
    for (Mesh* mesh : model->getMeshes()) {
        loadMesh(mesh);
        mesh->draw();
    }
}
