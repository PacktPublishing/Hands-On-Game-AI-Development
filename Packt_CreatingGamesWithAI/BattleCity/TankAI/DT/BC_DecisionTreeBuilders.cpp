//
//  BC_DecisionTreeBuilders.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 15/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "BC_DecisionTreeBuilders.hpp"

#include "TankDecisions.hpp"
#include "TankActions.hpp"

void BaseTankAiDtBuilder::applyConstructionBlueprint()
{
    auto root = std::make_unique<BC_IsPlayerClose>();
    auto canShoot = std::make_unique<BC_CanShootPlayer>();
    auto isCollided = std::make_unique<BC_IsCollidedWithWall>();
    auto isTimeNewPath = std::make_unique<BC_IsChooseNewPath>();
    
    isTimeNewPath->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_TRUE_NODE, std::make_unique<BC_TankChooseRandomPathByTimeAction>() );
    isTimeNewPath->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_FALSE_NODE, std::make_unique<BC_TankNoAction>() );
    
    isCollided->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_TRUE_NODE, std::make_unique<BC_TankChooseRandomPathByCollisionAction>() );
    isCollided->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_FALSE_NODE, std::move(isTimeNewPath) );
    
    canShoot->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_TRUE_NODE, std::make_unique<BC_TankShootAction>() );
    canShoot->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_FALSE_NODE, std::make_unique<BC_TankMoveTowardsPlayerAction>() );
    
    root->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_TRUE_NODE, std::move(canShoot) );
    root->addChild(DT_BoolDecision<TankAI>::eNODE_TYPE::eNT_FALSE_NODE, std::move(isCollided) );
    
    mRoot.reset( root.release() );
}
