//
//  AbstractGameWorld.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 19/09/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef AbstractGameWorld_hpp
#define AbstractGameWorld_hpp

#include "Texture.hpp"
#include "CollisionGrid.hpp"

#include <vector>

class AbstractGameWorld : public IGameObject
{
public:
    
    AbstractGameWorld() { }
    virtual ~AbstractGameWorld() { mTextures.clear(); }
    
    virtual std::vector<Texture*>& getObjectTextures() = 0;
    
    virtual void constructGameWorld()
    {
        generateTerrain();
        generateNPCs();
        generatePlayers();
    }

protected:
    
    virtual void generateTerrain() = 0;
    virtual void generateNPCs() = 0;
    virtual void generatePlayers() = 0;
    
    std::vector<Texture*> mTextures;
    std::unique_ptr<CollisionGrid> mCollisionGrid;
    
};

#endif /* AbstractGameWorld_hpp */
