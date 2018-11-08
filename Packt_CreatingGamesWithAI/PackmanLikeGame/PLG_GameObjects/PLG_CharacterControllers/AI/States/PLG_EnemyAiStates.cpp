//
//  PLG_EnemyAiStates.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 01/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_EnemyAiStates.hpp"

#include "PLG_EnemyAi.hpp"
#include "PLG_GameWorldInfo.hpp"

void PLG_EnemyWanderingState::onExecute(PLG_EnemyAi *pAgent)
{
    if(pAgent->isAlarmed())
    {
        pAgent->changeState(PLG_EnemyAi::eENEMY_STATES::eES_SearchPlayer);
    }
    
    if( pAgent->isPlayerSeen() )
    {
        pAgent->changeState(PLG_EnemyAi::eENEMY_STATES::eES_AlarmOthers);
    }
    
    if( !pAgent->hasPositionTarget() )
    {
        pAgent->chooseNewRandomPath();
    }
}

void PLG_EnemyAlarmOthersState::onEnter(PLG_EnemyAi *pAgent)
{
    pAgent->setPathToAlarm();
}

void PLG_EnemyAlarmOthersState::onExecute(PLG_EnemyAi *pAgent)
{
    if( PLG_GameInfo.isPlayerDown )
    {
        pAgent->changeState(PLG_EnemyAi::eENEMY_STATES::eES_WanderAround);
    }
    
    if( !pAgent->hasPositionTarget() )
    {
        pAgent->changeState(PLG_EnemyAi::eENEMY_STATES::eES_SearchPlayer);
    }
}

void PLG_EnemySearchPlayerState::onEnter(PLG_EnemyAi* pAgent)
{
    pAgent->setPathToPlayer();
}

void PLG_EnemySearchPlayerState::onExecute(PLG_EnemyAi* pAgent)
{
    if( PLG_GameInfo.isPlayerDown )
    {
        pAgent->changeState(PLG_EnemyAi::eENEMY_STATES::eES_WanderAround);
    }
    
    if( pAgent->isPlayerClose() )
    {
        pAgent->attack();
    }
    
    if( !pAgent->hasPositionTarget() )
    {
        pAgent->setPathToPlayer();
    }
}
