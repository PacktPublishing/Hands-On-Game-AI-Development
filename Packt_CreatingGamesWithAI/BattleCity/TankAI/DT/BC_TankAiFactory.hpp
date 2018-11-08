//
//  BC_TankAiFactory.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 03/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BC_TankAiFactory_hpp
#define BC_TankAiFactory_hpp

#include "BC_DecisionTreeBuilders.hpp"

enum eTANK_AI_TYPES{ BASE };

class BC_TankAiFactory
{
public:
    
    static DT_Node<TankAI>* instantiate(const eTANK_AI_TYPES type);
    
private:
    
    class TankGenerator
    {
    public:
      
        DT_Node<TankAI>* getDt();
        void generateAi(BaseDecisionTreeBuilder<TankAI>* pBuilder);
        
    private:
        
        BaseDecisionTreeBuilder<TankAI>* mBuilderPtr;
        
    };
    
private:
    
    static TankGenerator mTankGenerator;
    
    static BaseTankAiDtBuilder mBaseBuilder;
};


#endif /* BC_TankAiFactory_hpp */
