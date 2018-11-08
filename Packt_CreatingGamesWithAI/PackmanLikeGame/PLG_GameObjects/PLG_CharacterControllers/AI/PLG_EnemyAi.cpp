//
//  PLG_EnemyAi.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 01/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_EnemyAi.hpp"
#include "PLG_Commons.hpp"
#include "BoxCollider.hpp"
#include "PLG_GameWorldInfo.hpp"
#include "Timer.hpp"

PLG_EnemyAi::PLG_EnemyAi()
    : GameCharacterController(), mDoesHavePositionTarget(false), mCanSeePlayer(false), mIsPlayerClose(false), mIsAlarmed(false),
      mIsInStoppingProcess(false), mPathPositionIndex(-1), mTimeToStop(0.f), mCurrentStopTime(0.f), mDecisionTimeLimit(0.3f), mCurrentDecisionTime(0.f)
{
    mBoundingRadius = 100.f;
    
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::ENEMY, this,  getColliderMin(), getColliderMax() );
    
    mStateMachine.initObject(1, this);
    mStateMachine.changeState(&mWanderingState);
    
    mMovingObjectReference = &mCharacter;
    
    mPathPlanner.setOwnner(this);
}

PLG_EnemyAi::PLG_EnemyAi(const float pPosX, const float pPosY)
    : GameCharacterController(), mDoesHavePositionTarget(false), mCanSeePlayer(false), mIsPlayerClose(false), mIsAlarmed(false),
      mIsInStoppingProcess(false), mPathPositionIndex(-1), mTimeToStop(0.f), mCurrentStopTime(0.f), mDecisionTimeLimit(0.3f), mCurrentDecisionTime(0.f)
{
    mBoundingRadius = 100.f;
    
    mCharacter.initObject(2, pPosX, pPosY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::ENEMY, this, getColliderMin(), getColliderMax() );

    mStateMachine.initObject(1, this);
    mStateMachine.changeState(&mWanderingState);

    mCharacter.initObject(2, pPosX, pPosY);
    
    mMovingObjectReference = &mCharacter;
    
    mPathPlanner.setOwnner(this);
}

void PLG_EnemyAi::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mCharacter.initObject(2, posX, posY);
    
    mCollider->setMaxPos( getColliderMax() );
    mCollider->setMinPos( getColliderMin() );
}

void PLG_EnemyAi::reset()
{
    mDoesHavePositionTarget = false;
    mCanSeePlayer = false;
    mIsPlayerClose = false;
    mIsAlarmed = false;
    mIsInStoppingProcess = false;
    
    mTimeToStop = 0.f;
    mCurrentStopTime = 0.f;
    
    resetPathTracking();
    changeState(eENEMY_STATES::eES_WanderAround);
}

glm::vec2 PLG_EnemyAi::getColliderMin()
{
    auto posX = mCharacter.getPosition().x;
    auto posY = mCharacter.getPosition().y;
    
    return glm::vec2(posX + 1, posY + 1);
}

glm::vec2 PLG_EnemyAi::getColliderMax()
{
    auto posX = mCharacter.getPosition().x;
    auto posY = mCharacter.getPosition().y;
    
    return glm::vec2(posX + mCharacter.getWidth() - 1, posY + mCharacter.getHeight() - 1);
}

void PLG_EnemyAi::changeState(const eENEMY_STATES pNewStateRequest)
{
    switch (pNewStateRequest)
    {
        case eENEMY_STATES::eES_WanderAround:
            mStateMachine.changeState(&mWanderingState);
            break;
        case eENEMY_STATES::eES_SearchPlayer:
            mStateMachine.changeState(&mSearchPlayerState);
            break;
        case eENEMY_STATES::eES_AlarmOthers:
            mStateMachine.changeState(&mAlarmOthersState);
            break;
    }
}

void PLG_EnemyAi::callOnFrame()
{
    mCollider->clearCollided();
    
    mLastPos = mCharacter.getPosition();
    
    monitorSelf();
    
    mStateMachine.callOnFrame();
    
    mCharacter.callOnFrame();
    
    mCollider->setMaxPos( getColliderMax() );
    mCollider->setMinPos( getColliderMin() );
}

void PLG_EnemyAi::callOnRender(std::vector<Texture*>& mTextures)
{
    mCharacter.callOnRender(mTextures);
}

void PLG_EnemyAi::onCollision(const Collider* pObject)
{
    if(pObject->getType() == ePLG_COLLIDER_TYPES::WALL)
    {
        rewindPosition();
    }
    else if(pObject->getType() == ePLG_COLLIDER_TYPES::ALARM && isPlayerSeen() )
    {
        PLG_GameWorldInfo::getInstance().isAlarmOn = true;
    }
}

void PLG_EnemyAi::chooseNewRandomPath()
{
    resetPathTracking();
    if( mPathPlanner.requestRandomPath(mPathPositions) )
    {
        handleMovement();
    }
}

void PLG_EnemyAi::setPathToAlarm()
{
    resetPathTracking();
    if( mPathPlanner.requestPathToPosition(PLG_GameInfo.alarmPosition, mPathPositions) )
    {
        handleMovement();
    }
}

void PLG_EnemyAi::setPathToPlayer()
{
    resetPathTracking();
    if( mPathPlanner.requestPathToPosition(PLG_GameInfo.playerPosition, mPathPositions) )
    {
        handleMovement();
    }
}

void PLG_EnemyAi::resetPathTracking()
{
    mIsInStoppingProcess = false;
    mPathPositionIndex = -1;
    mPathPositions.clear();
    mCharacter.getLocomotion()->clearMovement();
}

void PLG_EnemyAi::handleMovement()
{
    mPathPositionIndex = 0;
    updateMovementDirection();
}

void PLG_EnemyAi::updateMovementDirection()
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

void PLG_EnemyAi::monitorSelf()
{
    if(PLG_GameWorldInfo::getInstance().isAlarmOn)
    {
        mIsAlarmed = true;
    }
    
    if(mPathPositions.empty())
    {
        mDoesHavePositionTarget = false;
    }
    else if( !mDoesHavePositionTarget )
    {
        mDoesHavePositionTarget = true;
    }
    
    // Check whether the agent sees the player
    auto dirToPlayer = glm::normalize( ( PLG_GameInfo.playerPosition - mCharacter.getPosition() ) );
    auto dot = glm::dot(dirToPlayer, mCharacter.getHeadingVector() );
    if( glm::distance(PLG_GameInfo.playerPosition, mCharacter.getPosition()) < (WINDOW_WIDTH / 2) &&  MathCommons::definitelyGreaterThan(dot, 0.98f) )
    {
        mCanSeePlayer = true;
    }
    
    if(mCanSeePlayer && glm::distance(PLG_GameInfo.playerPosition, mCharacter.getPosition() ) < 200.f)
    {
        mIsPlayerClose = true;
    }
    else if(mIsPlayerClose)
    {
        mIsPlayerClose = false;
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
}

void PLG_EnemyAi::startStoppingProcess(const glm::vec2& pPosition)
{
    mIsInStoppingProcess = true;
    mCurrentStopTime = 0.f;
    mStopPosition = pPosition;
    mTimeToStop = (glm::distance(mStopPosition, getPosition()) / mCharacter.getDefaultSpeed() );
}

bool PLG_EnemyAi::isAtThePosition(const glm::vec2& pPosI, const glm::vec2& pPosII)
{
    const float epsilon = 100.f;
    auto dist = glm::distance( pPosI, pPosII );
    return ( dist < epsilon );
}

void PLG_EnemyAi::rewindPosition()
{
    mCharacter.setPosition(mLastPos);
    
    mCollider->setMaxPos( getColliderMax() );
    mCollider->setMinPos( getColliderMin() );
}
