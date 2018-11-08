//
//  BC_TankAiFactory.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 03/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "BC_TankAiFactory.hpp"

BC_TankAiFactory::TankGenerator BC_TankAiFactory::mTankGenerator;
BaseTankAiDtBuilder BC_TankAiFactory::mBaseBuilder;

DT_Node<TankAI>* BC_TankAiFactory::instantiate(const eTANK_AI_TYPES type)
{
    switch(type)
    {
        case BASE:
            mTankGenerator.generateAi(&mBaseBuilder);
            break;
    }
    
    return mTankGenerator.getDt();
}

DT_Node<TankAI>* BC_TankAiFactory::TankGenerator::getDt()
{
    return mBuilderPtr->getRoot();
}

void BC_TankAiFactory::TankGenerator::generateAi(BaseDecisionTreeBuilder<TankAI> *pBuilder)
{
    mBuilderPtr = pBuilder;
    mBuilderPtr->startCreationProcess();
}
