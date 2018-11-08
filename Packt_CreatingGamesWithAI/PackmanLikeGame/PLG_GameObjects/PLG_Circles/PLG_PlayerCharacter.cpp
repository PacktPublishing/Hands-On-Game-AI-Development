//
//  PLG_PlayerCharacter.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_PlayerCharacter.hpp"

#include "Commons.hpp"

PLG_PlayerCharacter::PLG_PlayerCharacter()
    : PLG_CircleCharacter()
{
    mSpeed = 80.f;
}

PLG_PlayerCharacter::~PLG_PlayerCharacter()
{ }

void PLG_PlayerCharacter::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);
    
    mPosition.x = posX;
    mPosition.y = posY;
    
    mTexture->init(mPosition.x, mPosition.y, TextureCommons::DEFAULT_Z_ORDER, 0.f, "Images/PacmanLikeGame/player.png");
}
