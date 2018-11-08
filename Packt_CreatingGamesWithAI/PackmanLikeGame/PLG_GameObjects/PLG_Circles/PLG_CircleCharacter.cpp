//
//  CircleCharacter.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 24/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_CircleCharacter.hpp"

#include <vector>

#include "PLG_Commons.hpp"
#include "PLG_CircleLocomotion.hpp"

PLG_CircleCharacter::PLG_CircleCharacter()
    : GameCharacter()
{
    mSpeed = CIRCLE_CHARACTER_SPEED;
    
    mLocomotion = std::make_unique<PLG_CircleLocomotion>(this);
}

PLG_CircleCharacter::~PLG_CircleCharacter()
{
    
}

void PLG_CircleCharacter::callOnFrame()
{
    mLocomotion->callOnFrame();
}

void PLG_CircleCharacter::callOnRender(std::vector<Texture*>& mTextures)
{
    mTextures.push_back(mTexture.get());
}

