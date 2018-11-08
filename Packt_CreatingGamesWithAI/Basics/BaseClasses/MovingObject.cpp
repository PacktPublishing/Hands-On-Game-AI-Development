//
//  MovingObject.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 15/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "MovingObject.hpp"

#include "Commons.hpp"

#include "trigonometric.hpp"
#include "geometric.hpp"

MovingObject::MovingObject(const std::string& pPath)
    :   VisualObject(pPath),
        mHeadingVector(glm::sin(0), -glm::cos(0)), mSideVector(-mHeadingVector.y, mHeadingVector.x),
        mSpeed(0), MAX_SPEED(MathCommons::EPSILON), mVelocity(mHeadingVector)
{
    
}

MovingObject::MovingObject(const int pZOrder, const std::string& pPath)
    : VisualObject(pZOrder, pPath),
    mHeadingVector(glm::sin(0), -glm::cos(0)), mSideVector(-mHeadingVector.y, mHeadingVector.x),
    mSpeed(0), MAX_SPEED(MathCommons::EPSILON), mVelocity(mHeadingVector)
{

}

MovingObject::MovingObject(const int pScreenX, const int pScreenY, const std::string& pPath)
    : VisualObject(pScreenX, pScreenY, pPath),
    mHeadingVector(glm::sin(0), -glm::cos(0)), mSideVector(-mHeadingVector.y, mHeadingVector.x),
    mSpeed(0), MAX_SPEED(MathCommons::EPSILON), mVelocity(mHeadingVector)
{

}

MovingObject::MovingObject(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath)
    : VisualObject(pScreenX, pScreenY, pZOrder, pPath),
    mHeadingVector(glm::sin(0), -glm::cos(0)), mSideVector(-mHeadingVector.y, mHeadingVector.x),
    mSpeed(0), MAX_SPEED(MathCommons::EPSILON), mVelocity(mHeadingVector)
{

}

MovingObject::~MovingObject()
{
    
}

Texture* MovingObject::getTexture()
{
    mTexture->setPosition(mPosition);
    return mTexture.get();
}

void MovingObject::setHeadingVector(const float pX, const float pY)
{
    mHeadingVector.x = pX;
    mHeadingVector.y = pY;
    
    mSideVector.x = -mHeadingVector.y;
    mSideVector.y = mHeadingVector.x;
}

void MovingObject::setHeadingVector(const glm::vec2& pVector)
{
    mHeadingVector.x = pVector.x;
    mHeadingVector.y = pVector.y;
    
    mSideVector.x = -mHeadingVector.y;
    mSideVector.y = mHeadingVector.x;
}

void MovingObject::setHeadingVector(const float pAngleRotation)
{
    // TODO Move rotation part into a common function or sth
    
    auto radAngle =  ( pAngleRotation * M_PI ) * 0.0055555556f;
    
    // Rotate the facing vector around z-axis (right-hand)
    // x' = x cos(tht) + y sin(tht)
    // y' = x -sin(tht) + y cos(tht)
    // z' = z
    
    auto cosTheta = cos(radAngle);
    auto sinTheta = sin(radAngle);
    
    auto px = (mHeadingVector.x * cosTheta) + (mHeadingVector.y * -sinTheta);
    auto py = (mHeadingVector.x * sinTheta) + (mHeadingVector.y * cosTheta);

    mHeadingVector.x = px;
    mHeadingVector.y = py;
    
    mHeadingVector = glm::normalize(mHeadingVector);
    
    mSideVector.x = -mHeadingVector.y;
    mSideVector.y = mHeadingVector.x;
    
    mVelocity = mHeadingVector;
    
}

glm::vec2 MovingObject::getHeadingVector() const
{
    return mHeadingVector;
}

glm::vec2 MovingObject::getVelocity() const
{
    return mVelocity;
}

void MovingObject::setDefaultSpeed(const float pDefaultSpeed)
{
    mSpeed = pDefaultSpeed;
    MAX_SPEED = mSpeed + MathCommons::EPSILON;
}

float MovingObject::getDefaultSpeed() const
{
    return mSpeed;
}
