//
// Created by dacma on 3/18/2024.
//

#ifndef CS455GAME_SHADER3D_H
#define CS455GAME_SHADER3D_H


#include "ShaderProgram.h"
#include "../Camera.h"
#include "../model/Mesh.h"
#include "../model/Model.h"
#include "../Environment.h"

class Shader3D: public ShaderProgram {
private:
    static std::string GLSL_HEADER;

    // attributes
    GLint aVertex;
    GLint aTexCoord;
    GLint aNormal;

    // uniforms
    GLint textureDiffuse;
    GLint textureCubemap;

    GLint uViewProjectionMatrix;
    GLint uModelMatrix;
    GLint uNormalMatrix;

    GLint uLightPosition;
    GLint uLightColor;
    GLint uAmbientLightColor;
    GLint uViewPosition;

    GLuint ubMaterial;
public:
    static std::string GLSL_PHONG_SHADING;
    static GLenum DIFFUSE_TEX_UNIT;
    static GLenum CUBEMAP_TEX_UNIT;

    Shader3D(std::vector<std::string> vertexShader, std::vector<std::string> fragmentShader);

    void loadCamera(Camera* camera, const glm::mat4& modelMatrix) const;
    void loadMesh(Mesh* mesh);
    void loadMaterial(Material* material);
    void loadEnvironment(Environment* env);

    void drawModel(Model *model);

    void link() override;
    void bind() override;
};


#endif //CS455GAME_SHADER3D_H
