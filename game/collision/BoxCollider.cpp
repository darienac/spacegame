//
// Created by dacma on 6/19/2024.
//

#include "BoxCollider.h"
#include "glm/matrix.hpp"

BoxCollider::LineSegment BoxCollider::getBoundsOnAxis(const glm::dvec3 &axis, const glm::dmat4 &transform) const {
    double minPos = glm::dot(glm::dvec3(transform * glm::dvec4(min, 1.0)), axis);
    double maxPos = minPos;
    glm::dvec3 extents[2] = {min, max};
    for (uint8_t i = 0; i < 2; i++) {
        for (uint8_t j = 0; j < 2; j++) {
            for (uint8_t k = 0; k < 2; k++) {
                glm::dvec3 corner = transform * glm::dvec4{extents[i].x, extents[j].y, extents[k].z, 1.0};
                double pos = glm::dot(corner, axis);
                if (pos < minPos) {
                    minPos = pos;
                } else if (pos > maxPos) {
                    maxPos = pos;
                }
            }
        }
    }
    return LineSegment(minPos, maxPos);
}

bool BoxCollider::boxesCollideOnAxis(const glm::dvec3 &axis, const BoxCollider &collider, const glm::dmat4 &transform) const {
    LineSegment span1 = getBoundsOnAxis(axis, glm::dmat4(1.0));
    LineSegment span2 = collider.getBoundsOnAxis(axis, transform);
    return (span1.p1 > span2.p1 && span1.p1 < span2.p2)
        || (span1.p2 > span2.p1 && span1.p2 < span2.p2)
        || (span2.p1 > span1.p1 && span2.p1 < span1.p2)
        || (span2.p2 > span1.p1 && span2.p2 < span1.p2);
}

BoxCollider::BoxCollider(const glm::dvec3 &min, const glm::dvec3 &max): min(min), max(max) {}

bool BoxCollider::collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const {
    return collider.collidesWith(*this, glm::inverse(transform));
}

bool BoxCollider::collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const {
    glm::dvec3 axes[15];
    axes[0] = {1.0, 0.0, 0.0};
    axes[1] = {0.0, 1.0, 0.0};
    axes[2] = {0.0, 0.0, 1.0};
    axes[3] = transform * glm::dvec4(axes[0], 0.0);
    axes[4] = transform * glm::dvec4(axes[1], 0.0);
    axes[5] = transform * glm::dvec4(axes[2], 0.0);
    axes[6] = glm::cross(axes[0], axes[3]);
    axes[7] = glm::cross(axes[0], axes[4]);
    axes[8] = glm::cross(axes[0], axes[5]);
    axes[9] = glm::cross(axes[1], axes[3]);
    axes[10] = glm::cross(axes[1], axes[4]);
    axes[11] = glm::cross(axes[1], axes[5]);
    axes[12] = glm::cross(axes[2], axes[3]);
    axes[13] = glm::cross(axes[2], axes[4]);
    axes[14] = glm::cross(axes[2], axes[5]);

    for (auto &axis : axes) {
        if (!boxesCollideOnAxis(axis, collider, transform)) {
            return false;
        }
    }

    return true;
}

bool BoxCollider::collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const {
    return false;
}
