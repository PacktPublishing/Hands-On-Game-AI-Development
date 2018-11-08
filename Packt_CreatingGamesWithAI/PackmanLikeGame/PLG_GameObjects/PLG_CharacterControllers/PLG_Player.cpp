//
//  PLG_Player.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_Player.hpp"

#include "GameEventManager.hpp"
#include "PLG_Commons.hpp"
#include "BoxCollider.hpp"
#include "Timer.hpp"
#include "PLG_GameWorldInfo.hpp"

PLG_Player::PLG_Player()
    : GameCharacterController(), mIsHandleInput(false), mIsInStoppingProcess(false), mDidArrive(false), mPathPositionIndex(-1), mCurrentStopTime(0.f), mTimeToStop(0.f)
{
    mBoundingRadius = 100.f;
    
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::PLAYER, this,  getColliderMin(), getColliderMax() );
    
    GameEventMngr.addMouseCallback(this, &Observer::mouseEventCallback);
    
    mMovingObjectReference = &mCharacter;
    
    mPathPlanner.setOwnner(this);
}

PLG_Player::PLG_Player(const float pPosX, const float pPosY)
    : GameCharacterController(), mIsHandleInput(false), mIsInStoppingProcess(false),  mDidArrive(false), mPathPositionIndex(-1), mCurrentStopTime(0.f), mTimeToStop(0.f)
{
    mBoundingRadius = 100.f;
    
    mCharacter.initObject(2, pPosX, pPosY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::PLAYER, this, getColliderMin(), getColliderMax() );
    
    GameEventMngr.addMouseCallback(this, &Observer::mouseEventCallback);
    
    mMovingObjectReference = &mCharacter;
    
    mPathPlanner.setOwnner(this);
}

void PLG_Player::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mCharacter.initObject(2, posX, posY);
}

void PLG_Player::reset()
{
    mIsHandleInput = false;
    mIsInStoppingProcess = false;
    mDidArrive = false;
    
    mCurrentStopTime = 0.f;
    mTimeToStop = 0.f;
    
    resetPathTracking();
    
    mCharacter.setPosition( glm::vec2(PLAYER_POS_X, PLAYER_POS_Y) );
}

PLG_Player::~PLG_Player()
{
    
}

glm::vec2 PLG_Player::getColliderMin()
{
    auto posX = mCharacter.getPosition().x;
    auto posY = mCharacter.getPosition().y;
    
    return glm::vec2(posX + 1, posY + 1);
}

glm::vec2 PLG_Player::getColliderMax()
{
    auto posX = mCharacter.getPosition().x;
    auto posY = mCharacter.getPosition().y;
    
    return glm::vec2(posX + mCharacter.getWidth() - 1, posY + mCharacter.getHeight() - 1);
}

bool PLG_Player::isAtThePosition(const glm::vec2& pPosI, const glm::vec2& pPosII)
{
    const float epsilon = 100.f;
    auto dist = glm::distance( pPosI, pPosII );
    return ( dist < epsilon );
}

void PLG_Player::callOnFrame()
{
    mCollider->clearCollided();
    
    mLastPos = mCharacter.getPosition();
    
    if(mIsHandleInput)
    {
        handleMovement();
    }
    
    if(mIsInStoppingProcess)
    {
        if( mCurrentStopTime > mTimeToStop)
        {
            mMovingObjectReference->setPosition(mStopPosition);
            mIsInStoppingProcess = false;

            if(mPathPositionIndex < mPathPositions.size())
            {
                // Still way to go
                updateMovementDirection();
            }
            else
            {
                resetPathTracking();
            }
        }
        else
        {
            mCurrentStopTime += Time.deltaTime;
        }
    }
    else
    {
        if(mPathPositionIndex > -1)
        {
            if( isAtThePosition(mPathPositions[mPathPositionIndex], getPosition()) )
            {
                startStoppingProcess(mPathPositions[mPathPositionIndex]);
                mPathPositionIndex++;
            }
        }
    }

    mCharacter.callOnFrame();
    
    mCollider->setMaxPos( getColliderMax() );
    mCollider->setMinPos( getColliderMin() );
}

void PLG_Player::callOnRender(std::vector<Texture*>& mTextures)
{
    mCharacter.callOnRender(mTextures);
}

void PLG_Player::mouseEventCallback(MouseEvents pEvent)
{
    if(pEvent.EVENT_TYPE == MouseEvents::MOUSE_UP)
    {
        mIsHandleInput = true;
        mCommanedPosition = glm::vec2(pEvent.mousePosX, pEvent.mousePosY);
    }
}

void PLG_Player::startStoppingProcess(const glm::vec2& pPosition)
{
    mIsInStoppingProcess = true;
    mCurrentStopTime = 0.f;
    mStopPosition = pPosition;
    mTimeToStop = (glm::distance(mStopPosition, getPosition()) / mCharacter.getDefaultSpeed() );
}

void PLG_Player::resetPathTracking()
{
    mIsInStoppingProcess = false;
    mPathPositionIndex = -1;
    mPathPositions.clear();
    mCharacter.getLocomotion()->clearMovement();
}

void PLG_Player::handleMovement()
{
    mIsHandleInput = false;
    resetPathTracking();
    
    if( mPathPlanner.requestPathToPosition(mCommanedPosition, mPathPositions) )
    {
        mPathPositionIndex = 0;
        updateMovementDirection();
    }
}

void PLG_Player::updateMovementDirection()
{
    auto dir = glm::normalize( mPathPositions[mPathPositionIndex] - getPosition() );
    if(std::fabsf(dir.x) > std::fabsf(dir.y))
    {
        // Left or right
        if(dir.x > MathCommons::EPSILON)
        {
            // Right
            mCharacter.getLocomotion()->setMovement(Locomotion<PLG_CircleCharacter>::eTRANSLATION_DIRECTION::eTD_RIGHT);
        }
        else
        {
            // Left
            mCharacter.getLocomotion()->setMovement(Locomotion<PLG_CircleCharacter>::eTRANSLATION_DIRECTION::eTD_LEFT);
        }
    }
    else
    {
        // Up or down, (or equal)
        if(dir.y > MathCommons::EPSILON)
        {
            // Down
            mCharacter.getLocomotion()->setMovement(Locomotion<PLG_CircleCharacter>::eTRANSLATION_DIRECTION::eTD_BACKWARD);
        }
        else
        {
            // Up
            mCharacter.getLocomotion()->setMovement(Locomotion<PLG_CircleCharacter>::eTRANSLATION_DIRECTION::eTD_FORWARD);
        }
    }
}

void PLG_Player::onCollision(const Collider* pObject)
{
    if(pObject->getType() == ePLG_COLLIDER_TYPES::WALL)
    {
        rewindPosition();
    }
    else if(pObject->getType() == ePLG_COLLIDER_TYPES::ENEMY)
    {
        PLG_GameWorldInfo::getInstance().isPlayerDown = true;
    }
    else if(pObject->getType() == ePLG_COLLIDER_TYPES::KEY)
    {
        PLG_GameWorldInfo::getInstance().isPlayerDown = true;
    }
}

void PLG_Player::rewindPosition()
{
    mCharacter.setPosition(mLastPos);
    
    mCollider->setMaxPos( getColliderMax() );
    mCollider->setMinPos( getColliderMin() );
}
