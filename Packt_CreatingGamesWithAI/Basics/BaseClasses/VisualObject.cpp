//
//  VisualObject.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 14/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "VisualObject.hpp"

VisualObject::VisualObject()
    : GameObject()
{
    mTexture = std::make_unique<Texture>();
    mPosition = mTexture->getPosition();
}

VisualObject::VisualObject(const std::string& pPath)
    : GameObject()
{
    mTexture = std::make_unique<Texture>(pPath);
    mPosition = mTexture->getPosition();
}

VisualObject::VisualObject(const int pZOrder, const std::string& pPath)
    : GameObject()
{
    mTexture = std::make_unique<Texture>(pZOrder, pPath);
    mPosition = mTexture->getPosition();
}

VisualObject::VisualObject(const int pScreenX, const int pScreenY, const std::string& pPath)
    : GameObject()
{
    mTexture = std::make_unique<Texture>(pScreenX, pScreenY, pPath);
    mPosition = mTexture->getPosition();
}

VisualObject::VisualObject(const int pScreenX, const int pScreenY, const int pZOrder, const std::string& pPath)
    : GameObject()
{
    mTexture = std::make_unique<Texture>(pScreenX, pScreenY, pZOrder, pPath);
    mPosition = mTexture->getPosition();
}

VisualObject::~VisualObject()
{
    
}
void VisualObject::init(
                          const int pScreenX, const int pScreenY,
                          const int pZOrder, const float pRotationDegree,
                          const std::string& pPath
                        )
{
    mPosition.x = pScreenX;
    mPosition.y = pScreenY;
    
    mTexture->init(mPosition.x, mPosition.y, pZOrder, pRotationDegree, pPath);
}

Texture* VisualObject::getTexture()
{
    return mTexture.get();
}

void VisualObject::setPosition(const glm::vec2& pos)
{
    mPosition = pos;
    mTexture->setPosition(mPosition);
}
glm::vec2 VisualObject::getPosition() const
{
    return mPosition;
}

float VisualObject::getWidth() const
{
    return mTexture->getWidth();
}

float VisualObject::getHeight() const
{
    return mTexture->getHeight();
}

