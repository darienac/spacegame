//
// Created by dacma on 6/19/2024.
//
#include "AbstractCollider.h"
#include "glm/matrix.hpp"

bool AbstractCollider::spansOverlap(const AbstractCollider::LineSegment &span1, const AbstractCollider::LineSegment &span2) {
    return (span1.p1 > span2.p1 && span1.p1 < span2.p2)
           || (span1.p2 > span2.p1 && span1.p2 < span2.p2)
           || (span2.p1 > span1.p1 && span2.p1 < span1.p2)
           || (span2.p2 > span1.p1 && span2.p2 < span1.p2);
}

bool AbstractCollider::collide(const AbstractCollider &collider1, const glm::dmat4 &transform1, const AbstractCollider &collider2,
                               const glm::dmat4 &transform2) {
    glm::dmat4 transform = glm::inverse(transform1) * transform2;
    return collider1.collidesWith(collider2, transform);
}

