//
//  GameWorld.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "BattleCityGameWorld.hpp"

#include "BattleCityCommons.hpp"

//#include "Tank.hpp"
#include "TankMissileManager.hpp"
#include "GameWorldInfo.hpp"

BattleCityGameWorld::BattleCityGameWorld()
    : mTankImagePath("Images/BattleCity/tank.png")
{
    mLegacyCollisionGrid = std::make_unique<  LegacyCollisionGrid<LegacyCollider> >(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
    TankMissileManager::getInstance().init( mLegacyCollisionGrid.get() );
}

BattleCityGameWorld::~BattleCityGameWorld()
{
    mTerrainVector.clear();
    mNpcVector.clear();
}


std::vector<Texture*>& BattleCityGameWorld::getObjectTextures()
{
    mTextures.clear();

    // NOT IN USE !!!! ////
    for(const auto& terrainElement : mTerrainVector)
    {
        mTextures.push_back(terrainElement->getTexture());
    }
    
    for(const auto& npc : mNpcVector)
    {
        mTextures.push_back(npc->getTexture());
    }
    
    mTextures.push_back( mPlayer->getVisual() );
    
    TankMissileManager::getInstance().pushTextures(mTextures);
    
    for(const auto& ai : mAIs)
    {
        mTextures.push_back( ai->getVisual() );
    }
    
    
    for(size_t wi = 0; wi < mWalls.size(); ++wi)
    {
         mTextures.push_back( mWalls[wi]->getTexture() );
    }
    
    return mTextures;
}

void BattleCityGameWorld::callOnFrame()
{
    TankMissileManager::getInstance().update();
    mPlayer->Update();
    
    GameInfo.playerPosition = mPlayer->getPosition();
    for(const auto& ai : mAIs)
    {
        ai->Update();
    }
    
    mLegacyCollisionGrid->insert( mPlayer->getCollider() );

    // Insert to the grid
    for(size_t wi = 0; wi < mWalls.size(); ++wi)
    {
         mLegacyCollisionGrid->insert( mWalls[wi]->getCollider() );
    }
    
    for(const auto& ai : mAIs)
    {
         mLegacyCollisionGrid->insert( ai->getCollider() );
    }
    
    mLegacyCollisionGrid->iterateGrid();
    
    
    mLegacyCollisionGrid->clear();
}

void BattleCityGameWorld::generateTerrain()
{
    const std::string wallPath = "Images/BattleCity/wall.png";
    
    // Construct the borders
    auto width = WINDOW_WIDTH / WALL_TEXTURE_WIDTH;
    auto height = WINDOW_HEIGHT / WALL_TEXTURE_HEIGHT;
    for(auto row = 0; row < height; ++row)
    {
        for(auto col = 0; col < width; ++col)
        {
            if(row == 0 || row == height - 1)
            {
                mWalls.emplace_back( std::make_unique<Wall>(col * WALL_TEXTURE_WIDTH, row * WALL_TEXTURE_HEIGHT, wallPath) );
            }
            else
            {
                mWalls.emplace_back( std::make_unique<Wall>( 0, row * WALL_TEXTURE_HEIGHT, wallPath ) );
                mWalls.emplace_back( std::make_unique<Wall>((width - 1) * WALL_TEXTURE_WIDTH, row * WALL_TEXTURE_HEIGHT, wallPath ) );
                break;
            }
        }
    }
    
    // Construct the inside elements
    const auto widthGap = WINDOW_WIDTH / 8;
    const auto heightGap = WINDOW_HEIGHT / 6;
    
    // Construct the left L
    // - part
    auto yPos = (heightGap * 3) - (WALL_TEXTURE_HEIGHT * 2);
    auto xPos = WALL_TEXTURE_WIDTH;
    auto limit = (widthGap * 3) + WALL_TEXTURE_WIDTH;
    while(xPos < limit)
    {
        mWalls.emplace_back( std::make_unique<Wall>(xPos, yPos, wallPath ) );
        xPos += WALL_TEXTURE_WIDTH;
    }
    // | part
    xPos -= WALL_TEXTURE_WIDTH;
    yPos = heightGap;
    limit = (heightGap * 3) - (WALL_TEXTURE_HEIGHT * 2);
    while(yPos < limit)
    {
        mWalls.emplace_back( std::make_unique<Wall>(xPos, yPos, wallPath ) );
        yPos += WALL_TEXTURE_HEIGHT;
    }
    
    // Construct the right L
    // | part
    xPos = (widthGap * 5) - WALL_TEXTURE_WIDTH;
    yPos = heightGap;
    limit = (heightGap * 3) - (WALL_TEXTURE_HEIGHT * 2);
    while(yPos < limit)
    {
        mWalls.emplace_back( std::make_unique<Wall>(xPos, yPos, wallPath ) );
        yPos += WALL_TEXTURE_HEIGHT;
    }
    // - part
    xPos = (widthGap * 5) - WALL_TEXTURE_WIDTH;
    yPos = (heightGap * 3) - (WALL_TEXTURE_HEIGHT * 2);
    limit = WINDOW_WIDTH - WALL_TEXTURE_WIDTH;
    while(xPos < limit)
    {
        mWalls.emplace_back( std::make_unique<Wall>(xPos, yPos, wallPath ) );
        xPos += WALL_TEXTURE_WIDTH;
    }
    
    // Construct the line in the middle
    xPos = (widthGap * 2) + (WALL_TEXTURE_WIDTH / 2);
    yPos = (heightGap * 4);
    limit = (widthGap * 6) + (WALL_TEXTURE_WIDTH / 2);
    while(xPos < limit)
    {
        mWalls.emplace_back( std::make_unique<Wall>(xPos, yPos, wallPath) );
        xPos += WALL_TEXTURE_WIDTH;
    }
    
    mWalls.emplace_back( std::make_unique<Wall>( (WINDOW_WIDTH / 2) - (WALL_TEXTURE_WIDTH / 2), (WINDOW_HEIGHT / 2) - (WALL_TEXTURE_HEIGHT / 2) , wallPath) );
    
}

void BattleCityGameWorld::generateNPCs()
{
    mAIs.emplace_back( std::make_unique<TankAI>(glm::vec2(64, 64)) );
    mAIs.emplace_back( std::make_unique<TankAI>(glm::vec2(896, 64)) );
    
    mAIs[0]->setPosition(glm::vec2(64, 64));
    mAIs[1]->setPosition(glm::vec2(896, 64));
}

void BattleCityGameWorld::generatePlayers()
{
    mPlayer = std::make_unique<Player>();
}
