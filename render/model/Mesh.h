//
// Created by dacma on 3/19/2024.
//

#ifndef CS455GAME_MESH_H
#define CS455GAME_MESH_H


#include <GL/glew.h>
#include "assimp/mesh.h"
#include "Material.h"

class Mesh {
private:
    GLuint verticesBuffer;
    GLuint texCoordBuffer;
    GLuint normalBuffer;
    GLuint facesBuffer;

    GLsizeiptr facesSize;

    Material* material;
public:
    Mesh(const GLfloat *vertices, GLsizeiptr verticesSize, const GLint *faces, GLsizeiptr facesSize);
    Mesh(aiMesh* mesh, Material* material);

    void bind(GLint aVertex, GLint aTexCoord, GLint aNormal);
    void draw();

    Material* getMaterial() const;
};


#endif //CS455GAME_MESH_H
