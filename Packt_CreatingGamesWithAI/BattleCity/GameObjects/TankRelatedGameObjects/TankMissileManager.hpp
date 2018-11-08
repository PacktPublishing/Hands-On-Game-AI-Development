//
//  TankMissileManager.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankMissileManager_hpp
#define TankMissileManager_hpp

#include "TankMissile.hpp"
#include "ExplosionAnimation.hpp"

#include "CollisionGrid.hpp"

#include <queue>

class TankMissileManager
{
public:
    
    static TankMissileManager& getInstance();
    
    void init(LegacyCollisionGrid<LegacyCollider>* pCollisionGridRef);

    void pushTextures(std::vector<Texture*>& pTextures);
    
    void reset();
    void update();
    
    void requestMissile(const glm::vec2& pTankPosition, const glm::vec2& pTankHeadingVector);
    void requestExplosion(const glm::vec2& pPosition);
    
private:
    
    TankMissileManager();
    ~TankMissileManager();
    
    void insertToGrid();
    
    LegacyCollisionGrid<LegacyCollider>* mCollisionGridRef;
    
    std::vector< std::unique_ptr<TankMissile> > mActiveMissiles;
    std::queue< std::unique_ptr<TankMissile> > mMissilePool;
    
    std::vector< std::unique_ptr<ExplosionAnimation> > mActiveExplosions;
    std::queue< std::unique_ptr<ExplosionAnimation> > mExplosionPool;
    
};

#endif /* TankMissileManager_hpp */
