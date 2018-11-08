//
//  PathPlanner.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PathPlanner_hpp
#define PathPlanner_hpp

#include "GameCharacterController.hpp"
#include "SparseGraph.hpp"
#include "NavGraphNode.hpp"
#include "GraphEdge.hpp"
#include "AStarSearch.hpp"
#include "AStarHeuristics.hpp"

class CollisionGrid;

// Common buffer for various path planners
typedef SparseGraph<NavGraphNode<void*>, GraphEdge> PlainNavGraph;
class PathInfo
{
public:
    
    static PathInfo& getInstance();
    
    const PlainNavGraph* navGraph;
    const CollisionGrid* collisionGrid;
    
    glm::vec2 getNodePosition(const int pNodeIndex) const;

    // Return true if the path from A to B is obstructed
    // Return false otherwise.
    //
    // It functions by stepping from A to B in steps of size pBoundingRadius and tests with the
    // world at each step/point
    bool isPathObstructed(const glm::vec2& pPosA, const glm::vec2& pPosB, float pBoundingRadius) const;
    
private:
    
    PathInfo() { }
    ~PathInfo() { }
};

// Path planner class is used for planning a path from A to B. Each agent has its own instance of the path planner.
// Path planners share the common navigation graph and collision grid information via PathInfo class.
class PathPlanner
{
public:
    
    PathPlanner();
    PathPlanner(GameCharacterController* pOwner);
    
    void setOwnner(GameCharacterController* pOwner);
    
    glm::vec2 getDestination() const { return mDestinationPos; }
    void setDestination(const glm::vec2& pPos){ mDestinationPos = pPos; }

    // Finds the optimal path to the target position via A* search with noisy euclidian heuristic
    bool requestPathToPosition(const glm::vec2& pTargetPos, std::vector<glm::vec2>& positions);
    
    // Finds the optimal path to a random graph node via A* search with noisy euclidian heuristic
    bool requestRandomPath(std::vector<glm::vec2>& positions);
    
private:

    const int NO_CLOSEST_NODE_FOUND = -1;
    
    // Returns the index of the closest visible and unobstructed graph node to the given position
    int getClosestNodeToPosition(const glm::vec2& pPos) const;
    
    // Converts node indices to positions
    void convertIndicesToVectors(std::list<int>& pathOfNodeIndices, std::vector<glm::vec2>& positions);
    
    // Work around for solving the movement issues created by the graph nodes that are few
    void cullBackNodes(std::vector<glm::vec2>& positions);
    void cullFrontNodes(const glm::vec2& pTargetPos, std::vector<glm::vec2>& positions);
    
    glm::vec2 mDestinationPos;
    GameCharacterController* mOwner;
    
    // A* search with euclidian heuristic
    std::unique_ptr<AStarSearch<PlainNavGraph, AstarEuclidHeuristic>> mAstarSearch;
};

#endif /* PathPlanner_hpp */
