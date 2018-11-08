//
//  PLG_GameWorldInfo.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 10/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_GameWorldInfo.hpp"

PLG_GameWorldInfo& PLG_GameWorldInfo::getInstance()
{
    static PLG_GameWorldInfo instance;
    return instance;
}

PLG_GameWorldInfo::PLG_GameWorldInfo()
{
    
}

PLG_GameWorldInfo::~PLG_GameWorldInfo()
{

}
