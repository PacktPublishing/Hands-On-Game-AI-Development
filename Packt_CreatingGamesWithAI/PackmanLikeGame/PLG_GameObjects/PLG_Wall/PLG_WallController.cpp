//
//  PLG_WallController.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 23/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_WallController.hpp"

#include "BoxCollider.hpp"
#include "PLG_Commons.hpp"

#include <vector>

PLG_WallController::PLG_WallController(const int posX, const int posY)
    : GameCharacterController()
{
    mVisual = std::make_unique<PLG_Wall>(posX, posY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::WALL, this, mVisual->getPosition(), glm::vec2(posX + mVisual->getWidth(), posY + mVisual->getHeight()) );
}

void PLG_WallController::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mVisual = std::make_unique<PLG_Wall>(posX, posY);
    mCollider = std::make_unique<BoxCollider>(ePLG_COLLIDER_TYPES::WALL, this, mVisual->getPosition(), glm::vec2(posX + mVisual->getWidth(), posY + mVisual->getHeight()) );
}

PLG_WallController::~PLG_WallController()
{
    
}

void PLG_WallController::callOnFrame()
{
    mCollider->clearCollided();
}

void PLG_WallController::callOnRender(std::vector<Texture*>& mTextures)
{
    mTextures.push_back(mVisual->getTexture());
}
