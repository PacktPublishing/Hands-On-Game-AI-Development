//
//  TankActions.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 11/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankActions.hpp"

#include "Commons.hpp"
#include "TankCommons.hpp"
#include "Timer.hpp"
#include "GameWorldInfo.hpp"
#include "glm.hpp"

using namespace TankCommons;

void BC_TankShootAction::performAction(TankAI *pAgent)
{
    pAgent->fire();
}

void BC_TankMoveTowardsPlayerAction::performAction(TankAI *pAgent)
{
    auto dir = GameInfo.playerPosition - pAgent->getPosition();
    dir = glm::normalize(dir);

    if( MathCommons::definitelyGreaterThan(dir.x, dir.y) )
    {
        // Move on left-right

        if( MathCommons::definitelyGreaterThan(dir.x, MathCommons::EPSILON) )
        {
            // right
            if(pAgent->getHeadingVector().x == 1)
            {
                pAgent->move(eTANK_MOVEMENT::eTM_UP);
            }
            else
            {
                pAgent->move(eTANK_MOVEMENT::eTM_LEFT);
            }
        }
        else
        {
            // left
            if(pAgent->getHeadingVector().x == -1)
            {
                pAgent->move(eTANK_MOVEMENT::eTM_UP);
            }
            else
            {
                pAgent->move(eTANK_MOVEMENT::eTM_LEFT);
            }
        }
    }
    else
    {

        // Move on up-down
        if( MathCommons::definitelyGreaterThan(dir.y, MathCommons::EPSILON) )
        {
            // up
            if(pAgent->getHeadingVector().y == 1)
            {
                pAgent->move(eTANK_MOVEMENT::eTM_UP);
            }
            else
            {
                pAgent->move(eTANK_MOVEMENT::eTM_RIGHT);
            }
            
        }
        else
        {
            // down
            if(pAgent->getHeadingVector().y == -1)
            {
                pAgent->move(eTANK_MOVEMENT::eTM_UP);
            }
            else
            {
                pAgent->move(eTANK_MOVEMENT::eTM_RIGHT);
            }
        }
    }
}

template <class T>
T getControlledRandom(T min, T max, T current)
{
    auto decision = MathCommons::randomUint( (unsigned int)min, (unsigned int)max );
    if( decision == current )
    {
        (MathCommons::randomUint(1, 100) < 51) ? decision-- : decision++;
        if(decision < (unsigned int)min)
        {
            decision = (unsigned int)max;
        }
        else if(decision > (unsigned int)max)
        {
            decision = (unsigned int)min;
        }
    }
    
    return (T)decision;
}

void BC_TankChooseRandomPathByCollisionAction::performAction(TankAI *pAgent)
{
    auto decision = MathCommons::randomUint( (unsigned int)eTM_UP, (unsigned int)eTM_LEFT );
    if( decision == pAgent->getCurrentMovement() )
    {
        (MathCommons::randomUint(1, 100) < 51) ? decision-- : decision++;
        if(decision < (unsigned int)eTM_UP)
        {
            decision = (unsigned int)eTM_LEFT;
        }
        else if(decision > (unsigned int)eTM_LEFT)
        {
            decision = (unsigned int)eTM_UP;
        }
    }
    
    pAgent->move((eTANK_MOVEMENT)decision);
    pAgent->clearIsCollided();
}

void BC_TankChooseRandomPathByTimeAction::performAction(TankAI *pAgent)
{
    pAgent->move( getControlledRandom(TankCommons::eTM_UP, TankCommons::eTM_LEFT, pAgent->getCurrentMovement()) );
    pAgent->setLastPathTime(Time.time);
    
}
