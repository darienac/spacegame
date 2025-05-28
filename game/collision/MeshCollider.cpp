//
// Created by dacma on 6/20/2024.
//

#include <stdexcept>
#include <iostream>
#include "MeshCollider.h"
#include "glm/geometric.hpp"
#include "glm/matrix.hpp"

MeshCollider::MeshCollider(const GameMesh &mesh): boundingBox(mesh.getBoundingBox()) {
    if (mesh.getTris().size() <= 4) {
        tris = mesh.getTris();
        return;
    } else {
        tris.clear();
    }
    glm::dvec3 bounds = mesh.getBoundingBox().max - mesh.getBoundingBox().min;
    uint8_t maxDim;
    if (bounds.x > bounds.y && bounds.x > bounds.z) {
        maxDim = 0;
    } else if (bounds.y > bounds.x && bounds.y > bounds.z) {
        maxDim = 1;
    } else {
        maxDim = 2;
    }
    std::vector<TriangleCollider> sortedTris = mesh.getTris();
    std::sort(sortedTris.begin(), sortedTris.end(), [&maxDim](auto &a, auto &b) {
        return a.points[0][maxDim] + a.points[1][maxDim] + a.points[2][maxDim] < b.points[0][maxDim] + b.points[1][maxDim] + b.points[2][maxDim];
//        return glm::max(glm::max(a.points[0][maxDim], a.points[1][maxDim]), a.points[2][maxDim]) < glm::max(glm::max(b.points[0][maxDim], b.points[1][maxDim]), b.points[2][maxDim]);
    });
    double totalSurfaceArea = 0.0;
    double halfSurfaceArea = 0.0;
    for (auto &tri : sortedTris) {
        totalSurfaceArea += glm::length(glm::cross(tri.points[2] - tri.points[0], tri.points[1] - tri.points[0]));
    }
    uint32_t i;
    for (i = 0; i < sortedTris.size(); i++) {
        auto &tri = sortedTris[i];
        halfSurfaceArea += glm::length(glm::cross(tri.points[2] - tri.points[0], tri.points[1] - tri.points[0]));
        if (halfSurfaceArea >= totalSurfaceArea * 0.5) {
            break;
        }
    }
    if (i == 0) { // prevent infinite recursion
        i = 1;
    }
    std::vector<TriangleCollider> firstTris(sortedTris.begin(), sortedTris.begin() + i);
    std::vector<TriangleCollider> lastTris(sortedTris.begin() + i, sortedTris.end());

    left = std::make_unique<MeshCollider>(GameMesh(firstTris));
    right = std::make_unique<MeshCollider>(GameMesh(lastTris));
}

bool MeshCollider::collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const {
    if (!boundingBox.collidesWith(collider, transform)) {
        return false;
    }
    if (tris.empty()) {
        return collider.collidesWith(*left, glm::inverse(transform)) || collider.collidesWith(*right, glm::inverse(transform));
    }
    for (auto &tri : tris) {
        if (tri.collidesWith(collider, transform)) {
            return true;
        }
    }
    return false;
}

bool MeshCollider::collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const {
    return collidesWith((AbstractCollider&) collider, transform);
}

bool MeshCollider::collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const {
    return collidesWith((AbstractCollider&) collider, transform);
}

const std::vector<TriangleCollider> &MeshCollider::getTris() const {
    return tris;
}

const BoxCollider &MeshCollider::getBoundingBox() const {
    return boundingBox;
}

const MeshCollider &MeshCollider::getLeft() const {
    return *left;
}

const MeshCollider &MeshCollider::getRight() const {
    return *right;
}
