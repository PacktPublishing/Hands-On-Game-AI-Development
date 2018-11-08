//
//  PLG_CircleLocomotion.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 28/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_CircleLocomotion.hpp"

#include "Timer.hpp"

PLG_CircleLocomotion::PLG_CircleLocomotion()
    : Locomotion()
{ }

PLG_CircleLocomotion::PLG_CircleLocomotion(PLG_CircleCharacter* pOwner)
    : Locomotion(pOwner)
{ }

void PLG_CircleLocomotion::applyRotation()
{ }

void PLG_CircleLocomotion::applyTranslation()
{
    switch (mTranslationDirection)
    {
        case eTRANSLATION_DIRECTION::eTD_FORWARD:
            moveUp();
            break;
        case eTRANSLATION_DIRECTION::eTD_BACKWARD:
            moveDown();
            break;
        case eTRANSLATION_DIRECTION::eTD_LEFT:
            moveLeft();
            break;
        case eTRANSLATION_DIRECTION::eTD_RIGHT:
            moveRight();
            break;
        default:
            break;
    }
}

void PLG_CircleLocomotion::moveUp()
{
    auto currentPos = mOwner->getPosition();
    currentPos.y = currentPos.y - (mOwner->getDefaultSpeed() * Time.deltaTime);
    mOwner->setPosition(currentPos);
    
    mOwner->setHeadingVector(0, -1.f);
}

void PLG_CircleLocomotion::moveDown()
{
    auto currentPos = mOwner->getPosition();
    currentPos.y = currentPos.y + (mOwner->getDefaultSpeed() * Time.deltaTime);
    mOwner->setPosition(currentPos);
    
    mOwner->setHeadingVector(0, 1.f);
}

void PLG_CircleLocomotion::moveLeft()
{
    auto currentPos = mOwner->getPosition();
    currentPos.x = currentPos.x - (mOwner->getDefaultSpeed() * Time.deltaTime);
    mOwner->setPosition(currentPos);
    
    mOwner->setHeadingVector(-1.f, 0.f);
}

void PLG_CircleLocomotion::moveRight()
{
    auto currentPos = mOwner->getPosition();
    currentPos.x = currentPos.x + (mOwner->getDefaultSpeed() * Time.deltaTime);
    mOwner->setPosition(currentPos);
    
     mOwner->setHeadingVector(1.f, 0.f);
}
