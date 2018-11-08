//
//  PLG_GameWorld.cpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#include "PLG_GameWorld.hpp"

#include "PLG_Commons.hpp"
#include "PLG_GameWorldInfo.hpp"
#include "PathPlanner.hpp"

PLG_GameWorld::PLG_GameWorld()
{
    mCollisionGrid = std::make_unique<CollisionGrid>(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
}

//#include "TextureLoader.hpp"

void PLG_GameWorld::reset()
{
    PLG_GameWorldInfo::getInstance().isAlarmOn = false;
    PLG_GameWorldInfo::getInstance().isPlayerDown = false;
    
    mKey->reset();
    mAlarm->reset();
    mPlayer->reset();
    
    for(const auto& ai : mAIs)
    {
        ai->reset();
    }
}

std::vector<Texture*>& PLG_GameWorld::getObjectTextures()
{
    mTextures.clear();

    for(const auto& wall : mWalls)
    {
        wall->callOnRender(mTextures);
    }
    
    for(const auto& ai : mAIs)
    {
        ai->callOnRender(mTextures);
    }

    mPlayer->callOnRender(mTextures);
    mKey->callOnRender(mTextures);
    mAlarm->callOnRender(mTextures);
    
    if(PLG_GameWorldInfo::getInstance().isPlayerDown)
    {
        mTextures.push_back( mGameOverImage.get() );
    }
    
    return mTextures;
}

void PLG_GameWorld::callOnFrame()
{
    if( !PLG_GameWorldInfo::getInstance().isPlayerDown )
    {
        for(const auto& wall : mWalls)
        {
            mCollisionGrid->insert( wall->getCollider() );
        }
        
        for(const auto& ai : mAIs)
        {
            mCollisionGrid->insert( ai->getCollider() );
        }
        
        mCollisionGrid->insert( mKey->getCollider() );
        mCollisionGrid->insert( mAlarm->getCollider() );
        
        mPlayer->callOnFrame();
        mCollisionGrid->insert(mPlayer->getCollider());
        
        for(const auto& ai : mAIs)
        {
            ai->callOnFrame();
        }
        
        mCollisionGrid->iterateGrid();
        
        mCollisionGrid->clear();
        
        PLG_GameInfo.playerPosition = mPlayer->getPosition();
    }
}

void PLG_GameWorld::generateNPCs()
{
    mAIs.emplace_back( std::make_unique<PLG_EnemyAi>(864, 64) );
    mAIs.emplace_back( std::make_unique<PLG_EnemyAi>(896, 864) );
}

void PLG_GameWorld::generatePlayers()
{
    mPlayer = std::make_unique<PLG_Player>(PLAYER_POS_X, PLAYER_POS_Y);
}

void PLG_GameWorld::generateTerrain()
{
    mGameOverImage = std::make_unique<Texture>(384, 384, 5, "Images/PacmanLikeGame/gameover.jpg");
    
    // Set static location info about the terrain
    PLG_GameWorldInfo::getInstance().alarmPosition = glm::vec2(ALARM_POS_X, ALARM_POS_Y);
    PLG_GameWorldInfo::getInstance().keyPosition = glm::vec2(KEY_POS_X, KEY_POS_Y);
    
    // Init key and alarm
    mKey = std::make_unique<PLG_KeyController>(KEY_POS_X, KEY_POS_Y);
    mAlarm = std::make_unique<PLG_AlarmController>(ALARM_POS_X, ALARM_POS_Y);
    
    PLG_GameWorldInfo::getInstance().isPlayerDown = false;
    PLG_GameWorldInfo::getInstance().isAlarmOn = false;
    
    // Construct the borders
    auto width = WINDOW_WIDTH / WALL_TEXTURE_WIDTH;
    auto height = WINDOW_HEIGHT / WALL_TEXTURE_HEIGHT;
    for(auto row = 0; row < height; ++row)
    {
        for(auto col = 0; col < width; ++col)
        {
            if(row == 0 || row == height - 1)
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>(col * WALL_TEXTURE_WIDTH, row * WALL_TEXTURE_HEIGHT) );
            }
            else
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>( 0, row * WALL_TEXTURE_HEIGHT) );
                mWalls.emplace_back( std::make_unique<PLG_WallController>((width - 1) * WALL_TEXTURE_WIDTH, row * WALL_TEXTURE_HEIGHT) );
                break;
            }
        }
    }
    
    // Construct the first inside-border
    width = (WINDOW_WIDTH - (WALL_TEXTURE_WIDTH * 4)) / WALL_TEXTURE_WIDTH;
    height = (WINDOW_HEIGHT - (WALL_TEXTURE_HEIGHT * 4)) / WALL_TEXTURE_HEIGHT;
    for(auto row = 0; row < height; ++row)
    {
        for(auto col = 0; col < width; ++col)
        {
            if(row == 0 || row == height - 1)
            {
                if( (row == 0 && col == (width / 2)) ||  (row == height - 1 && col == ( (width - 1) / 2)))
                {
                    continue;
                }
                
                mWalls.emplace_back( std::make_unique<PLG_WallController>((col + 2) * WALL_TEXTURE_WIDTH, (row + 2) * WALL_TEXTURE_HEIGHT) );
            }
            else
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>( (col + 2) * WALL_TEXTURE_WIDTH, (row + 2) * WALL_TEXTURE_HEIGHT) );
                mWalls.emplace_back( std::make_unique<PLG_WallController>((width + 1) * WALL_TEXTURE_WIDTH, (row + 2) * WALL_TEXTURE_HEIGHT) );
                break;
            }
        }
    }
    
    // Construct the second inside-border
    width = (WINDOW_WIDTH - (WALL_TEXTURE_WIDTH * 8)) / WALL_TEXTURE_WIDTH;
    height = (WINDOW_HEIGHT - (WALL_TEXTURE_HEIGHT * 8)) / WALL_TEXTURE_HEIGHT;
    for(auto row = 0; row < height; ++row)
    {
        for(auto col = 0; col < width; ++col)
        {
            if(row == 0 || row == height - 1)
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>((col + 4) * WALL_TEXTURE_WIDTH, (row + 4) * WALL_TEXTURE_HEIGHT) );
            }
            else
            {
                if(row == height / 2)
                {
                    continue;
                }
                
                mWalls.emplace_back( std::make_unique<PLG_WallController>( (col + 4) * WALL_TEXTURE_WIDTH, (row + 4) * WALL_TEXTURE_HEIGHT) );
                mWalls.emplace_back( std::make_unique<PLG_WallController>((width + 3) * WALL_TEXTURE_WIDTH, (row + 4) * WALL_TEXTURE_HEIGHT) );
                break;
            }
        }
    }
        
    // Construct the key holder
    width = (WINDOW_WIDTH - (WALL_TEXTURE_WIDTH * 12)) / WALL_TEXTURE_WIDTH;
    height = (WINDOW_HEIGHT - (WALL_TEXTURE_HEIGHT * 12)) / WALL_TEXTURE_HEIGHT;
    for(auto row = 0; row < height; ++row)
    {
        for(auto col = 0; col < width; ++col)
        {
            if(row == 0)
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>((col + 6) * WALL_TEXTURE_WIDTH, (row + 6) * WALL_TEXTURE_HEIGHT) );
            }
            else
            {
                mWalls.emplace_back( std::make_unique<PLG_WallController>( (col + 6) * WALL_TEXTURE_WIDTH, (row + 6) * WALL_TEXTURE_HEIGHT) );
                mWalls.emplace_back( std::make_unique<PLG_WallController>((width + 5) * WALL_TEXTURE_WIDTH, (row + 6) * WALL_TEXTURE_HEIGHT) );
                break;
            }
        }
    }
    
    // Graph points
    auto nodeIndex = -1;
    
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(64, 64)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(512, 64)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(896, 64)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(896, 896)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(448, 896)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(64, 896)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(512, 192)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(768, 192)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(768, 512)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(768, 768)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(448, 768)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(192, 768)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(192, 512)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(192, 192)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(640, 512)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(640, 640)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(480, 640)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(480, 512)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(320, 640)) );

    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(320, 512)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(320, 320)) );
    mNavGraph.addNode( NavGraphNode<void *>(++nodeIndex, glm::vec2(640, 320)) );

    mNavGraph.addEdge( GraphEdge(0, 1) );
    mNavGraph.addEdge( GraphEdge(0, 5) );
    
    mNavGraph.addEdge( GraphEdge(1, 2) );
    mNavGraph.addEdge( GraphEdge(1, 6) );
    
    mNavGraph.addEdge( GraphEdge(2, 3) );
    
    mNavGraph.addEdge( GraphEdge(3, 4) );
    
    mNavGraph.addEdge( GraphEdge(4, 5) );
    mNavGraph.addEdge( GraphEdge(4, 10) );
    
    mNavGraph.addEdge( GraphEdge(6, 7) );
    mNavGraph.addEdge( GraphEdge(6, 13) );
    
    mNavGraph.addEdge( GraphEdge(7, 8) );
    
    mNavGraph.addEdge( GraphEdge(8, 9) );
    mNavGraph.addEdge( GraphEdge(8, 14) );
    
    mNavGraph.addEdge( GraphEdge(9, 10) );
    
    mNavGraph.addEdge( GraphEdge(10, 11) );
    
    mNavGraph.addEdge( GraphEdge(11, 12) );
    
    mNavGraph.addEdge( GraphEdge(12, 13) );
    mNavGraph.addEdge( GraphEdge(12, 19) );
    
    mNavGraph.addEdge( GraphEdge(14, 15) );
    mNavGraph.addEdge( GraphEdge(14, 21) );
    
    mNavGraph.addEdge( GraphEdge(15, 16) );
    
    mNavGraph.addEdge( GraphEdge(16, 17) );
    mNavGraph.addEdge( GraphEdge(16, 18) );
    
    mNavGraph.addEdge( GraphEdge(18, 19) );
    
    mNavGraph.addEdge( GraphEdge(19, 20) );
    
    mNavGraph.addEdge( GraphEdge(20, 21) );
    
    PathInfo::getInstance().navGraph = &mNavGraph;
    PathInfo::getInstance().collisionGrid = mCollisionGrid.get();
}
