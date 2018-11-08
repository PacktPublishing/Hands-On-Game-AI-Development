//
//  TankCharacter.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 09/08/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef TankCharacter_hpp
#define TankCharacter_hpp

#include "TankCommons.hpp"

#include "LegacyGameCharacter.hpp"
#include "Tank.hpp"
#include "TankLocomotion.hpp"

class TankCharacter : public LegacyGameCharacter
{
public:
    
    TankCharacter(LegacyGameCharacter* const pOwner, const std::string& pTexturePath = "Images/BattleCity/tank.png");
    ~TankCharacter()    { }

    Texture* getVisual() const override;

    LegacyCollider* getCollider() const override;
    glm::vec2 getPosition() const override;
    glm::vec2 getHeadingVector() const override;
    
    LegacyGameCharacter* const getOwner() const;
    
    TankCommons::eTANK_MOVEMENT getCurrentMovement() const;
    
    void setPosition(const glm::vec2& pPos) override;
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopMoving();
    void fire();
    
    void Update() override;
    void handleCollision(const LegacyCollider* pObj) override;
    
private:
    
    TankCommons::eTANK_MOVEMENT mMovementDecision;
    
    LegacyGameCharacter* const mOwner;
    
    std::unique_ptr<Tank> mTank;    // Visual + Data for now
    TankLocomotion mLocomotion;
};

#endif /* TankCharacter_hpp */
