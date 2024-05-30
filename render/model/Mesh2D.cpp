//
// Created by dacma on 5/28/2024.
//

#include "Mesh2D.h"

Mesh2D::Mesh2D(const std::vector<GLfloat> &vertices, const std::vector<GLfloat> &texCoords,
               const std::vector<GLint> &faces) {
    verticesBuffer = std::make_unique<GlBuffer>(vertices);
    texCoordBuffer = std::make_unique<GlBuffer>(texCoords);
    facesBuffer = std::make_unique<GlBuffer>(faces);
    numFaceElements = faces.size();
}
