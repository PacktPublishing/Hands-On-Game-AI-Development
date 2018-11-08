//
//  DecisionNodes.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 04/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef DecisionNodes_hpp
#define DecisionNodes_hpp

#include "DT_DecisionTree.hpp"

template <class entity_type>
class DT_BoolDecision : public DT_Decision<entity_type>
{
public:
    
    enum eNODE_TYPE{ eNT_TRUE_NODE = 0, eNT_FALSE_NODE};

    DT_BoolDecision()
        : DT_Decision<entity_type>(),
          BRANCH_NUMBER(2)
    {
        
    }
    
    virtual ~DT_BoolDecision()
    {
        
    }
    
    void addChild(std::unique_ptr< DT_Node<entity_type> >&& pNewChild) override
    {
        this->mNodes.emplace_back( std::move(pNewChild) );
    }
    
    void addChild(const eNODE_TYPE pNodeType, std::unique_ptr< DT_Node<entity_type> >&& pNewChild)
    {
        if(this->mNodes.size() <BRANCH_NUMBER)
        {
            this->mNodes.emplace( this->mNodes.begin() + (int)pNodeType, std::move(pNewChild) );
        }
    }

protected:

    virtual bool performTest(entity_type* pAgentPtr) = 0;
    
    DT_Node<entity_type>* getBranch(entity_type* pAgentPtr) override
    {
        if( performTest(pAgentPtr) )
        {
            return this->mNodes[eNODE_TYPE::eNT_TRUE_NODE].get();
        }
        
        return this->mNodes[eNODE_TYPE::eNT_FALSE_NODE].get();
    }

    const int BRANCH_NUMBER;
};

#endif /* DecisionNodes_hpp */
