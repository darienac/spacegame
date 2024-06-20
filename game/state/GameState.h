//
// Created by dacma on 4/30/2024.
//

#ifndef SPACEGAME_GAMESTATE_H
#define SPACEGAME_GAMESTATE_H

#include <map>
#include "boost/uuid/uuid.hpp"
#include "glm/vec3.hpp"
#include "PerlinNoise.h"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"
#include "../collision/GameMesh.h"

class GameState {
public:
    struct Debug {
        bool objectsCollide = false;
        GameMesh *shipMesh;
        GameMesh *islandMesh;
    };

    enum Planet_LOD {
        DISTANT2,
        DISTANT,
        NEAR,
        ATMOSPHERE,
        GROUND,
        GROUND2
    };

    struct CameraState {
        glm::dvec3 pos;
        glm::dvec3 dir;
        glm::dvec3 up;
        bool viewInverted;
    };

    struct ModelState {
        glm::dvec3 pos;
        glm::dvec3 dir = {0.0, 0.0, -1.0};
        glm::dvec3 up = {0.0, 1.0, 0.0};
        glm::dvec3 scale = {1.0, 1.0, 1.0};
    };

    enum ShipBoosterState {
        BOOSTER_OFF,
        BOOSTER_ON,
        BOOSTER_TURBO
    };

    struct ShipState {
        ModelState modelState;
        glm::dvec3 vel;
        double rollVel;
        glm::dvec2 turnVel;
        ShipBoosterState boosterState;
        double boosterStrength;
    };

    struct Planet {
        boost::uuids::uuid id;
        Planet_LOD lod;
        glm::vec3 surfaceColor;
        glm::vec4 atmosphereColor;
        float atmosphereHeight;
        glm::vec3 liquidColor;
        float liquidHeight;
        float maxLandHeight;
        PerlinNoise surfaceNoise;
        glm::dvec3 position;
        double radius;
    };

    struct Star {
        boost::uuids::uuid id;
        Planet_LOD lod;
        glm::vec3 color;
        glm::dvec3 position;
        double radius;
    };

    struct Light {
        boost::uuids::uuid id;
        glm::dvec3 position;
        glm::vec3 color;
    };

    Planet planet = {
            .id = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
            .lod = ATMOSPHERE,
            .surfaceColor = {0.1f, 0.25f, 0.1f},
            .atmosphereColor = {0.2f, 0.7f, 1.0f, 0.8f},
            .atmosphereHeight = 25.0f,
            .liquidColor = {0.02f, 0.1f, 0.2f},
            .liquidHeight = 0.005f,
            .maxLandHeight = 0.01f,
            .surfaceNoise = {
                    .id = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
                    .perm = {149,142,120,125,178,21,129,250,26,3,53,180,168,253,218,177,27,30,158,75,32,117,222,56,195,39,69,71,44,160,143,199,201,102,19,251,165,184,154,70,115,249,153,52,28,78,121,220,95,7,183,72,10,107,179,188,57,99,215,144,225,155,47,68,235,37,40,74,136,85,84,55,204,243,202,217,67,187,227,211,174,219,134,233,6,18,77,92,166,24,66,161,14,9,49,192,89,106,98,36,105,13,148,35,79,103,45,186,230,164,65,207,138,203,221,132,175,238,131,111,15,255,212,23,5,46,90,237,198,209,83,150,216,196,76,157,224,254,87,245,34,137,127,152,11,241,130,113,141,171,17,169,173,172,210,234,94,252,206,88,43,12,20,242,41,176,162,2,112,22,247,73,4,29,189,182,240,109,63,228,51,246,123,97,42,140,200,48,33,96,64,236,193,159,151,146,133,1,0,226,139,248,54,118,128,223,163,167,116,58,8,185,25,190,147,108,126,194,59,16,191,244,145,229,170,38,91,124,100,31,81,119,61,231,156,104,86,232,197,205,101,214,60,239,135,82,122,208,80,93,213,110,62,114,181,50},
                    .numOctaves = 5,
                    .amplitude = 1.0f,
                    .frequency = 1.0f,
                    .amplitudeMult = 0.5f,
                    .frequencyMult = 2.0f
            },
            .position = {-10000.0, 0.0, 0.0},
            .radius = 1000.0
    };

    Planet planet2 = {
            .id = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe},
            .lod = ATMOSPHERE,
            .surfaceColor = {0.3f, 0.15f, 0.1f},
            .atmosphereColor = {1.0f, 0.8f, 0.7f, 0.9f},
            .atmosphereHeight = 40.0f,
            .liquidColor = {0.3f, 0.25f, 0.2f},
            .liquidHeight = 0.003f,
            .maxLandHeight = 0.01f,
            .surfaceNoise = {
                    .id = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe},
                    .perm = {149,142,120,125,178,21,129,250,26,3,53,180,168,253,218,177,27,30,158,75,32,117,222,56,195,39,69,71,44,160,143,199,201,102,19,251,165,184,154,70,115,249,153,52,28,78,121,220,95,7,183,72,10,107,179,188,57,99,215,144,225,155,47,68,235,37,40,74,136,85,84,55,204,243,202,217,67,187,227,211,174,219,134,233,6,18,77,92,166,24,66,161,14,9,49,192,89,106,98,36,105,13,148,35,79,103,45,186,230,164,65,207,138,203,221,132,175,238,131,111,15,255,212,23,5,46,90,237,198,209,83,150,216,196,76,157,224,254,87,245,34,137,127,152,11,241,130,113,141,171,17,169,173,172,210,234,94,252,206,88,43,12,20,242,41,176,162,2,112,22,247,73,4,29,189,182,240,109,63,228,51,246,123,97,42,140,200,48,33,96,64,236,193,159,151,146,133,1,0,226,139,248,54,118,128,223,163,167,116,58,8,185,25,190,147,108,126,194,59,16,191,244,145,229,170,38,91,124,100,31,81,119,61,231,156,104,86,232,197,205,101,214,60,239,135,82,122,208,80,93,213,110,62,114,181,50},
                    .numOctaves = 6,
                    .amplitude = 1.0f,
                    .frequency = 1.0f,
                    .amplitudeMult = 0.5f,
                    .frequencyMult = 2.0f
            },
            .position = {10000.0, 0.0, 0.0},
            .radius = 2000.0
    };

private:

    Star star {
            .id = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            .lod = DISTANT2,
            .color = {1.5, 1.5, 1.5},
            .position = {0.0, 10000.0, 0.0},
            .radius = 1000.0
    };

    Star star2 {
            .id = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            .lod = DISTANT,
            .color = {3.0, 0.0, 0.0},
            .position = {-30000.0, 0.0, 0.0},
            .radius = 500.0
    };

    Light light {
            .id = {0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            .position = {0.0, 10000.0, 0.0},
            .color = {1.5f, 1.5f, 1.5f}
    };

    Light light2 {
            .id = {0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            .position = {-30000.0, 0.0, 0.0},
            .color = {3.0, 0.0, 0.0}
    };
public:
    Debug debug = {
        .objectsCollide = false
    };

    ShipState ship = {
        .modelState = {
            .pos = {0.0, 0.0, 0.0},
            .dir = {0.0, 0.0, -1.0},
            .up = {0.0, 1.0, 0.0},
            .scale = {1.0, 1.0, 1.0}
        },
        .vel = {0.0, 0.0, 0.0},
        .rollVel = 0.0,
        .turnVel = {0.0, 0.0},
        .boosterState = BOOSTER_OFF,
        .boosterStrength = 0.0
    };

    ModelState island {
        .pos = {0.0, 0.0, 0.0},
        .dir = {0.0f, 0.0f, -1.0},
        .up = {0.0, 1.0, 0.0},
        .scale = {0.001, 0.001, 0.001}
    };

    CameraState camera = {
        .pos = {0.0, 0.0, 10.0},
        .dir = {0.0, 0.0, -1.0},
        .up = {0.0, 1.0, 0.0},
        .viewInverted = false
    };

    PerlinNoise spaceNoise {
            .id = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            .perm = {149,142,120,125,178,21,129,250,26,3,53,180,168,253,218,177,27,30,158,75,32,117,222,56,195,39,69,71,44,160,143,199,201,102,19,251,165,184,154,70,115,249,153,52,28,78,121,220,95,7,183,72,10,107,179,188,57,99,215,144,225,155,47,68,235,37,40,74,136,85,84,55,204,243,202,217,67,187,227,211,174,219,134,233,6,18,77,92,166,24,66,161,14,9,49,192,89,106,98,36,105,13,148,35,79,103,45,186,230,164,65,207,138,203,221,132,175,238,131,111,15,255,212,23,5,46,90,237,198,209,83,150,216,196,76,157,224,254,87,245,34,137,127,152,11,241,130,113,141,171,17,169,173,172,210,234,94,252,206,88,43,12,20,242,41,176,162,2,112,22,247,73,4,29,189,182,240,109,63,228,51,246,123,97,42,140,200,48,33,96,64,236,193,159,151,146,133,1,0,226,139,248,54,118,128,223,163,167,116,58,8,185,25,190,147,108,126,194,59,16,191,244,145,229,170,38,91,124,100,31,81,119,61,231,156,104,86,232,197,205,101,214,60,239,135,82,122,208,80,93,213,110,62,114,181,50},
            .numOctaves = 6,
            .amplitude = 1.0f,
            .frequency = 0.1f,
            .amplitudeMult = 0.5f,
            .frequencyMult = 2.0f
    };

    glm::vec3 ambientLight = {0.068f, 0.04f, 0.088f};

    std::map<boost::uuids::uuid, Planet*> planets = {{planet.id, &planet}, {planet2.id, &planet2}};
    std::map<boost::uuids::uuid, Star*> stars = {{star.id, &star}, {star2.id, &star2}};
    std::map<boost::uuids::uuid, Light*> lights = {{light.id, &light}};
};

#endif //SPACEGAME_GAMESTATE_H
