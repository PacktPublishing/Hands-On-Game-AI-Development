//
//  Player.hpp
//  Packt_CreatingGamesWithAI
//
//  Created by Cihan Ozer on 17/05/2018.
//  Copyright © 2018 Cihan Ozer. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "LegacyGameCharacter.hpp"
#include "TankCharacter.hpp"

class Player : public LegacyGameCharacter
{
public:
    
    Player();
    virtual ~Player();
    
    void keyboardEventCallback(KeyboardEvents pEvent) override;
    
    Texture* getVisual() const override;
    LegacyCollider* getCollider() const override;;
    glm::vec2 getPosition() const override;;
    glm::vec2 getHeadingVector() const override;;
    
    void setPosition(const glm::vec2& pPos) override;
    
    void Update() override;
    
    void handleCollision(const LegacyCollider* pObj) override;
    
private:
    
    float mFireCoolDown;
    
    std::unique_ptr<TankCharacter> mTankCharacter;
    
    void reset();
    
    void handleFiring();
};

#endif /* Player_hpp */
