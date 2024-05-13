//
// Created by dacma on 3/19/2024.
//

#include "Mesh.h"

Mesh::Mesh(const GLfloat *vertices, GLsizeiptr verticesSize, const GLint *faces, GLsizeiptr facesSize): facesSize(facesSize) {
    glGenBuffers(1, &verticesBuffer);
    glGenBuffers(1, &facesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize, faces, GL_STATIC_DRAW);
    material = nullptr;
}

void Mesh::bind(GLint aVertex, GLint aTexCoord, GLint aNormal) {
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glVertexAttribPointer(aTexCoord, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::draw() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glDrawElements(GL_TRIANGLES, facesSize / sizeof(GLfloat), GL_UNSIGNED_INT, nullptr); // 6 for a quad
}

Mesh::Mesh(aiMesh *mesh, Material* material): material(material) {
    aiVector3D* vertices = mesh->mVertices;
    aiVector3D* texCoords = mesh->mTextureCoords[0];
    aiVector3D* normals = mesh->mNormals;
    aiFace* faces = mesh->mFaces;

    glGenBuffers(1, &verticesBuffer);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &facesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, texCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, normals, GL_STATIC_DRAW);

    GLsizeiptr elementCount = mesh->mNumFaces * 3;
    auto facesArray = new GLint[elementCount];
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = faces[i];
        if (face.mNumIndices != 3) {
            throw std::runtime_error("AIFace.mNumIndices != 3");
        }
        facesArray[i*3] = face.mIndices[0];
        facesArray[i*3+1] = face.mIndices[1];
        facesArray[i*3+2] = face.mIndices[2];
    }
    facesSize = elementCount * sizeof(GLfloat);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize, facesArray, GL_STATIC_DRAW);
}

Material *Mesh::getMaterial() const {
    return material;
}
