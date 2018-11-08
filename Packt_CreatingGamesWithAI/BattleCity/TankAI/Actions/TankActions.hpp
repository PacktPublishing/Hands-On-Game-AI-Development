//
//  TankActions.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 11/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankActions_hpp
#define TankActions_hpp

#include "DT_DecisionTree.hpp"
#include "TankAI.hpp"

class BC_TankShootAction : public DT_Action<TankAI>
{
public:
    
    BC_TankShootAction() {}
    virtual ~BC_TankShootAction() {}
    
    void performAction(TankAI* pAgent) override;
};

class BC_TankMoveTowardsPlayerAction : public DT_Action<TankAI>
{
public:
    
    BC_TankMoveTowardsPlayerAction()
        : currentMoveDir(eMOVING_DIR::none), isDirectionDecided(false), isSecondTimer(false)
    {}
    virtual ~BC_TankMoveTowardsPlayerAction() {}
    
    void performAction(TankAI* pAgent) override;
    
private:
    
    enum eMOVING_DIR{ none, X, Y };
    enum eMOVING_DIR currentMoveDir;
    
    bool isDirectionDecided;
    bool isSecondTimer;
    
};

class BC_TankChooseRandomPathByCollisionAction : public DT_Action<TankAI>
{
public:
    
    BC_TankChooseRandomPathByCollisionAction() {}
    virtual ~BC_TankChooseRandomPathByCollisionAction() {}
    
    void performAction(TankAI* pAgent) override;
};

class BC_TankChooseRandomPathByTimeAction : public DT_Action<TankAI>
{
public:
    
    BC_TankChooseRandomPathByTimeAction() {}
    virtual ~BC_TankChooseRandomPathByTimeAction() {}
    
    void performAction(TankAI* pAgent) override;
};


class BC_TankNoAction : public DT_Action<TankAI>
{
public:
    
    BC_TankNoAction() {}
    virtual ~BC_TankNoAction() {}
    
    void performAction(TankAI* pAgent) override {}
};

#endif /* TankActions_hpp */
