//
//  AStarHeuristics.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef AStarHeuristics_hpp
#define AStarHeuristics_hpp

#include "Commons.hpp"
#include "glm.hpp"

// Heuristic uses Euclidian (straight line) distance
class AstarEuclidHeuristic
{
public:
    
    template <class GraphType>
    static float calculate(const GraphType* pGraph, const int pNode1index, const int pNode2index)
    {
        return glm::distance(pGraph->getNode(pNode1index).getPosition(), pGraph->getNode(pNode2index).getPosition());
    }
};

// If you have lots of agents in the scene, this heuristic provides
// better results since it will prevent agents in a line following each other
// thanks to the noise
class AstarNoisyEuclidHeuristic
{
public:
    
    template <class GraphType>
    static float calculate(const GraphType* pGraph, const int pNode1index, const int pNode2index)
    {
        using namespace MathCommons;
        return glm::distance(pGraph->getNode(pNode1index).getPosition(), pGraph->getNode(pNode2index).getPosition()) * randomFloat(0.9f, 1.1f);
    }
};

// Manhattan distance heuristic
class AstarManhattanDistanceHeuristic
{
public:
    
    template <class GraphType>
    static float calculate(const GraphType* pGraph, const int pNode1index, const int pNode2index)
    {
        auto posI = pGraph->getNode(pNode1index).getPosition();
        auto posII = pGraph->getNode(pNode2index).getPosition();
        
        return ( fabsf(posI.x - posII.x) + (posI.y - posII.y) );
    }
};

// For turning A* into Dijkstra
class AstarDijkstraHeuristic
{
public:
    
    template <class GraphType>
    static float calculate(const GraphType* pGraph, const int pNode1index, const int pNode2index)
    {
        return 0.f;
    }
};

#endif /* AStarHeuristics_hpp */
