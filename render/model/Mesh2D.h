//
// Created by dacma on 5/28/2024.
//

#ifndef SPACEGAME_MESH2D_H
#define SPACEGAME_MESH2D_H


#include <memory>
#include "../GlBuffer.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Mesh2D {
public:
    std::unique_ptr<GlBuffer> verticesBuffer;
    std::unique_ptr<GlBuffer> texCoordBuffer;
    std::unique_ptr<GlBuffer> facesBuffer;
    GLsizeiptr numFaceElements;

    Mesh2D(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &texCoords,
           const std::vector<GLint> &faces);
};


#endif //SPACEGAME_MESH2D_H
