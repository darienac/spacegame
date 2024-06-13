//
// Created by dacma on 3/18/2024.
//

#ifndef CS455GAME_SHADER3D_H
#define CS455GAME_SHADER3D_H


#include "ShaderProgram.h"
#include "../Camera.h"
#include "../model/Mesh.h"
#include "../model/Model.h"
#include "UniformBlock.h"
#include "../model/Cubemap.h"

class Shader3D: public ShaderProgram {
private:
    static std::string FRAGMENT_HEADER;
    static std::string VERTEX_HEADER;

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

    GLint uViewPosition;

    GLint uModelPosition;

    GLuint ubMaterial;
    GLuint ubLight;
    GLuint ubPlanetProps;
public:
    static std::string GLSL_PHONG_SHADING;
    static std::string GLSL_PERLIN;
    static GLenum DIFFUSE_TEX_UNIT;
    static GLenum CUBEMAP_TEX_UNIT;

    Shader3D(std::vector<std::string> vertexShader, std::vector<std::string> fragmentShader);
    Shader3D(const std::string &vertexShader, const std::string &fragmentShader);

    void loadCamera(Camera *camera, const glm::dmat4 &modelMatrix) const;
    void loadMesh(Mesh *mesh);
    void loadMesh(Mesh *mesh, UniformBlock &matBlock);
    void bindDiffuseTexture(const Texture &texture);
    void bindCubemap(const Cubemap &cubemap);
    void loadMaterial(const Material &material);
    static void loadMaterialBlock(UniformBlock &matBlock);

    void drawModel(Model *model);
    void drawModel(Model *model, UniformBlock &matBlock);

    void link() override;
    void bind() override;
};


#endif //CS455GAME_SHADER3D_H
