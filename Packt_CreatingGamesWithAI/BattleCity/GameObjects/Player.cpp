//
//  Player.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Player.hpp"

#include "BattleCityCommons.hpp"
#include "Timer.hpp"
#include "GameEventManager.hpp"
#include "TankMissileManager.hpp"

Player::Player()
    : LegacyGameCharacter(), mFireCoolDown(FIRE_COOL_DOWN_TIME + 1.f)
{
    mTankCharacter = std::make_unique<TankCharacter>(this);
    
    GameEventMngr.addKeyboardCallback(this, &Observer::keyboardEventCallback);
}

Player::~Player()
{
    GameEventMngr.removeKeyboardCallback( getId() );
}

void Player::reset()
{
    mTankCharacter->setPosition(glm::vec2(PLAYER_SPAWN_POINT.x, PLAYER_SPAWN_POINT.y));
}

void Player::keyboardEventCallback(KeyboardEvents pEvent)
{
    if(pEvent.EVENT_TYPE == KeyboardEvents::KEY_DOWN)
    {
        if(pEvent.key == SDLK_LEFT)
        {
            mTankCharacter->moveLeft();
        }
        else if(pEvent.key == SDLK_RIGHT)
        {
            mTankCharacter->moveRight();
        }
        else if(pEvent.key == SDLK_UP)
        {
            mTankCharacter->moveUp();
        }
        else if(pEvent.key == SDLK_DOWN)
        {
            mTankCharacter->moveDown();
        }
    }
    else if(pEvent.EVENT_TYPE == KeyboardEvents::KEY_UP)
    {
        if(pEvent.key == SDLK_UP || pEvent.key == SDLK_DOWN)
        {
            mTankCharacter->stopMoving();
        }
        else if(pEvent.key == SDLK_f)
        {
            handleFiring();
        }
    }
}

void Player::handleFiring()
{
    if( MathCommons::definitelyGreaterThan(mFireCoolDown, FIRE_COOL_DOWN_TIME) )
    {
        mFireCoolDown = 0.f;
        mTankCharacter->fire();
    }
}

void Player::handleCollision(const LegacyCollider* pObj)
{
     if((eTankColliderTypes)pObj->getType() == eTankColliderTypes::eCT_Bullet)
    {
        reset();
    }
}

Texture* Player::getVisual() const
{
    return mTankCharacter->getVisual();
}

LegacyCollider* Player::getCollider() const
{
    return mTankCharacter->getCollider();
}

glm::vec2 Player::getPosition() const
{
    return mTankCharacter->getPosition();
}

glm::vec2 Player::getHeadingVector() const
{
    return mTankCharacter->getHeadingVector();
}

void Player::setPosition(const glm::vec2& pPos)
{
    mTankCharacter->setPosition(pPos);
}

void Player::Update()
{
    if(mFireCoolDown < FIRE_COOL_DOWN_TIME)
    {
        mFireCoolDown += Time.deltaTime;
    }
    
    mTankCharacter->Update();
}
