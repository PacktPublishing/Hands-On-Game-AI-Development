//
//  TankMissileManager.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "TankMissileManager.hpp"


///////////// CONSTRUCTOR - DESTRUCTOR /////////////

TankMissileManager& TankMissileManager::getInstance()
{
    static TankMissileManager instance;
    return instance;
}

TankMissileManager::TankMissileManager()
{
    
}

TankMissileManager::~TankMissileManager()
{
    reset();
}

///////////// PUBLIC METHODS /////////////

void TankMissileManager::init(LegacyCollisionGrid<LegacyCollider>* pCollisionGridRef)
{
    mCollisionGridRef = pCollisionGridRef;
}

void TankMissileManager::pushTextures(std::vector<Texture*>& pTextures)
{
    for(const auto& missile : mActiveMissiles)
    {
        pTextures.push_back( missile->getTexture() );
    }
    
    for(const auto& explosion : mActiveExplosions)
    {
        pTextures.push_back( explosion.get() );
    }
}

void TankMissileManager::reset()
{
    mActiveMissiles.clear();
    std::queue< std::unique_ptr<TankMissile> > emptyMissilePool;
    std::swap(emptyMissilePool, mMissilePool);
    
    mActiveExplosions.clear();
    std::queue< std::unique_ptr<ExplosionAnimation> > emptyExplosionPool;
    std::swap(emptyExplosionPool, mExplosionPool);
}

void TankMissileManager::insertToGrid()
{
    for(const auto& missile : mActiveMissiles)
    {
        mCollisionGridRef->insert( missile->getCollider() );
    }
}

void TankMissileManager::update()
{
    for(size_t mi = 0; mi < mActiveMissiles.size(); ++mi)
    {
        mActiveMissiles[mi]->projectile();
        if( !mActiveMissiles[mi]->isFired() )
        {
            // Collided with a tank or out of game field
            mMissilePool.push( std::move(mActiveMissiles[mi]) );
            mActiveMissiles.erase( mActiveMissiles.begin() + mi);
            --mi;
        }
    }
    
    for(size_t ei = 0; ei < mActiveExplosions.size(); ++ei)
    {
        if( mActiveExplosions[ei]->isPlaying() )
        {
            mActiveExplosions[ei]->update();
        }
        else
        {
            mExplosionPool.push( std::move(mActiveExplosions[ei]) );
            mActiveExplosions.erase( mActiveExplosions.begin() + ei);
            --ei;
        }
    }
    
    insertToGrid();
}

void TankMissileManager::requestMissile(const glm::vec2& pTankPosition, const glm::vec2& pTankHeadingVector)
{
    // Check in the pool
    //Generate new if there is none
    if(mMissilePool.size() > 0)
    {
        auto missile = std::move(mMissilePool.front());
        mMissilePool.pop();
        missile->fire(pTankPosition, pTankHeadingVector);
        mActiveMissiles.emplace_back(std::move(missile));
    }
    else
    {
        auto missile = std::make_unique<TankMissile>();
        missile->fire(pTankPosition, pTankHeadingVector);
        mActiveMissiles.emplace_back(std::move(missile));
    }
}

void TankMissileManager::requestExplosion(const glm::vec2& pPosition)
{
    if(mExplosionPool.size() > 0)
    {
        auto explosion = std::move(mExplosionPool.front());
        mExplosionPool.pop();
        explosion->getReady(pPosition);
        explosion->startAnimation();
        mActiveExplosions.emplace_back(std::move(explosion));
    }
    else
    {
        auto explosion = std::make_unique<ExplosionAnimation>(pPosition);
        explosion->startAnimation();
        mActiveExplosions.emplace_back(std::move(explosion));
    }
}
