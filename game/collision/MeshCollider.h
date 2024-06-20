//
// Created by dacma on 6/20/2024.
//

#ifndef SPACEGAME_MESHCOLLIDER_H
#define SPACEGAME_MESHCOLLIDER_H


#include <memory>
#include "AbstractCollider.h"
#include "GameMesh.h"

class MeshCollider: public AbstractCollider {
private:
    std::vector<TriangleCollider> tris;
    BoxCollider boundingBox;
    std::unique_ptr<MeshCollider> left;
    std::unique_ptr<MeshCollider> right;

public:
    explicit MeshCollider(const GameMesh &mesh);

    bool collidesWith(const AbstractCollider &collider, const glm::dmat4 &transform) const override;
    bool collidesWith(const BoxCollider &collider, const glm::dmat4 &transform) const override;
    bool collidesWith(const TriangleCollider &collider, const glm::dmat4 &transform) const override;
};


#endif //SPACEGAME_MESHCOLLIDER_H
