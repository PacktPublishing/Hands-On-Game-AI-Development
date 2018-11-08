//
//  AStarSearch.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef AStarSearch_hpp
#define AStarSearch_hpp

#include "Commons.hpp"
#include "IndexedPriorityQueueLow.hpp"

#include <list>

// A* graph search algorithm
template <class GraphType, class HeuristicType>
class AStarSearch
{
private:
    
    typedef typename GraphType::EdgeT Edge;
    typedef typename GraphType::NodeT Node;
    
public:
    
    // In case you want to use A* as a class member
    AStarSearch(const GraphType* pGraph)
    : mGraph(pGraph), mShortestPathTree( pGraph->getNumberOfAllNodes() ), mSearchFrontier( pGraph->getNumberOfAllNodes() ),
    mGCosts(pGraph->getNumberOfAllNodes(), 0.f), mFCosts(pGraph->getNumberOfAllNodes(), 0.f),
    mSourceIndex(GraphCommons::INVALID_NODE_INDEX), mTargetIndex(GraphCommons::INVALID_NODE_INDEX)
    { }
    
    // In case you want to use A* as a local variable
    AStarSearch(const GraphType* pGraph, int pSourceIndex, int pTargetIndex)
        :   mGraph(pGraph), mShortestPathTree( pGraph->getNumberOfAllNodes() ), mSearchFrontier( pGraph->getNumberOfAllNodes() ),
            mGCosts(pGraph->getNumberOfAllNodes(), 0.f), mFCosts(pGraph->getNumberOfAllNodes(), 0.f),
            mSourceIndex(pSourceIndex), mTargetIndex(pTargetIndex)
    {
        getPreparedForSearch(mSourceIndex, mTargetIndex);
    }
    
    ~AStarSearch()
    {
        mGCosts.clear();
        mFCosts.clear();
        mShortestPathTree.clear();
        mSearchFrontier.clear();
    }
    
    std::vector<const Edge*> getSPT() const { return mShortestPathTree; }
    
    // Returns the total cost to the target
    float getCostToTarget() const { return mGCosts[mTargetIndex]; }
    
    // Return the series of nodes needed to visit for reaching to the target node
    std::list<int> getPathToTarget() const
    {
        using namespace GraphCommons;
        
        std::list<int> path;

        if (mTargetIndex == INVALID_NODE_INDEX)
        {
            return path;
        }
        
        auto currentTarget = mTargetIndex;
        path.push_front(currentTarget);
        
        while ((currentTarget != mSourceIndex) && (mShortestPathTree[currentTarget] != NULL))
        {
            currentTarget = mShortestPathTree[currentTarget]->getFrom();
            path.push_front(currentTarget);
        }
        
        return path;
    }
    
    void getPreparedForSearch(const int pSourceNodeIndex, const int pTargetNodeIndex)
    {
        using namespace GraphCommons;
        
        if(
            pSourceNodeIndex != INVALID_NODE_INDEX && (pSourceNodeIndex > -1 && pSourceNodeIndex < mGraph->getNextNodeIndex()) &&
            pTargetNodeIndex != INVALID_NODE_INDEX && (pTargetNodeIndex > -1 && pTargetNodeIndex < mGraph->getNextNodeIndex())
           )
        {
            mSourceIndex = pSourceNodeIndex;
            mTargetIndex = pTargetNodeIndex;
            
            reset();
            
            search();
        }
    }
    
private:
    
    void reset()
    {
        for(size_t ci = 0; ci < mGCosts.size(); ++ci)
        {
            mGCosts[ci] = 0.f;
        }
        
        for(size_t ci = 0; ci < mFCosts.size(); ++ci)
        {
            mFCosts[ci] = 0.f;
        }
        
        for(size_t ci = 0; ci < mShortestPathTree.size(); ++ci)
        {
            mShortestPathTree[ci] = NULL;
        }
        
        for(size_t ci = 0; ci < mSearchFrontier.size(); ++ci)
        {
            mSearchFrontier[ci] = NULL;
        }
    }
    
    // A* algorithm
    void search()
    {
        // Indexed priority (low) queue is used to keep track of the nodes.
        // The nodes with the lowest overall cost (F = G + H) are positioned
        // at the front of the queue.
        IndexedPriorityQueueLow<float> pq(mFCosts, mGraph->getNumberOfAllNodes());
        
        // Start with the source node
        pq.insert(mSourceIndex);
        
        while( !pq.empty() )
        {
            // Get the lowest cost node
            int nextClosestNode = pq.pop();
            
            // Move this node from the frontier to the spanning tree
            mShortestPathTree[nextClosestNode] = mSearchFrontier[nextClosestNode];
            
            if (nextClosestNode == mTargetIndex)
            {
                return;
            }

            // Check all the edges from this node
            for(const auto& pE : mGraph->getEdgeList(nextClosestNode))
            {
                // Calculate the heuristic cost (H) from this node to the target
                auto hCost = HeuristicType::calculate(mGraph, mTargetIndex, pE.getTo());
                
                // Calculate the 'real' cost (G) to this node from the source
                auto gCost = mGCosts[nextClosestNode] + pE.getCost();
                
                // If the node is not on the frontier
                if (mSearchFrontier[pE.getTo()] == NULL)
                {
                    // Add the node to the frontier and update the overall (F)
                    // and real (G) costs
                    mFCosts[pE.getTo()] = gCost + hCost;
                    mGCosts[pE.getTo()] = gCost;
                    
                    pq.insert(pE.getTo());
                    
                    mSearchFrontier[pE.getTo()] = &pE;
                }
                // If the node already on the frontier but the cost leading there is lower
                else if ((gCost < mGCosts[pE.getTo()]) && (mShortestPathTree[pE.getTo()]==NULL))
                {
                    // Update the costs and frontier
                    mFCosts[pE.getTo()] = gCost + hCost;
                    mGCosts[pE.getTo()] = gCost;
                    
                    pq.changePriority(pE.getTo());
                    
                    mSearchFrontier[pE.getTo()] = &pE;
                }
            }
        }
    }
    
    int mSourceIndex, mTargetIndex;
    
    // Real accumulative cost to the node
    std::vector<float> mGCosts;
    
    // The cost from adding mGCosts[n] to the heuristic cost from n to the target node
    // Priority queue indexes into this vector
    std::vector<float> mFCosts;
    
    std::vector<const Edge*> mShortestPathTree;
    std::vector<const Edge*> mSearchFrontier;
    
    const GraphType* mGraph;
    
};

#endif /* AStarSearch_hpp */
