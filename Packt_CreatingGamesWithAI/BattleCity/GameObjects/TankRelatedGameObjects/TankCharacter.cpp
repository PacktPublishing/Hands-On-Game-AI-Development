//
//  TankCharacter.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankCharacter.hpp"

#include "BattleCityCommons.hpp"
#include "TankMissileManager.hpp"

using namespace TankCommons;

TankCharacter::TankCharacter(LegacyGameCharacter* const pOwner, const std::string& pTexturePath)
: mMovementDecision(eTANK_MOVEMENT::eTM_NONE), mOwner(pOwner)
{
    mTank = std::make_unique<Tank>(this, pTexturePath);
    mLocomotion.setObject(mTank.get());
}

Texture* TankCharacter::getVisual() const
{
    return mTank->getTexture();
}

LegacyCollider* TankCharacter::getCollider() const
{
    return mTank->getCollider();
}

glm::vec2 TankCharacter::getPosition() const
{
    return mTank->getPosition();
}

glm::vec2 TankCharacter::getHeadingVector() const
{
    return mTank->getHeadingVector();
}

TankCommons::eTANK_MOVEMENT TankCharacter::getCurrentMovement() const
{
    return mMovementDecision;
}

LegacyGameCharacter* const TankCharacter::getOwner() const
{
    return mOwner;
}

void TankCharacter::setPosition(const glm::vec2& pPos)
{
    mTank->setPosition(pPos);
}

void TankCharacter::moveLeft()
{
    mMovementDecision = eTANK_MOVEMENT::eTM_LEFT;
}

void TankCharacter::moveRight()
{
    mMovementDecision = eTANK_MOVEMENT::eTM_RIGHT;
}

void TankCharacter::moveUp()
{
     mMovementDecision = eTANK_MOVEMENT::eTM_UP;
}

void TankCharacter::moveDown()
{
    mMovementDecision = eTANK_MOVEMENT::eTM_DOWN;
}

void TankCharacter::stopMoving()
{
    mMovementDecision = eTANK_MOVEMENT::eTM_NONE;
}

void TankCharacter::fire()
{
    TankMissileManager::getInstance().requestMissile( mTank->getPosition(), mTank->getHeadingVector()) ;
    
    // Calculate position after missile resilience.
    mTank->setPosition(mTank->getPosition() + (mTank->getVelocity() * MISSILE_RESILIENCE * -1.f));
    
}

void TankCharacter::Update()
{
    switch (mMovementDecision)
    {
        case eTANK_MOVEMENT::eTM_UP:
            mLocomotion.moveForward();
            break;
        case eTANK_MOVEMENT::eTM_DOWN:
            mLocomotion.moveBackward();
            break;
        case eTANK_MOVEMENT::eTM_LEFT:
        {
            mLocomotion.turnLeft();
            mMovementDecision = eTANK_MOVEMENT::eTM_NONE;
        }
            break;
        case eTANK_MOVEMENT::eTM_RIGHT:
        {
            mLocomotion.turnRight();
            mMovementDecision = eTANK_MOVEMENT::eTM_NONE;
        }
            break;
        default:
            break;
    }
}

void TankCharacter::handleCollision(const LegacyCollider* pObj)
{
    mOwner->handleCollision(pObj);
}
