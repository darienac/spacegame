//
// Created by dacma on 4/30/2024.
//

#ifndef SPACEGAME_GAMESTATE_H
#define SPACEGAME_GAMESTATE_H

#include "../render/Camera.h"

class GameState {
public:
    struct CameraState {
        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;
    };

    CameraState camera = {
        .pos = {0.0f, 0.0f, 10.0f},
        .dir = {0.0f, 0.0f, -1.0f},
        .up = {0.0f, 1.0f, 0.0f}
    };
};

#endif //SPACEGAME_GAMESTATE_H
