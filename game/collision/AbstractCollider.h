//
// Created by dacma on 6/19/2024.
//

#ifndef SPACEGAME_ABSTRACTCOLLIDER_H
#define SPACEGAME_ABSTRACTCOLLIDER_H

#include "glm/fwd.hpp"

class BoxCollider;
class TriangleCollider;

class AbstractCollider {
public:
    static bool collide(const AbstractCollider &collider1, const glm::dmat4 &transform1, const AbstractCollider &collider2, const glm::dmat4 &transform2);

    [[nodiscard]] virtual bool collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const = 0;
    [[nodiscard]] virtual bool collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const = 0;
    [[nodiscard]] virtual bool collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const = 0;
};

#endif //SPACEGAME_ABSTRACTCOLLIDER_H