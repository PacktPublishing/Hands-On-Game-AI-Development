//
//  SparseGraph.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef SparseGraph_hpp
#define SparseGraph_hpp

#include <vector>
#include <list>

#include "Commons.hpp"

// Graph with adjacency list representation
template <class NodeType, class EdgeType>
class SparseGraph
{
public:

    typedef NodeType NodeT;
    typedef EdgeType EdgeT;
    
    typedef std::vector<NodeType> NodeVector;
    typedef std::list<EdgeType> EdgeList;
    typedef std::vector<EdgeList> EdgeListVector;
    
    SparseGraph()
        : mIsDigraph(false), mIndexOfNextNode(0)
    { }
    
    SparseGraph(bool pIsDigraph)
        : mIsDigraph(pIsDigraph), mIndexOfNextNode(0)
    { }
    
    void clear()
    {
        mIndexOfNextNode = 0;
        mNodes.clear();
        mEdges.clear();
    }
    
    bool isDigraph() const { return mIsDigraph; }
    bool isEmpty() const { return mNodes.empty(); }
    int getNextNodeIndex() const { return mIndexOfNextNode; }
    
    const NodeVector& getNodes() const { return mNodes; }
    const NodeType& getNode(const int pIndex) const { return mNodes[pIndex]; }
    NodeType& getNode(const int pIndex) { return mNodes[pIndex]; }
    
    // If the node exists, but inactive, then reactivates the node
    // If the node unexists, checks whether the index is correct and then adds it to the graph.
    // If the node aimed to be added has invalid nindex, then the method return INVALID_NODE_INDEX (-1)
    int addNode(NodeType pNewNode)
    {
        using namespace GraphCommons;
        
        if (pNewNode.getIndex() < (int)mNodes.size() && pNewNode.getIndex() != INVALID_NODE_INDEX)
        {
            // A dublicated node
            mNodes[pNewNode.getIndex()] = pNewNode;
            return mIndexOfNextNode;
        }
        else
        {
            if(pNewNode.getIndex() == INVALID_NODE_INDEX)
            {
                return INVALID_NODE_INDEX;
            }
            
            mNodes.push_back(pNewNode);
            mEdges.push_back(EdgeList());
            
            return mIndexOfNextNode++;
        }
    }
    
    // Marks the node as invalid and removes all the edges leading from and to this node
    void removeNode(const int pNodeIndex)
    {
        if(pNodeIndex >= mNodes.size())
        {
            return;
        }
        
        using namespace GraphCommons;
        
        // Mark the node as invalid
        mNodes[pNodeIndex].setIndex(INVALID_NODE_INDEX);
        
        // If the graph is not directed, remove all the edges leading to this node and
        // then clear the edges leading from this node
        if( !mIsDigraph )
        {
            for (auto curEdge = mEdges[pNodeIndex].begin(); curEdge != mEdges[pNodeIndex].end(); ++curEdge)
            {
                for (auto curE = mEdges[curEdge->getTo()].begin(); curE != mEdges[curEdge->getTo()].end(); ++curE)
                {
                    if (curE->getTo() == pNodeIndex)
                    {
                        curE = mEdges[curEdge->getTo()].erase(curE);
                        break;
                    }
                }
            }
            
            mEdges[pNodeIndex].clear();
        }
        else
        {
            // If the graph is directed, then cull the invalid edges.
            // Reuires iterating through all the edges
            cullInvalidEdges();
        }
    }
    
    // Return number of active + inactive nodes
    int getNumberOfAllNodes() const { return (int)mNodes.size(); }
    
    int getNumberofActiveNodes() const
    {
        using namespace GraphCommons;
        auto count = 0;
        for(size_t ni = 0; ni < mNodes.size(); ++ni)
        {
            if(mNodes[ni].getIndex() != INVALID_NODE_INDEX)
            {
                ++count;
            }
        }
        return count;
    }
    
    bool checkIsNodePresent(const int pIndex) const
    {
        using namespace GraphCommons;
        if(  (pIndex >= mNodes.size()) || (mNodes[pIndex].getIndex() == INVALID_NODE_INDEX ) )
        {
            return false;
        }
        return true;
    }
    
    const EdgeList& getEdgeList(const int pNodeIndex) const
    {
        return mEdges[pNodeIndex];
    }
    
    const EdgeType& getEdge(const int pFrom, const int pTo) const
    {
        for(const auto& edge : mEdges[pFrom])
        {
            if(edge.getTo() == pTo)
            {
                return edge;
            }
        }
    }
    
    EdgeType& getEdge(const int pFrom, const int pTo)
    {
        for(auto& edge : mEdges[pFrom])
        {
            if(edge.getTo() == pTo)
            {
                return edge;
            }
        }
    }
    
    // Used for adding new edges to the graph. This methid ensures that the edge passed
    // is valid before adding it to the graph. In case the graph is an undirected graph,
    // then the edge in the opposite direction will be automatically added.
    void addEdge(EdgeType pNewEdge)
    {
        using namespace GraphCommons;
        
        // The edge indices are invalid
        if(pNewEdge.getFrom() >= mIndexOfNextNode || pNewEdge.getTo() >= mIndexOfNextNode )
        {
            return;
        }
        
        // Be sure both nodes are active
        if(
                (mNodes[pNewEdge.getTo()].getIndex() != INVALID_NODE_INDEX) &&
                (mNodes[pNewEdge.getFrom()].getIndex() != INVALID_NODE_INDEX)
           )
        {
            // Be sure the edge is unique
            if ( checkUniqueEdge(pNewEdge.getFrom(), pNewEdge.getTo()) )
            {
                mEdges[pNewEdge.getFrom()].push_back(pNewEdge);
            }
            
            // If the graph is undirected, add the other connection
            if( !mIsDigraph )
            {
                // Be sure the edge is unique
                if ( checkUniqueEdge(pNewEdge.getTo(), pNewEdge.getFrom()) )
                {
                    EdgeType newEdge = pNewEdge;
                    
                    newEdge.setTo(pNewEdge.getFrom() );
                    newEdge.setFrom(pNewEdge.getTo() );
                    
                    mEdges[pNewEdge.getTo()].push_back(newEdge);
                }
            }
        }
    }
    
    void removeEdge(const int pFrom, const int pTo)
    {
        if(pFrom >= mNodes.size() || pTo >= mNodes.size())
        {
            return;
        }
        
        if ( !mIsDigraph )
        {
            for(auto& edge : mEdges[pTo])
            {
                if(edge.getTo() == pFrom)
                {
                    mEdges[pTo].erase(edge);
                    break;
                }
            }
        }
        
        for(auto& edge : mEdges[pFrom])
        {
            if(edge.getTo() == pTo)
            {
                mEdges[pFrom].erase(edge);
                break;
            }
        }
    }
    
    void setEdgeCost(const int pFrom, const int pTo, const float pCost)
    {
        if(pFrom >= mNodes.size() || pTo >= mNodes.size() )
        {
            return;
        }
        
        for(auto& edge : mEdges[pFrom])
        {
            if(edge.getTo() == pTo)
            {
                edge.setCost(pCost);
                break;
            }
        }
    }
    
    bool checkIsEdgePresent(const int pFrom, const int pTo) const
    {
        if( checkIsNodePresent(pFrom) && checkIsNodePresent(pTo) )
        {
            for(const auto& edge : mEdges[pFrom])
            {
                if(edge.getTo() == pTo)
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    int getTotalNumberOfEdges() const
    {
        auto totalNum = 0;
        for(const auto& edge : mEdges)
        {
            totalNum += edge->size();
        }
        return totalNum;
    }
    
    // Remove all the edges
    void removeEdges()
    {
        for(auto& edge : mEdges)
        {
            edge->clear();
        }
        
        mEdges.clear();
    }
    
private:
    
    // This is used for preventing the dublicates.
    // Returns true if the edge is already in the graph.
    bool checkUniqueEdge(int pFrom, int pTo) const
    {
        for(const auto& edge : mEdges[pFrom])
        {
            if(edge.getTo() == pTo)
            {
                return false;
            }
        }
        return true;
    }

    // Iterates through all the edges and removes the invalid ones
    void cullInvalidEdges()
    {
        using namespace GraphCommons;
        
        for (auto curEdgeList = mEdges.begin(); curEdgeList != mEdges.end(); ++curEdgeList)
        {
            for (auto curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
            {
                if(
                        mNodes[curEdge->getTo()].getIndex() == INVALID_NODE_INDEX ||
                        mNodes[curEdge->getFrom()].getIndex() == INVALID_NODE_INDEX
                   )
                {
                    curEdge = (*curEdgeList).erase(curEdge);
                }
            }
        }
    }
    
    // The graph nodes
    NodeVector mNodes;
    
    // A vector of adjacency edge lists. Each node index keys into the
    // list of edges associated with that node.
    EdgeListVector  mEdges;
    
    // True if this is a directed graph, false othwerwise.
    bool mIsDigraph;
    
    // The index of the next node to be added
    int mIndexOfNextNode;
};

#endif /* SparseGraph_hpp */
