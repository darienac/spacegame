//
// Created by dacma on 6/19/2024.
//
#include "AbstractCollider.h"
#include "glm/matrix.hpp"

bool AbstractCollider::collide(const AbstractCollider &collider1, const glm::dmat4 &transform1, const AbstractCollider &collider2,
                               const glm::dmat4 &transform2) {
    glm::dmat4 transform = glm::inverse(transform1) * transform2;
    return collider1.collidesWith(collider2, transform);
}

