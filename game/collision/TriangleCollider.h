//
// Created by dacma on 6/20/2024.
//

#ifndef SPACEGAME_TRIANGLECOLLIDER_H
#define SPACEGAME_TRIANGLECOLLIDER_H

#include "glm/vec3.hpp"
#include "AbstractCollider.h"

class TriangleCollider: public AbstractCollider {
public:
    glm::dvec3 points[3]{};

    explicit TriangleCollider();
    explicit TriangleCollider(glm::dvec3 *points);

    [[nodiscard]] LineSegment getBoundsOnAxis(const glm::dvec3 &axis, const glm::dmat4 &transform) const;

    [[nodiscard]] bool collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const override;
    [[nodiscard]] bool collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const override;
    [[nodiscard]] bool collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const override;
};


#endif //SPACEGAME_TRIANGLECOLLIDER_H
