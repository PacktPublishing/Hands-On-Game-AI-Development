//
//  TankDecisions.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 04/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankDecisions_hpp
#define TankDecisions_hpp

#include "Timer.hpp"

#include "DecisionNodes.hpp"
#include "TankAI.hpp"


class BC_IsPlayerClose : public DT_BoolDecision<TankAI>
{
public:
    
    BC_IsPlayerClose() {}
    virtual ~BC_IsPlayerClose() {}
    
protected:
    
    bool performTest(TankAI* pAgentPtr);
};

class BC_CanShootPlayer : public DT_BoolDecision<TankAI>
{
public:
    
    BC_CanShootPlayer() {}
    virtual ~BC_CanShootPlayer() {}
    
protected:
    
    bool performTest(TankAI* pAgentPtr);
};

class BC_IsCollidedWithWall : public DT_BoolDecision<TankAI>
{
public:
    
    BC_IsCollidedWithWall() {}
    virtual ~BC_IsCollidedWithWall() {}
    
protected:
    
    bool performTest(TankAI* pAgentPtr);
};

class BC_IsChooseNewPath : public DT_BoolDecision<TankAI>
{
public:
    
    BC_IsChooseNewPath() {}
    virtual ~BC_IsChooseNewPath() {}
    
protected:
    
    bool performTest(TankAI* pAgentPtr);
};

#endif /* TankDecisions_hpp */
