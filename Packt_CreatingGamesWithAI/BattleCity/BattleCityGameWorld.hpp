//
//  GameWorld.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef GameWorld_hpp
#define GameWorld_hpp

#include "AbstractGameWorld.hpp"

#include "Player.hpp"
#include "TankAI.hpp"
#include "Wall.hpp"


class BattleCityGameWorld : public AbstractGameWorld
{
public:
    
    BattleCityGameWorld();
    virtual ~BattleCityGameWorld();
    
    std::vector<Texture*>& getObjectTextures() override;
    
    void callOnFrame() override;
    
protected:
    
    void generateTerrain() override;
    void generateNPCs() override;
    void generatePlayers() override;
    
private:
    
    std::string mTankImagePath;

    std::unique_ptr< LegacyCollisionGrid<LegacyCollider> > mLegacyCollisionGrid;
    
    
    std::vector<VisualObject*> mTerrainVector;
    std::vector<MovingObject*> mNpcVector;

    std::unique_ptr<Player> mPlayer;
    std::vector< std::unique_ptr<TankAI>> mAIs;
    std::vector< std::unique_ptr<Wall> > mWalls;
};

#endif /* GameWorld_hpp */
