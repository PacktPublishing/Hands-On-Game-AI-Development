//
//  ExplosionAnimation.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "ExplosionAnimation.hpp"

ExplosionAnimation::ExplosionAnimation()
    : AnimateTexture( 3, 0.75f, 32, 32, "Images/BattleCity/explosion.png", false )
{
    
}

ExplosionAnimation::ExplosionAnimation(const glm::vec2& pPosition)
    : AnimateTexture( 3, 0.75f, 32, 32, pPosition.x, pPosition.y, "Images/BattleCity/explosion.png", false )
{
    
}

ExplosionAnimation::~ExplosionAnimation()
{
    
}

void ExplosionAnimation::getReady(const glm::vec2& pPosition)
{
    setPosition(pPosition);
}
