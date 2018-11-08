//
//  PLG_GameWorld.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef PLG_GameWorld_hpp
#define PLG_GameWorld_hpp

#include "AbstractGameWorld.hpp"

#include "CollisionGrid.hpp"
#include "PLG_WallController.hpp"
#include "PLG_Player.hpp"
#include "PLG_EnemyAi.hpp"
#include "PLG_KeyController.hpp"
#include "PLG_AlarmController.hpp"
#include "SparseGraph.hpp"
#include "NavGraphNode.hpp"
#include "GraphEdge.hpp"

class PLG_GameWorld : public AbstractGameWorld
{
public:
    
    PLG_GameWorld();
    virtual ~PLG_GameWorld() { }
    
    std::vector<Texture*>& getObjectTextures() override;
    
    void reset() override;
    void callOnFrame() override;
    
protected:
    
    void generateTerrain() override;
    void generateNPCs() override;
    void generatePlayers() override;
    
private:

    std::unique_ptr<Texture> mGameOverImage;
    std::unique_ptr<PLG_KeyController> mKey;
    std::unique_ptr<PLG_AlarmController> mAlarm;
    std::unique_ptr<PLG_Player> mPlayer;
    std::vector< std::unique_ptr<PLG_EnemyAi>> mAIs;
    std::vector< std::unique_ptr<PLG_WallController> > mWalls;
    
    SparseGraph<NavGraphNode<void*>, GraphEdge> mNavGraph;
};

#endif /* PLG_GameWorld_hpp */
