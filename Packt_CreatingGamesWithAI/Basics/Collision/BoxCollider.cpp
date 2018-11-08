//
//  BoxCollider.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "BoxCollider.hpp"

BoxCollider::BoxCollider(const unsigned int pColliderType, GameCharacterController* pOwner)
: Collider(Collider::eINTERNAL_COLLIDER_TYPE::BOX, pColliderType, pOwner)
{
    mMin = glm::vec2(0.f, 0.f);
    mMax = glm::vec2(0.f, 0.f);
}

BoxCollider::BoxCollider(const unsigned int pColliderType, GameCharacterController* pOwner, const glm::vec2& pMin, const glm::vec2& pMax)
: Collider(Collider::eINTERNAL_COLLIDER_TYPE::BOX, pColliderType, pOwner)
{
    mMin = pMin;
    mMax = pMax;
}

BoxCollider::~BoxCollider() {}

const glm::vec2& BoxCollider::getMinPos() const { return mMin; }
const glm::vec2& BoxCollider::getMaxPos() const { return mMax; }
float BoxCollider::getWidth() const { return mMax.x - mMin.x; }
float BoxCollider::getHeight() const { return mMax.y - mMin.y; }
//float BoxCollider::getDepth() const { return mMax[eVECTOR3_INDICES::Z] - mMin[eVECTOR3_INDICES::Z]; }

bool BoxCollider::checkCollision(const Collider* obj) const
{
    auto objMax = obj->getMaxPos();
    auto objMin = obj->getMinPos();
    
    return    ((mMin.x <= objMax.x && mMax.x >= objMin.x) &&
               (mMin.y <= objMax.y && mMax.y >= objMin.y) ); //&&
//               (mMin[eVECTOR3_INDICES::Z] <= objMax[eVECTOR3_INDICES::Z] && mMax[eVECTOR3_INDICES::Z] >= objMin[eVECTOR3_INDICES::Z]));
}

bool BoxCollider::checkCollision(const glm::vec2& point) const
{
    return (
                (point.x >= mMin.x && point.x <= mMax.x) &&
                (point.y >= mMin.y && point.y <= mMax.y)
            ); //&&
    //(point.z >= box.minZ && point.z <= box.maxZ);
}
