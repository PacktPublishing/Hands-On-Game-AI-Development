//
//  BC_DecisionTreeBuilders.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 15/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BC_DecisionTreeBuilders_hpp
#define BC_DecisionTreeBuilders_hpp

#include "BaseDecisionTreeBuilder.hpp"
#include "TankAI.hpp"

class BaseTankAiDtBuilder : public BaseDecisionTreeBuilder<TankAI>
{
public:
    
    BaseTankAiDtBuilder() {}
    virtual ~BaseTankAiDtBuilder() {}
    
protected:
    
    void applyConstructionBlueprint() override;
};

#endif /* BC_DecisionTreeBuilders_hpp */
