//
// Created by dacma on 6/20/2024.
//

#include "TriangleCollider.h"
#include "BoxCollider.h"
#include "glm/matrix.hpp"

TriangleCollider::TriangleCollider() = default;

TriangleCollider::TriangleCollider(glm::dvec3 *points) {
    this->points[0] = points[0];
    this->points[1] = points[1];
    this->points[2] = points[2];
}

AbstractCollider::LineSegment TriangleCollider::getBoundsOnAxis(const glm::dvec3 &axis, const glm::dmat4 &transform) const {
    double p1 = glm::dot(glm::dvec3(transform * glm::dvec4(points[0], 1.0)), axis);
    double p2 = glm::dot(glm::dvec3(transform * glm::dvec4(points[1], 1.0)), axis);
    double p3 = glm::dot(glm::dvec3(transform * glm::dvec4(points[2], 1.0)), axis);
    return LineSegment(glm::min(glm::min(p1, p2), p3), glm::max(glm::max(p1, p2), p3));
}

bool TriangleCollider::collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const {
    return collider.collidesWith(*this, glm::inverse(transform));
}

bool TriangleCollider::collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const {
    return collider.collidesWith(*this, glm::inverse(transform));
}

bool TriangleCollider::collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const {
    glm::dvec3 t0p0 = points[0];
    glm::dvec3 t0p1 = points[1];
    glm::dvec3 t0p2 = points[2];

    glm::dvec3 t0v0 = t0p1 - t0p0;
    glm::dvec3 t0v1 = t0p2 - t0p1;
    glm::dvec3 t0v2 = t0p0 - t0p2;

    glm::dvec3 t1p0 = collider.points[0];
    glm::dvec3 t1p1 = collider.points[1];
    glm::dvec3 t1p2 = collider.points[2];

    glm::dvec3 t1v0 = t0p1 - t0p0;
    glm::dvec3 t1v1 = t0p2 - t0p1;
    glm::dvec3 t1v2 = t0p0 - t0p2;

    glm::dvec3 axes[11];
    axes[0] = glm::cross(t0v0, t0v1);
    axes[1] = glm::cross(t1v0, t1v1);
    axes[2] = glm::cross(t0v0, t1v0);
    axes[3] = glm::cross(t0v0, t1v1);
    axes[4] = glm::cross(t0v0, t1v2);
    axes[5] = glm::cross(t0v1, t1v0);
    axes[6] = glm::cross(t0v1, t1v1);
    axes[7] = glm::cross(t0v1, t1v2);
    axes[8] = glm::cross(t0v2, t1v0);
    axes[9] = glm::cross(t0v2, t1v1);
    axes[10] = glm::cross(t0v2, t1v2);

    for (auto &axis : axes) {
        LineSegment span1 = getBoundsOnAxis(axis, glm::dmat4(1.0));
        LineSegment span2 = collider.getBoundsOnAxis(axis, transform);
        if (!spansOverlap(span1, span2)) {
            return false;
        }
    }

    return true;
}
