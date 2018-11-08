//
//  TankLocomotion.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankLocomotion.hpp"

#include "Timer.hpp"

TankLocomotion::TankLocomotion()
    : LegacyLocomotion()
{
    
}

TankLocomotion::TankLocomotion(Tank* pTank)
    : LegacyLocomotion(pTank)
{
    
}

TankLocomotion::~TankLocomotion()
{
    
}

void TankLocomotion::turnLeft()
{
    mObject->decreaseRotation(90.f);
}

void TankLocomotion::turnRight()
{
    mObject->increaseRotation(90.f);
}

void TankLocomotion::moveForward()
{
    mObject->setPosition(  mObject->getPosition() + (mObject->getVelocity() * mObject->getDefaultSpeed() * Time.deltaTime) );
}

void TankLocomotion::moveBackward()
{
    mObject->setPosition(mObject->getPosition() - (mObject->getVelocity() * mObject->getDefaultSpeed() * Time.deltaTime));
}
