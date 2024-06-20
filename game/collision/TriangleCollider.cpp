//
// Created by dacma on 6/20/2024.
//

#include "TriangleCollider.h"
#include "glm/matrix.hpp"

TriangleCollider::TriangleCollider() = default;

TriangleCollider::TriangleCollider(glm::dvec3 *points) {
    this->points[0] = points[0];
    this->points[1] = points[1];
    this->points[2] = points[2];
}

bool TriangleCollider::collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const {
    return collider.collidesWith(*this, glm::inverse(transform));
}

bool TriangleCollider::collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const {
    return false;
}

bool TriangleCollider::collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const {
    return false;
}