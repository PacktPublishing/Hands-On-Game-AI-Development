//
//  TankDecisions.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 04/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankDecisions.hpp"

#include "glm.hpp"

#include "Commons.hpp"
#include "GameWorldInfo.hpp"

#include <cmath>

bool BC_IsPlayerClose::performTest(TankAI *pAgentPtr)
{
    auto distance = glm::distance(pAgentPtr->getPosition(), GameInfo.playerPosition);
    if( MathCommons::definitelyLessThan(distance, 200.f + MathCommons::EPSILON) )
    {
        return true;
    }
    
    return false;
}

bool BC_CanShootPlayer::performTest(TankAI *pAgentPtr)
{
    // The vector from agent to player
    glm::vec2 dir = GameInfo.playerPosition - pAgentPtr->getPosition();
    dir = glm::normalize(dir);
    // If the angle (in degrees) between the agent and the player is
    // in [0, 30] range, then the agent can fire
    float theta = glm::dot(pAgentPtr->getHeadingVector(), dir);
    if( MathCommons::definitelyLessThan(theta, 1.f + MathCommons::EPSILON) && MathCommons::definitelyGreaterThan(theta, 0.8660) )
    {
        return true;
    }
    
    return false;
}

bool BC_IsCollidedWithWall::performTest(TankAI *pAgentPtr)
{
    if( pAgentPtr->getIsCollided() )
    {
        return true;
    }
    
    return false;
}

bool BC_IsChooseNewPath::performTest(TankAI* pAgentPtr)
{
    if( MathCommons::definitelyGreaterThan((Time.time - pAgentPtr->getLastPathChangeTime()), pAgentPtr->getPathTimeLimit()) && MathCommons::randomInt(1, 100) < 70 )
    {
        return true;
    }
    
    return false;
}
