//
//  PLG_AlarmController.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_AlarmController.hpp"

#include "PLG_Commons.hpp"
#include "BoxCollider.hpp"
#include "PLG_GameWorldInfo.hpp"

#include <vector>

PLG_AlarmController::PLG_AlarmController(const float pPosX, const float pPosY)
: GameCharacterController(), mIsDisappeared(false)
{
    mVisual = std::make_unique<PLG_Alarm>(pPosX, pPosY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::ALARM, this, glm::vec2(pPosX + 1, pPosY), glm::vec2(pPosX + mVisual->getWidth() - 1, pPosY + mVisual->getHeight()) );
}

void PLG_AlarmController::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mIsDisappeared = false;
    mVisual = std::make_unique<PLG_Alarm>(posX, posY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::ALARM, this, mVisual->getPosition(), glm::vec2(posX + mVisual->getWidth(), posY + mVisual->getHeight()) );
}

PLG_AlarmController::~PLG_AlarmController()
{
    
}

void PLG_AlarmController::reset()
{
    mIsDisappeared = false;
}

void PLG_AlarmController::onCollision(const Collider* pObject)
{
    if(pObject->getType() == ePLG_COLLIDER_TYPES::ENEMY && PLG_GameWorldInfo::getInstance().isAlarmOn)
    {
        mIsDisappeared = true;
    }
}

void PLG_AlarmController::callOnRender(std::vector<Texture*>& mTextures)
{
    if( !mIsDisappeared )
    {
        mTextures.push_back(mVisual->getTexture());
    }
}
