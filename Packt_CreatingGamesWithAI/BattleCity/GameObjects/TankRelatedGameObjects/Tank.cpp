//
//  Tank.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 18/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Tank.hpp"

#include "BattleCityCommons.hpp"
#include "TankCommons.hpp"
#include "Timer.hpp"

#include <cmath>

Tank::Tank(LegacyGameCharacter* const pOwner, const std::string& pImagePath)
    :   MovingObject(PLAYER_SPAWN_POINT.x, PLAYER_SPAWN_POINT.y, TextureCommons::DEFAULT_Z_ORDER, pImagePath),
        mCanMoveForward(true), mCanMoveBackward(true), mOwner(pOwner)
{
    mRotationAngle = mTexture->getRotation();
    mSpeed = MAX_TANK_SPEED;
    
    mCollider = std::make_unique<LegacyBoxCollider>((unsigned int)eTankColliderTypes::eCT_Tank, this);
}

Tank::Tank(LegacyGameCharacter* const pOwner, const float pPosX, const float pPosY, const float startRotationAngle, const std::string& pImagePath)
    :   MovingObject(pPosX, pPosY, TextureCommons::DEFAULT_Z_ORDER, pImagePath),
        mCanMoveForward(true), mCanMoveBackward(true), mOwner(pOwner)
{
    mRotationAngle = mTexture->getRotation();
    mSpeed = MAX_TANK_SPEED;
    
    mCollider = std::make_unique<LegacyBoxCollider>((unsigned int)eTankColliderTypes::eCT_Tank, this);
}

Tank::~Tank()
{
    
}

bool Tank::canMoveForward() const { return mCanMoveForward; }
bool Tank::canMoveBackward() const { return mCanMoveBackward; }

LegacyCollider* Tank::getCollider() const { return mCollider.get(); }

void Tank::OnCollision(const LegacyCollider *obj)
{
    if( (eTankColliderTypes)obj->getType() == eTankColliderTypes::eCT_Wall)
    {
        bounceBack(obj);
    }
    
    mOwner->handleCollision(obj);
}

void Tank::bounceBack(const LegacyCollider *obj)
{
    checkForBlock(obj);
    
    if( !canMoveForward() )
    {
        mPosition = mPosition + (mVelocity * mSpeed * Time.deltaTime * TankCommons::SAFE_COLLISION_DISTANCE);
        mCanMoveForward = true;
    }
    
    if( !canMoveBackward() )
    {
        mPosition = mPosition - (mVelocity * mSpeed * Time.deltaTime * TankCommons::SAFE_COLLISION_DISTANCE);
        mCanMoveBackward = true;
    }
}

void Tank::increaseRotation(const float pAngleDegrees)
{
    mRotationAngle += pAngleDegrees;
    mTexture->setRotation(mRotationAngle);
    setHeadingVector(pAngleDegrees);
}

void Tank::decreaseRotation(const float pAngleDegrees)
{
    increaseRotation(-pAngleDegrees);
}

void Tank::checkForBlock(const LegacyCollider* obj)
{
    if( MathCommons::definitelyGreaterThan( std::fabsf(this->mHeadingVector.y), MathCommons::EPSILON)  )
    {
        // Going on Y direction
        if( MathCommons::definitelyGreaterThan( this->mHeadingVector.y, -1.f ) )
        {
            // Heading north
            if( MathCommons::definitelyLessThan(obj->getBboxTopLeft().y, this->mPosition.y) )
            {
                mCanMoveForward = false;
            }
            else if( MathCommons::definitelyLessThan(this->mPosition.y, obj->getBboxDownRight().y) )
            {
                mCanMoveBackward = false;
            }
            
        }
        else
        {
            // Heading south
            if( MathCommons::definitelyLessThan(obj->getBboxTopLeft().y, this->mPosition.y) )
            {
                mCanMoveBackward = false;
            }
            else if( MathCommons::definitelyGreaterThan(obj->getBboxDownRight().y, this->mPosition.y ) )
            {
                mCanMoveForward = false;
            }
        }
    }
    else if( MathCommons::definitelyGreaterThan( std::fabsf(this->mHeadingVector.x), MathCommons::EPSILON)  )
    {
        // Going on X direction
        if( MathCommons::definitelyGreaterThan( this->mHeadingVector.x, -1.f ) )
        {
            if( MathCommons::definitelyLessThan(obj->getBboxTopLeft().x, this->mPosition.x) )
            {
                mCanMoveForward = false;
            }
            else if( MathCommons::definitelyGreaterThan(obj->getBboxTopLeft().x, this->mPosition.x) )
            {
                mCanMoveBackward = false;
            }
        }
        else
        {
            if( MathCommons::definitelyLessThan(obj->getBboxTopLeft().x, this->mPosition.x) )
            {
                mCanMoveBackward = false;
            }
            else if( MathCommons::definitelyGreaterThan(obj->getBboxDownRight().x, this->mPosition.x) )
            {
                mCanMoveForward = false;
            }
        }
    }
}
