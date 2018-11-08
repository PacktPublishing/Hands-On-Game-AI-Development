//
//  DT_DecisionTree.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 04/03/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef DT_DecisionTree_hpp
#define DT_DecisionTree_hpp

#include <vector>
#include <memory>

#include <iostream> // For std::cout

// Base class for DecisionTree nodes
template <class entity_type>
class DT_Node
{
public:
    
    DT_Node() {}
    virtual ~DT_Node()
    {
        mNodes.clear();
    }
    
    // Performs decision process
    virtual DT_Node* decide(entity_type* pAgentPtr) = 0;
    
    virtual void addChild(std::unique_ptr<DT_Node>&& pNewChild)
    {
        mNodes.emplace_back( std::move(pNewChild) );
    }
    
protected:
    
    // Vector of children
    std::vector< std::unique_ptr<DT_Node> > mNodes;
};

// Base class for decisions of a DecisionTree
template <class entity_type>
class DT_Decision : public DT_Node<entity_type>
{
public:
    
    DT_Decision()
        : DT_Node<entity_type>()
    {
      
    }
    
    virtual ~DT_Decision()
    {
        
    }
    
    // Moves to resultant branch
    DT_Node<entity_type>* decide(entity_type* pAgentPtr)
    {
        return getBranch(pAgentPtr)->decide(pAgentPtr);
    }
    
protected:
    
    // Performs the test of the decision
    virtual DT_Node<entity_type>* getBranch(entity_type* pAgentPtr) = 0;
};

// Base class for actions of a DecisionTree
template <class entity_type>
class DT_Action : public DT_Node<entity_type>
{
public:
    
    DT_Action()
        : DT_Node<entity_type>()
    {}
    virtual ~DT_Action() {}
    
    // Returns itself as the decision -since we reach to the leaf
    DT_Node<entity_type>* decide(entity_type* pAgentPtr) override
    {
        return this;
    }
    
    // Actions have no children
    void addChild(std::unique_ptr< DT_Node<entity_type> >&& pNewChild) override {}
    
    // Performs the related action
    virtual void performAction(entity_type* pAgent) = 0;
    
};

// Template DecisionTree
template <class entity_type>
class DecisionTree
{
public:
    
    DecisionTree(entity_type* pAgentPtr)
    {
        mAgentPtr = pAgentPtr;
    }
    
    DecisionTree(entity_type* pAgentPtr, std::unique_ptr< DT_Node<entity_type> >&& pRoot)
    {
        mAgentPtr = pAgentPtr;
        mRoot = std::move(pRoot);
    }
    
    DecisionTree(entity_type* pAgentPtr,  DT_Node<entity_type>* pRoot)
    {
        mAgentPtr = pAgentPtr;
        mRoot.reset(pRoot);
    }
    
    ~DecisionTree()
    {
        
    }
    
    void addRoot(std::unique_ptr< DT_Node<entity_type> >&& pRoot)
    {
        mRoot = std::move(pRoot);
    }
    
    // Starts the decision process
    void decide()
    {
        // Get related action
        DT_Action<entity_type>* resultantAction = (DT_Action<entity_type>*)(mRoot->decide(mAgentPtr));
        if(resultantAction != nullptr)
        {
            // Perform the result of the action
            resultantAction->performAction(mAgentPtr);
        }
        else
        {
            std::cout<<"ERROR! DT! FACED WITH A NULL DT_ACTION";
        }
    }
    
private:
    
    // Root of the DecisionTree
    std::unique_ptr<DT_Node<entity_type>> mRoot;
    
    // Pointer to the agent (not ownership)
    entity_type* mAgentPtr;
};

#endif /* DT_DecisionTree_hpp */
