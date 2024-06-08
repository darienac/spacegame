//
// Created by dacma on 5/27/2024.
//

#ifndef SPACEGAME_HEIGHTMAP_H
#define SPACEGAME_HEIGHTMAP_H


#include "Mesh.h"
#include "glm/fwd.hpp"
#include "Mesh2D.h"
#include "../../game/state/GameState.h"
#include "../shader/ShaderPerlin.h"
#include "glm/detail/type_mat4x4.hpp"

class Heightmap {
private:
    static inline float RADIUS_MULT = 1.001;

    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Mesh2D> noiseSampleMesh;
    std::unique_ptr<Texture> noiseTexture;
    std::unique_ptr<GlFramebuffer> noiseFB;
    ShaderPerlin *perlinShader;
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::vec3 lastPos = {0.0, 0.0, 0.0};
    boost::uuids::uuid planetId;

    static Mesh *createMesh(uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, float lowerRadius);
    static Mesh2D *createNoiseSampleMesh(uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, float lowerRadius);
public:
    Heightmap(ShaderPerlin &perlinShader, uint32_t numCells, float cellWidth, uint32_t numExtendCells, float extendCellWidth, const GameState::Planet &planet);

    void updateToPosition(const glm::vec3 &pos, const PerlinNoise &noise);

    [[nodiscard]] Mesh *getMesh();
    [[nodiscard]] Mesh2D *getNoiseSampleMesh();
    [[nodiscard]] Texture *getNoiseTexture();
    [[nodiscard]] glm::mat4 *getRotation();
    [[nodiscard]] glm::vec3 *getLastPos();
};


#endif //SPACEGAME_HEIGHTMAP_H
