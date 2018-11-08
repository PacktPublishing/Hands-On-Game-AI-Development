//
//  PathPlanner.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PathPlanner.hpp"

#include "PLG_GameWorldInfo.hpp"
#include "CollisionGrid.hpp"
#include "glm.hpp"

#include <limits>

PathInfo& PathInfo::getInstance()
{
    static PathInfo instance;
    return instance;
}

glm::vec2 PathInfo::getNodePosition(const int pNodeIndex) const { return navGraph->getNode(pNodeIndex).getPosition(); }

// Return true if the path from A to B is obstructed
// Return false otherwise.
//
// It functions by stepping from A to B in steps of size pBoundingRadius and tests with the
// world at each step/point
bool PathInfo::isPathObstructed(const glm::vec2& pPosA, const glm::vec2& pPosB, float pBoundingRadius) const
{
    auto dirToB = glm::normalize( (pPosB - pPosA) );
    auto currentPos = pPosA;
    auto boundingRadiusSq = pBoundingRadius * pBoundingRadius;
    
    auto distance = glm::distance(currentPos, pPosB);
    auto distanceSq = distance * distance;
    while( distanceSq  > boundingRadiusSq )
    {
        currentPos += dirToB * 0.5f * pBoundingRadius;
        if( collisionGrid->queryPoint(currentPos + 0.0001f) )
        {
            return true;
        }
        
        distance = glm::distance(currentPos, pPosB);
        distanceSq = distance * distance;
    }
    
    return false;
}

PathPlanner::PathPlanner()
    : mOwner(nullptr)
{
    mAstarSearch = std::make_unique<AStarSearch<PlainNavGraph, AstarEuclidHeuristic>>(PathInfo::getInstance().navGraph);
}

PathPlanner::PathPlanner(GameCharacterController* pOwner)
    : mOwner(pOwner)
{
    mAstarSearch = std::make_unique<AStarSearch<PlainNavGraph, AstarEuclidHeuristic>>(PathInfo::getInstance().navGraph);
}

void PathPlanner::setOwnner(GameCharacterController* pOwner) { mOwner = pOwner;}

// Finds the optimal path to the target position via A* search with euclidian heuristic
bool PathPlanner::requestPathToPosition(const glm::vec2& pTargetPos, std::vector<glm::vec2>& positions)
{
    mDestinationPos = pTargetPos;
    
    // If the agent can walk to the target positio, then there is no need to search a path
    if ( mOwner->canMoveTo(pTargetPos) )
    {
        positions.push_back(mDestinationPos);
        return true;
    }

    // Get the closest node index to the agent
    auto closestNodeToAgent = getClosestNodeToPosition(mOwner->getCenterPosition());
    
    // If there is no visible node to the agent...
    // This happens if the navigation graph is badly design, or the agent put itself
    // into a sticky situation, such as getting into a geometry in the game
    if (closestNodeToAgent == NO_CLOSEST_NODE_FOUND)
    {
        return false;
    }
    
    // Get the closest node index to the target position
    auto closestNodeToTarget = getClosestNodeToPosition(pTargetPos);
    
    // If there is no visible node to the target...
    // This situation occurs more frequently than not finding a close node to the agent position,
    // i.e. the player clicks inside an area surrounded by the walls or inside and object
    if (closestNodeToTarget == NO_CLOSEST_NODE_FOUND)
    {
        return false;
    }
    
    // Start the pathfinding process
    mAstarSearch->getPreparedForSearch(closestNodeToAgent, closestNodeToTarget);
    
    // Get the path
    auto pathOfNodeIndices = mAstarSearch->getPathToTarget();
    // If the search is successful convert the node indices into position vectors
    if (!pathOfNodeIndices.empty())
    {
        convertIndicesToVectors(pathOfNodeIndices, positions);
        
        // Work around: Remove the unnecessary nodes returned by A*
        cullBackNodes(positions);
        cullFrontNodes(pTargetPos, positions);
        
        // Remember to add the target position to the end of the path
        positions.push_back(pTargetPos);

        return true;
    }
    else
    {
        // No path found by the search
        return false;
    }
}

// Remove the unnecessary node visits on the back of the agent
void PathPlanner::cullBackNodes(std::vector<glm::vec2>& positions)
{
    const auto cullValue = -0.98f;
    auto ownerPos = mOwner->getPosition();
    auto posI = positions.begin();
    auto posII = positions.begin();
    ++posII;
    
    while( posII != positions.end() )
    {
        auto dirI = glm::normalize( (*posI) - ownerPos );
        auto dirII = glm::normalize( (*posII) - ownerPos );
        auto cosTheta = glm::dot(dirII, dirI);
        
        if(cosTheta  <= cullValue )
        {
            posI = positions.erase(posI);
        }
        else
        {
            posI = posII;
            ++posII;
        }
    }
}

// Remove the unnecessary node visits further than the target
void PathPlanner::cullFrontNodes(const glm::vec2& pTargetPos, std::vector<glm::vec2>& positions)
{
    auto posI = positions.begin() + positions.size() - 2;
    auto posII = positions.begin() + positions.size() - 1;
    auto dirI = glm::normalize( pTargetPos - (*posI) );
    auto dirII = glm::normalize( pTargetPos - (*posII) );
    auto cosTheta = glm::dot(dirII, dirI);
    
    if( cosTheta <= MathCommons::EPSILON )
    {
        posII = positions.erase(posII);
    }
}

// Finds the optimal path to a random graph node via A* search with noisy euclidian heuristic
bool PathPlanner::requestRandomPath(std::vector<glm::vec2>& positions)
{
    auto graph = PathInfo::getInstance().navGraph;
    auto targetIndex = MathCommons::randomInt(0, graph->getNumberofActiveNodes() - 1);
    return requestPathToPosition(graph->getNode(targetIndex).getPosition(), positions);
}

// Returns the index of the closest visible and unobstructed graph node to the given position
int PathPlanner::getClosestNodeToPosition(const glm::vec2& pPos) const
{
    auto closestDistance = std::numeric_limits<float>::max();
    auto closestNodeIndex = NO_CLOSEST_NODE_FOUND;
    
    auto allNodes = PathInfo::getInstance().navGraph->getNodes();
    for(const auto& node : allNodes)
    {
        if( mOwner->canMoveBetween(pPos, node.getPosition() ) )
        {
            auto distance = glm::distance(pPos, node.getPosition() );
            if(distance < closestDistance)
            {
                closestDistance = distance;
                closestNodeIndex = node.getIndex();
            }
        }
    }
    
    return closestNodeIndex;
}

void PathPlanner::convertIndicesToVectors(std::list<int>& pathOfNodeIndices, std::vector<glm::vec2>& positions)
{
    auto graph = PathInfo::getInstance().navGraph;
    for(const auto nextIndex : pathOfNodeIndices)
    {
        positions.push_back( graph->getNode(nextIndex).getPosition() );
    }
}
