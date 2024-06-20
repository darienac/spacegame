//
// Created by dacma on 6/20/2024.
//

#include "MeshCollider.h"
#include "glm/geometric.hpp"

MeshCollider::MeshCollider(const GameMesh &mesh): boundingBox(mesh.getBoundingBox()) {
    if (mesh.getTris().size() <= 8) {
        tris = mesh.getTris();
        return;
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
    });
    double totalSurfaceArea = 0.0;
    double halfSurfaceArea = 0.0;
    for (auto &tri : sortedTris) {
        totalSurfaceArea += glm::length(glm::cross(tri.points[2] - tri.points[0], tri.points[1] - tri.points[0]));
    }
    uint32_t i = 0;
    for (i = 0; i < sortedTris.size(); i++) {
        auto &tri = sortedTris[i];
        halfSurfaceArea += glm::length(glm::cross(tri.points[2] - tri.points[0], tri.points[1] - tri.points[0]));
        if (halfSurfaceArea >= totalSurfaceArea * 0.5) {
            break;
        }
    }
    if (i == 0) { // prevent infinite recursion
        i++;
    }
    std::vector<TriangleCollider> firstTris(sortedTris.begin(), sortedTris.begin() + i);
    std::vector<TriangleCollider> lastTris(sortedTris.begin() + i, sortedTris.end());

    left = std::make_unique<MeshCollider>(GameMesh(firstTris));
    right = std::make_unique<MeshCollider>(GameMesh(lastTris));
}

bool MeshCollider::collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const {
    if (tris.empty()) {
        return collider.collidesWith(*left, transform) || collider.collidesWith(*right, transform);
    }
    return false;
}

bool MeshCollider::collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const {
    return false;
}

bool MeshCollider::collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const {
    return false;
}
