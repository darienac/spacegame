//
// Created by dacma on 6/19/2024.
//

#ifndef SPACEGAME_BOXCOLLIDER_H
#define SPACEGAME_BOXCOLLIDER_H


#include "AbstractCollider.h"
#include "glm/detail/type_vec3.hpp"

class BoxCollider: public AbstractCollider {
public:
    glm::dvec3 min;
    glm::dvec3 max;

    BoxCollider(const glm::dvec3 &min, const glm::dvec3 &max);

    [[nodiscard]] LineSegment getBoundsOnAxis(const glm::dvec3 &axis, const glm::dmat4 &transform) const;

    bool collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const override;
    bool collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const override;
    bool collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const override;
};


#endif //SPACEGAME_BOXCOLLIDER_H
