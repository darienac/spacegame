//
// Created by dacma on 5/27/2024.
//

#include "Heightmap.h"
#include "glm/geometric.hpp"
#include "glm/ext/matrix_transform.hpp"

Mesh *Heightmap::createMesh(uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, float lowerRadius) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;
    std::size_t numVertices = (numCells+1)*(numCells+1) + numCells*4*numExtendCells;
    vertices.reserve(numVertices);
    texCoords.reserve(numVertices);
    normals.reserve(numVertices);

    // points
    float width = (float) numCells * cellWidth * (2.0f * (float) numExtendCells * extendCellWidth);
    float innerWidth = (float) numCells * cellWidth;
    float xInnerMin = innerWidth * -0.5f;
    float texInnerWidth = (float) numCells / (numExtendCells * 2);
    float texInnerMin = (1.0f - texInnerWidth) * 0.5f;
    for (std::size_t i = 0; i <= numCells; i++) {
        for (std::size_t j = 0; j <= numCells; j++) {
            glm::vec3 pos = glm::vec3(xInnerMin + ((float) i / numCells) * innerWidth, lowerRadius, xInnerMin + ((float) j / numCells) * innerWidth);
            vertices.emplace_back(glm::normalize(pos) * lowerRadius);
            texCoords.emplace_back(texInnerMin + ((float) i / numCells) * texInnerWidth, texInnerMin + ((float) j / numCells) * texInnerWidth, 0.0f);
            normals.emplace_back(glm::normalize(pos));

            // temporary, draw 0=(x^{2}+z-y) / 10
//            vertices[vertices.size()-1] = (vertices[vertices.size()-1].x * vertices[vertices.size()-1].x + vertices[vertices.size()-1].z) / 5.0f;
//            glm::vec3 v = vertices[vertices.size()-1];
//            normals[normals.size()-1] = glm::normalize(-1.0f * glm::vec3{0.4f * v.x, -1.0f, 0.2f});
        }
    }

    // faces
    for (std::size_t i = 0; i < numCells; i++) {
        for (std::size_t j = 0; j < numCells; j++) {
            std::size_t v0 = i * (numCells+1) + j;
            std::size_t v1 = v0 + (numCells+1);
            std::size_t v2 = v0 + 1;
            std::size_t v3 = v1 + 1;

            faces.emplace_back(v0, v2, v3);
            faces.emplace_back(v3, v1, v0);
        }
    }

    return new Mesh(vertices, texCoords, normals, faces);
}

Mesh2D *Heightmap::createNoiseSampleMesh(uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, float lowerRadius) {
    GLfloat innerDist = numCells * cellWidth * 0.5f;
    GLfloat outerDist = innerDist + numExtendCells * extendCellWidth;
    uint32_t totalCells = numCells + numExtendCells * 2;
    GLfloat innerTexPos = (totalCells - numCells) * 0.5f;
    GLfloat innerTexPos2 = 1.0f - innerTexPos;

    return new Mesh2D(
        std::vector<GLfloat>{
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            innerTexPos, innerTexPos,
            innerTexPos2, innerTexPos,
            innerTexPos, innerTexPos2,
            innerTexPos2, innerTexPos2
        }, std::vector<GLfloat>{
                    -outerDist, lowerRadius, -outerDist,
                    outerDist, lowerRadius, -outerDist,
                    -outerDist, lowerRadius, outerDist,
                    outerDist, lowerRadius, outerDist,
                    -innerDist, lowerRadius, -innerDist,
                    innerDist, lowerRadius, -innerDist,
                    -innerDist, lowerRadius, innerDist,
                    innerDist, lowerRadius, innerDist,
        }, std::vector<GLint>{
            0, 1, 4,
            4, 1, 5,
            0, 4, 6,
            0, 6, 2,
            5, 1, 7,
            7, 1, 3,
            2, 6, 7,
            2, 7, 3,
            6, 4, 5,
            6, 5, 7
    });
}

Heightmap::Heightmap(ShaderPerlin &perlinShader, uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, const GameState::Planet &planet) {
    float lowerRadius = planet.radius * RADIUS_MULT;
    this->perlinShader = &perlinShader;
    mesh = std::unique_ptr<Mesh>(createMesh(numCells, cellWidth, numExtendCells, extendCellWidth, lowerRadius));
    noiseSampleMesh = std::unique_ptr<Mesh2D>(createNoiseSampleMesh(numCells, cellWidth, numExtendCells, extendCellWidth, lowerRadius));
    uint32_t width = numCells + 1 + numExtendCells * 2;
    noiseTexture = std::make_unique<Texture>(width, width, GL_RED, GL_RED, GL_TEXTURE_2D);
    noiseFB = std::make_unique<GlFramebuffer>(std::vector<Texture*>{noiseTexture.get()}, false);
}

Mesh *Heightmap::getMesh() {
    return mesh.get();
}

Mesh2D *Heightmap::getNoiseSampleMesh() {
    return noiseSampleMesh.get();
}

void Heightmap::updateToPosition(const glm::vec3 &pos) {
    // TODO: implement this, store the orientation for the last render, probably use glm::lookAt
    lastPos = glm::normalize(pos);
    glm::vec3 up;
    if (lastPos.x < lastPos.y && lastPos.x < lastPos.z) {
        up = {1.0f, 0.0f, 0.0f};
    } else if (lastPos.y < lastPos.x && lastPos.y < lastPos.z) {
        up = {0.0f, 1.0f, 0.0f};
    } else {
        up = {0.0f, 0.0f, 1.0f};
    }
    up = {0.0f, 1.0f, 0.0f};
    rotation = glm::inverse(glm::lookAt({0.0f, 0.0f, 0.0f}, lastPos, up)) * glm::lookAt(glm::vec3{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f});

    noiseFB->bind();
    // TODO: Render the perlin noise
    perlinShader->draw(noiseSampleMesh.get());

    std::cout << "Pos updated" << std::endl;
}

glm::mat4 *Heightmap::getRotation() {
    return &rotation;
}

glm::vec3 *Heightmap::getLastPos() {
    return &lastPos;
}
