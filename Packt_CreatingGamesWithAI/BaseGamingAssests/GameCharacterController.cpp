//
//  GameCharacterController.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 10/10/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "GameCharacterController.hpp"

#include "PLG_GameWorldInfo.hpp"
#include "MovingObject.hpp"
#include "PathPlanner.hpp"

glm::vec2 GameCharacterController::getPosition() const
{
    return mMovingObjectReference->getPosition();
}

glm::vec2 GameCharacterController::getCenterPosition() const
{
    return getPosition() + glm::vec2(mMovingObjectReference->getWidth() * 0.5f, mMovingObjectReference->getHeight() * 0.5f);
}

// Checks whether the agent can move to the given position from its current position
bool GameCharacterController::canMoveTo(const glm::vec2& pPos)
{
    return  !PathInfo::getInstance().isPathObstructed(pPos, getCenterPosition(), getBoundingRadius());
}

// Checks whether the agent can move between given position
bool GameCharacterController::canMoveBetween(const glm::vec2& pFrom, const glm::vec2& pTo)
{
    return   !PathInfo::getInstance().isPathObstructed(pFrom, pTo, getBoundingRadius());
}
