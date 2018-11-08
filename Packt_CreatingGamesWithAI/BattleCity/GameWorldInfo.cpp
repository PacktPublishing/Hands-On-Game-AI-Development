//
//  GameWorldInfo.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 06/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "GameWorldInfo.hpp"

GameWorldInfo& GameWorldInfo::getInstance()
{
    static GameWorldInfo instance;
    return instance;
}

GameWorldInfo::GameWorldInfo()
{
    
}

GameWorldInfo::~GameWorldInfo()
{
    aiPositions.clear();
}
