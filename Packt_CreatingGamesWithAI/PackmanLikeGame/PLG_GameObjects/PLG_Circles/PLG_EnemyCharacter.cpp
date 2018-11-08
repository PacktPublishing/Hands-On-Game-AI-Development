//
//  PLG_EnemyCharacter.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_EnemyCharacter.hpp"

#include "Commons.hpp"

PLG_EnemyCharacter::PLG_EnemyCharacter()
: PLG_CircleCharacter()
{
    mSpeed = 85.f;
}

PLG_EnemyCharacter::~PLG_EnemyCharacter()
{ }

void PLG_EnemyCharacter::performInit(const int pArgNumber, va_list args)
{
    float posX = va_arg(args, double);
    float posY = va_arg(args, double);

    mTexture->init(posX, posY, TextureCommons::DEFAULT_Z_ORDER, 0.f, "Images/PacmanLikeGame/enemy.png");
    
    mPosition = mTexture->getPosition();
}
