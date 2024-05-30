//
// Created by dacma on 3/19/2024.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> texCoords, std::vector<glm::vec3> normals,
           std::vector<glm::ivec3> faces) {
    glGenBuffers(1, &verticesBuffer);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &facesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * texCoords.size(), texCoords.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);

    facesSize = sizeof(glm::ivec3) * faces.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize, faces.data(), GL_STATIC_DRAW);
}

Mesh::Mesh(const GLfloat *vertices, GLsizeiptr verticesSize, const GLint *faces, GLsizeiptr facesSize): facesSize(facesSize) {
    glGenBuffers(1, &verticesBuffer);
    glGenBuffers(1, &facesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize, faces, GL_STATIC_DRAW);
}

void Mesh::bind(GLint aVertex, GLint aTexCoord, GLint aNormal) {
    if (aVertex != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
        glVertexAttribPointer(aVertex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
    if (aTexCoord != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
        glVertexAttribPointer(aTexCoord, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
    if (aNormal != -1) {
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
}

void Mesh::draw() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glDrawElements(GL_TRIANGLES, facesSize / sizeof(GLint), GL_UNSIGNED_INT, nullptr); // 6 for a quad
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
    facesSize = elementCount * sizeof(GLint);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize, facesArray, GL_STATIC_DRAW);
}

Material *Mesh::getMaterial() const {
    return material;
}
