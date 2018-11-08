//
//  Collider.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 31/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Collider.hpp"

#include "VisualObject.hpp"

LegacyCollider::LegacyCollider(const unsigned int pColliderType, VisualObject* pOwner)
    : mColliderType(pColliderType), mIsCollided(false), mOwner(pOwner)
{
    mWidth = mOwner->getWidth();
    mHeight = mOwner->getHeight();
}

LegacyCollider::LegacyCollider(const unsigned int pColliderType, VisualObject* pOwner, const int pWidth, const int pHeight)
    : mColliderType(pColliderType), mIsCollided(false), mOwner(pOwner), mWidth(pWidth), mHeight(pHeight)
{

}

glm::vec2 LegacyCollider::getBboxTopLeft() const { return mOwner->getPosition(); }
glm::vec2 LegacyCollider::getBboxDownRight() const
{
    // TODO This does not answer if the owner's size change in run time
    auto pos = mOwner->getPosition() + glm::vec2( mWidth, mHeight );
    return pos;
}

void LegacyCollider::collide(const LegacyCollider* obj) const
{
    mOwner->OnCollision(obj);
}
