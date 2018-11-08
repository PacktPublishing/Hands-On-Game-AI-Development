//
//  TankAI.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankAI.hpp"

#include "BattleCityCommons.hpp"
#include "Timer.hpp"
#include "BC_TankAiFactory.hpp"

TankAI::TankAI(const glm::vec2& pDefultPos)
    : mFireCoolDown(FIRE_COOL_DOWN_TIME + 1.f), mReflexTime(REFLEX_LIMIT + 1.f), mPathTimeLimit(3.f), mLastPathChangeTime(Time.time), mDefultPos(pDefultPos)
{
    mTankCharacter = std::make_unique<TankCharacter>(this, "Images/BattleCity/enemyTank.png");
    mAi = std::make_unique<DecisionTree<TankAI>>(this, BC_TankAiFactory::instantiate(eTANK_AI_TYPES::BASE) );
}

void TankAI::reset()
{
    mTankCharacter->setPosition(mDefultPos);
}

bool TankAI::getIsCollided() const
{
    return mIsCollided;
}

void TankAI::clearIsCollided()
{
    mIsCollided = false;
}

Texture* TankAI::getVisual() const
{
    return mTankCharacter->getVisual();
}

LegacyCollider* TankAI::getCollider() const
{
    return mTankCharacter->getCollider();
}

glm::vec2 TankAI::getPosition() const
{
    return mTankCharacter->getPosition();
}

glm::vec2 TankAI::getHeadingVector() const
{
    return mTankCharacter->getHeadingVector();
}

float TankAI::getLastPathChangeTime() const
{
    return mLastPathChangeTime;
}

float TankAI::getPathTimeLimit() const
{
    return mPathTimeLimit;
}

void TankAI::setLastPathTime(const float time)
{
    mLastPathChangeTime = time;
}

void TankAI::setPosition(const glm::vec2& pPos)
{
    mTankCharacter->setPosition(pPos);
}

TankCommons::eTANK_MOVEMENT TankAI::getCurrentMovement() const
{
    return mTankCharacter->getCurrentMovement();
}

void TankAI::move(const TankCommons::eTANK_MOVEMENT pMovementDecision)
{
    using namespace TankCommons;
    
    if(mReflexTime < REFLEX_LIMIT && !mIsStillMove)
    {
        // Can't make a move
        return;
    }
    
    switch (pMovementDecision)
    {
        case eTANK_MOVEMENT::eTM_UP:
            mTankCharacter->moveUp();
            break;
        case eTANK_MOVEMENT::eTM_DOWN:
            mTankCharacter->moveUp();
            break;
        case eTANK_MOVEMENT::eTM_LEFT:
            mTankCharacter->moveLeft();
            mIsStillMove = true;
            mFutureMove = eTANK_MOVEMENT::eTM_UP;
            break;
        case eTANK_MOVEMENT::eTM_RIGHT:
            mTankCharacter->moveRight();
            mIsStillMove = true;
            mFutureMove = eTANK_MOVEMENT::eTM_UP;
            break;
        case eTANK_MOVEMENT::eTM_NONE:
            mTankCharacter->stopMoving();
        default:
            break;
    }
    
    mReflexTime = 0.f;
}

void TankAI::Update()
{
    if(mFireCoolDown < FIRE_COOL_DOWN_TIME)
    {
        mFireCoolDown += Time.deltaTime;
    }
    
    if(mReflexTime < REFLEX_LIMIT)
    {
        mReflexTime += Time.deltaTime;
    }
    
    if(mIsStillMove)
    {
        move(mFutureMove);
        mIsStillMove = false;
        mFutureMove = TankCommons::eTANK_MOVEMENT::eTM_NONE;
    }
    
    // DecisonTree::decide here!
    mAi->decide();
    
    mTankCharacter->Update();
}

void TankAI::handleCollision(const LegacyCollider* pObj)
{
    if( (eTankColliderTypes)pObj->getType() == eTankColliderTypes::eCT_Wall)
    {
        mIsCollided = true;
    }
    else if((eTankColliderTypes)pObj->getType() == eTankColliderTypes::eCT_Bullet)
    {
        reset();
    }
}

void TankAI::fire()
{
    if( MathCommons::definitelyGreaterThan(mFireCoolDown, FIRE_COOL_DOWN_TIME) )
    {
        mFireCoolDown = 0.f;
        mTankCharacter->fire();
    }
}
