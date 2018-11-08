//
//  TankMissile.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 22/06/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankMissile_hpp
#define TankMissile_hpp

#include "BattleCityCommons.hpp"

#include "MovingObject.hpp"
#include "BoxCollider.hpp"


class TankMissile : public MovingObject
{
public:
    
    TankMissile();
    virtual ~TankMissile();
    
    void reset();
    
    LegacyCollider* getCollider() const;
    void OnCollision(const LegacyCollider* obj );
    
    bool isFired();
    
    void destructSelf();
    void fire(const glm::vec2& pTankPosition, const glm::vec2& pTankHeadingVector);
    void projectile();

private:
    
    std::unique_ptr<LegacyBoxCollider> mCollider;
    
    bool mIsFired;
    
};

#endif /* TankMissile_hpp */
