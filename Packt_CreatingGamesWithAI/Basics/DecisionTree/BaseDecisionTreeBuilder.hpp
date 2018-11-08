//
//  BC_DecisionTreeBuilder.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 15/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef BaseDecisionTreeBuilder_hpp
#define BaseDecisionTreeBuilder_hpp

#include "DT_DecisionTree.hpp"

template <class entity_type>
class BaseDecisionTreeBuilder
{
public:
    
    virtual ~BaseDecisionTreeBuilder() {}
    
    DT_Node<entity_type>* getRoot()
    {
        return mRoot.release();
    }
    
    void startCreationProcess()
    {
        applyConstructionBlueprint();
    }
    
protected:
    
    virtual void applyConstructionBlueprint() = 0;
    
    std::unique_ptr<DT_Node<entity_type>> mRoot;
};

#endif /* BC_DecisionTreeBuilder_hpp */
