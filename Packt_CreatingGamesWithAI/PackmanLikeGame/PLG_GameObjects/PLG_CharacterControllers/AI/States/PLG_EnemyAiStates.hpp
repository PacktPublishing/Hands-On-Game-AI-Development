//
//  PLG_EnemyAiStates.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 01/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_EnemyAiStates_hpp
#define PLG_EnemyAiStates_hpp

#include "State.hpp"

class PLG_EnemyAi;

class PLG_EnemyWanderingState : public State<PLG_EnemyAi>
{
public:
    
    virtual ~PLG_EnemyWanderingState() { }
    
    void onEnter(PLG_EnemyAi* pAgent) override { }
    
    void onExecute(PLG_EnemyAi* pAgent) override;

    void onExit(PLG_EnemyAi* pAgent) override { }
};

class PLG_EnemyAlarmOthersState : public State<PLG_EnemyAi>
{
public:
    
    virtual ~PLG_EnemyAlarmOthersState() { }
    
    void onEnter(PLG_EnemyAi* pAgent) override;
    void onExecute(PLG_EnemyAi* pAgent) override;
    
    void onExit(PLG_EnemyAi* pAgent) override { }
};

class PLG_EnemySearchPlayerState : public State<PLG_EnemyAi>
{
public:
    
    virtual ~PLG_EnemySearchPlayerState() { }
    
    void onEnter(PLG_EnemyAi* pAgent) override;
    void onExecute(PLG_EnemyAi* pAgent) override;
    
    void onExit(PLG_EnemyAi* pAgent) override { }
};

#endif /* PLG_EnemyAiStates_hpp */
