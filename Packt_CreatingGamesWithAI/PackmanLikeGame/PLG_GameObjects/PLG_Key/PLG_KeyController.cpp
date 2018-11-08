//
//  PLG_KeyController.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 02/11/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_KeyController.hpp"

#include "PLG_Commons.hpp"
#include "BoxCollider.hpp"

#include <vector>

PLG_KeyController::PLG_KeyController(const float pPosX, const float pPosY)
    : GameCharacterController(), mIsDisappeared(false)
{
    mVisual = std::make_unique<PLG_Key>(pPosX, pPosY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::KEY, this, mVisual->getPosition(), glm::vec2(pPosX + mVisual->getWidth(), pPosY + mVisual->getHeight()) );
}

void PLG_KeyController::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mIsDisappeared = false;
    mVisual = std::make_unique<PLG_Key>(posX, posY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::KEY, this, mVisual->getPosition(), glm::vec2(posX + mVisual->getWidth(), posY + mVisual->getHeight()) );
}

PLG_KeyController::~PLG_KeyController()
{
    
}

void PLG_KeyController::reset()
{
    mIsDisappeared = false;
}

void PLG_KeyController::onCollision(const Collider* pObject)
{
    if(pObject->getType() == ePLG_COLLIDER_TYPES::PLAYER)
    {
        mIsDisappeared = true;
    }
}

void PLG_KeyController::callOnRender(std::vector<Texture*>& mTextures)
{
    if( !mIsDisappeared )
    {
        mTextures.push_back(mVisual->getTexture());
    }
}
