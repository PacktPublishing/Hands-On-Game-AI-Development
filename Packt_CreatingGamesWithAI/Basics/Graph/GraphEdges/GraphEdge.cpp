//
//  GraphEdge.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 08/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "GraphEdge.hpp"

#include "Commons.hpp"
using namespace GraphCommons;

GraphEdge::GraphEdge()
    : mFrom(INVALID_NODE_INDEX), mTo(INVALID_NODE_INDEX), mCost(DEFAULT_COST)
{ }

GraphEdge::GraphEdge(const int pFrom, const int pTo)
    : mFrom(pFrom), mTo(pTo), mCost(DEFAULT_COST)
{ }

GraphEdge::GraphEdge(const int pFrom, const int pTo, const float pCost)
: mFrom(pFrom), mTo(pTo), mCost(pCost)
{ }

GraphEdge::~GraphEdge()
{ }

int GraphEdge::getFrom() const { return mFrom; }
int GraphEdge::getTo() const { return mTo; }
float GraphEdge::getCost() const { return mCost; }

void GraphEdge::setFrom(const int pFrom) { mFrom = pFrom; }
void GraphEdge::setTo(const int pTo) { mTo = pTo; }
void GraphEdge::setCost(const float pCost) { mCost = pCost; }

bool GraphEdge::operator==(const GraphEdge& pOther) const
{
    return (
                this->getFrom() == pOther.getFrom() &&
                this->getTo()   == pOther.getTo() &&
                this->getCost() == pOther.getCost()
            );
}

bool GraphEdge::operator!=(const GraphEdge& pOther) const
{
    return !(*this == pOther);
}
