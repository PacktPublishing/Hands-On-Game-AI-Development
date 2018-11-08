//
//  Wall.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/07/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "Wall.hpp"

#include "BattleCityCommons.hpp"

Wall::Wall(const int posX, const int posY, const std::string& imagePath)
    : VisualObject(posX, posY, TextureCommons::DEFAULT_Z_ORDER, imagePath)
{

    mCollider = std::make_unique<LegacyBoxCollider>((unsigned int)eTankColliderTypes::eCT_Wall, this);
}

Wall::~Wall()
{
    
}

bool Wall::getIsAlive() const
{
    return mIsAlive;
}

LegacyCollider* Wall::getCollider() const
{
    return mCollider.get();
}

void Wall::OnCollision(const LegacyCollider *obj)
{
    // TODO Fill it if you need it
}

