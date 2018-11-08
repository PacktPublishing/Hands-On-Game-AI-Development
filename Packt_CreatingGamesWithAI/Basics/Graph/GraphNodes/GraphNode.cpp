//
//  GraphNode.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "GraphNode.hpp"

#include "Commons.hpp"

using namespace GraphCommons;

GraphNode::GraphNode()
 : mIndex(INVALID_NODE_INDEX)
{ }

GraphNode::GraphNode(const int pIndex)
: mIndex(pIndex)
{ }

GraphNode::~GraphNode()
{}

int GraphNode::getIndex() const
{
    return  mIndex;
}

void GraphNode::setIndex(const int pIndex)
{
    mIndex = pIndex;
}
